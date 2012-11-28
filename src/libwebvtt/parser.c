#include "parser_internal.h"
#include <string.h>

#define _ERROR(X) do { if( skip_error == 0 ) { ERROR(X); } } while(0)

/**
 * ASCII characters
 */
#define  ASCII_PERIOD (0x2E)
#define  ASCII_CR     (0x0D)
#define  ASCII_LF     (0x0A)
#define  ASCII_SPACE  (0x20)
#define  ASCII_TAB    (0x09)
#define  ASCII_DASH   (0x2D)
#define  ASCII_GT     (0x3E)

/**
 * parser modes
 */
enum
{
	M_WEBVTT = 0,
	M_CUETEXT,
	M_SKIP_CUE,
	M_READ_LINE,
};


/**
 * states
 */
enum parse_state_t
{
	/**
	 * WEBVTT parse states
	 */
		T_INITIAL = 0,
		T_TAG,
		T_TAGCOMMENT,
		T_EOL,
		T_BODY,

		/**
		 * NOTE comments
		 */
		T_COMMENT,

		/**
		 * Cuetimes
		 */
		T_FROM,
		T_SEP_LEFT,
		T_SEP,
		T_SEP_RIGHT,
		T_UNTIL,

		/**
		 * Cuesettings
		 */
		T_PRECUESETTING,
		T_CUESETTING,
		T_CUESETTING_DELIMITER,
		T_CUESETTING_VALUE,
		T_SKIP_SETTING /* We have to skip a cue-setting because of an error. */

	/**
	 * Cuetext parse states
	 */
};


#define ASCII_0 (0x30)
#define ASCII_9 (0x39)
#define ASCII_ISDIGIT(c) ( ((c) >= ASCII_0) && ((c) <= ASCII_9) )
#define ASCII_DASH (0x2D)
#define ASCII_COLON  (0x3A)

#define SECS_PER_HOUR (3600)
#define SECS_PER_MINUTE (60)
#define SECS_PER_MILLI (0.001)
#define BUFFER (self->buffer + self->position)
#define MALFORMED_TIME ((webvtt_timestamp_t)-1.0)

static int find_bytes(const webvtt_byte *buffer, webvtt_uint len, const webvtt_byte *sbytes, webvtt_uint slen);
static webvtt_int64 parse_int( const webvtt_byte **pb, int *pdigits );
static int parse_timestamp( webvtt_parser self, const webvtt_byte *b, webvtt_timestamp *result );

WEBVTT_EXPORT webvtt_status
webvtt_create_parser( webvtt_cue_fn_ptr on_read,
						webvtt_error_fn_ptr on_error, void *
						userdata,
						webvtt_parser *ppout )
{
	webvtt_parser p;
	if( !on_read || !on_error || !ppout )
	{
		return WEBVTT_INVALID_PARAM;
	}
	
	if( !(p = (webvtt_parser)webvtt_alloc0( sizeof *p ) ) )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	
	memset(p->astack, 0, sizeof(p->astack));
	p->stack = p->astack;
	p->top = p->stack;
	p->top->state = T_INITIAL;
	p->stack_alloc = sizeof(p->astack) / sizeof(p->astack[0]);

	p->read = on_read;
	p->error = on_error;
	p->column = p->line = 1;
	p->userdata = userdata;
	*ppout = p;
	
	return WEBVTT_SUCCESS;
}

static void
finish_cue( webvtt_parser self, webvtt_cue cue )
{
	if( cue )
	{
		/**
		 * Validate the cue
		 */
		if( webvtt_validate_cue( (webvtt_cue)cue ) )
		{
			self->read( self->userdata, cue );
		}
		else
		{
			webvtt_release_cue( &cue );
		}
	}
}

WEBVTT_EXPORT webvtt_status
webvtt_finish_parsing( webvtt_parser self )
{
	if( !self )
	{
		return WEBVTT_INVALID_PARAM;
	}
	/**
	 * If we have a cue in the works and are in state T_PAYLOAD or T_PAYLOADEOL,
	 * we should assume that we're finished with the cue and provide it to the application
	 */
	self->finish = 1;
	self->finish = 0;
	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT void
webvtt_delete_parser( webvtt_parser self )
{
	if( self )
	{
		if( self->stack != self->astack )
		{
			webvtt_free( self->stack );
		}

		if( self->line_buffer )
		{
			webvtt_delete_bytearray( &self->line_buffer );
		}
		if( self->cue )
		{
			webvtt_release_cue( (webvtt_cue *)&self->cue );
		}
		webvtt_free( self );
	}
}

#define BEGIN_STATE(State) case State: {
#define END_STATE } break;
#define IF_TOKEN(Token,Actions) case Token: { Actions } break;
#define BEGIN_DFA switch(top->state) {
#define END_DFA }
#define BEGIN_TOKEN switch(token) {
#define END_TOKEN }
#define IF_TRANSITION(Token,State) if( token == Token ) { self->state = State;
#define ELIF_TRANSITION(Token,State) } else IF_TRANSITION(Token,State)
#define ENDIF }
#define ELSE } else {

static WEBVTT_INTERN int
find_newline( const webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint len )
{
	while( *pos < len )
	{
		if( buffer[ *pos ] == ASCII_CR || buffer[ *pos ] == ASCII_LF )
		{
			return 1;
		} 
		else
		{ 
			(*pos)++;
		}
	}
	return -1;
}

static WEBVTT_INTERN void
find_next_whitespace(const webvtt_byte *buffer, webvtt_uint *ppos, webvtt_uint len)
{
	webvtt_uint pos = *ppos;
	while( pos < len )
	{
		webvtt_byte c = buffer[pos];
		if( c == ASCII_CR || c == ASCII_LF || c == ASCII_SPACE || c == ASCII_TAB )
		{
			break;
		}

		++pos;
	}
	*ppos = pos;
}

/**
 * basic strnstr-ish routine
 */
WEBVTT_INTERN int
find_bytes(const webvtt_byte *buffer, webvtt_uint len, const webvtt_byte *sbytes, webvtt_uint slen)
{
	webvtt_uint slen2 = slen - 1;
	do
	{
		if( *buffer == *sbytes && memcmp( buffer + 1, sbytes + 1, slen2) == 0 )
		{
			return 1;
		}
	} while( len-- >= slen && *buffer++ );
	return 0;
}

	/**
	 * Helpers to figure out what state we're on
	 */
#define SP (self->top)
#define AT_BOTTOM (self->top == self->stack)
#define ON_HEAP (self->stack_alloc == sizeof(p->astack) / sizeof(p->astack[0]))
#define STACK_SIZE ((webvtt_uint)(self->top - self->stack))
#define FRAME(i) (self->top - (i))
#define RECHECK goto _recheck;
	/**
	 * More state stack helpers
	 */
static WEBVTT_INTERN webvtt_status
do_push( webvtt_parser self, webvtt_uint state, void *data )
{
	if( STACK_SIZE + 1 >= self->stack_alloc )
	{
		webvtt_state *stack = (webvtt_state *)webvtt_alloc0( sizeof(webvtt_state) * (self->stack_alloc<<1) ), *tmp;
		if( !stack )
		{
			ERROR(WEBVTT_ALLOCATION_FAILED);
			return WEBVTT_OUT_OF_MEMORY;
		}
		memcpy( stack, self->stack, sizeof(webvtt_state) * self->stack_alloc ); \
		tmp = self->stack;
		self->stack = stack;
		self->top = stack + (self->top - tmp);
		if( tmp != self->astack )
		{
			webvtt_free( tmp );
		}
	}
	++self->top;
	self->top->state = state;
	self->top->v.pointer = data;
	return WEBVTT_SUCCESS;
}
#define PUSH(S,V) do { if( do_push(self,(S),(void*)(V)) == WEBVTT_OUT_OF_MEMORY ) return WEBVTT_OUT_OF_MEMORY; } while(0)
#define POP() \
do \
{ \
	--(self->top); \
} while(0)
static WEBVTT_INTERN webvtt_status
parse_webvtt( webvtt_parser self, const webvtt_byte *buffer, webvtt_uint *ppos, webvtt_uint len, webvtt_uint *mode, int finish )
{
	webvtt_status status = WEBVTT_SUCCESS;
	webvtt_token token;
	webvtt_uint pos = *ppos;
	int settings_delimiter = 0;
	int settings_whitespace = 0;
	webvtt_uint settings_whitespace_at;
	webvtt_uint missing_cuesetting_at;

	while( pos < len )
	{
		int skip_error = 0;
		webvtt_uint last_column = self->column;
		webvtt_uint last_line = self->line;
		webvtt_uint last_pos = pos;
		token = webvtt_lex( self, buffer, &pos, len, finish );
_recheck:
		switch( SP->state )
		{
		case T_INITIAL:
			switch( token )
			{
			case WEBVTT:
				PUSH( T_TAG, 0 );
				break;
			default:
				_ERROR(WEBVTT_MALFORMED_TAG);
			}
			break;
		
		case T_TAG:
			switch(token)
			{
			case WHITESPACE:
				/**
				 * Skip comment
				 */
				PUSH(T_TAGCOMMENT,0);
				break;
			case NEWLINE:
				/**
				 * Expect another newline
				 */
				POP();
				SP->state = T_BODY;
				PUSH(T_EOL,1);
				break;
			}
			break;

		/**
		 * COMMENT -- Read until EOL, ignore everything else
		 */
		case T_TAGCOMMENT:
			switch(token)
			{
			case NEWLINE:
				FRAME(1)->state = T_BODY;
				SP->state = T_EOL;
				SP->v.value = 1;
				break;
			default:
				continue;
			}
			break;

		/**
		 * Count EOLs, POP when finished
		 */
		case T_EOL:
			switch(token)
			{
			case NEWLINE:
				SP->v.value++;
				break;
			default:
				POP();
				RECHECK
			}
			break;

		case T_BODY:
			/**
			 * If we're here, we need to read a line
			 */
			*mode = M_READ_LINE;	
			/**
			 * We read a token before coming here, so lets just unread it.
			 */
			pos = last_pos;
			self->line = last_line;
			self->column = last_column;
			self->token_pos = 0;
			goto _finish;
			break;

		case T_FROM:
			/**
			 * We already know that this line contains '-->', and we're expecting the first TIMESTAMP
			 */
			switch(token)
			{
			case TIMESTAMP:
				if( !SP->v.cue )
				{
					if(WEBVTT_FAILED(status=webvtt_create_cue( &SP->v.cue )))
					{
						if(status == WEBVTT_OUT_OF_MEMORY)
						{
							_ERROR(WEBVTT_ALLOCATION_FAILED);
							return status;
						}
					}
				}
				if( !parse_timestamp( self, self->token, &SP->v.cue->from ) )
				{
					_ERROR(WEBVTT_MALFORMED_TIMESTAMP);
					*mode = M_SKIP_CUE;
				}
				PUSH( T_SEP_LEFT, SP->v.cue );
			}
			break;

		case T_SEP_LEFT:
			switch(token)
			{
			case WHITESPACE:
				PUSH( T_SEP, SP->v.cue );
				break;

			case SEPARATOR:
				_ERROR(WEBVTT_EXPECTED_WHITESPACE);
				PUSH( T_SEP, SP->v.cue );
				PUSH( T_SEP_RIGHT, SP->v.cue );
				break;

			case TIMESTAMP:
				_ERROR(WEBVTT_MISSING_CUETIME_SEPARATOR);
				PUSH( T_SEP, SP->v.cue );
				PUSH( T_SEP_RIGHT, SP->v.cue );
				PUSH( T_UNTIL, SP->v.cue );
				goto _until;
			}
			break;

		case T_SEP:
			switch(token)
			{
			case WHITESPACE:
				/**
				 * safely ignore whitespace
				 */
				break;
			case SEPARATOR:
				PUSH( T_SEP_RIGHT, SP->v.cue );
				break;
			}
			break;

		case T_SEP_RIGHT:
			switch(token)
			{
			case WHITESPACE:
				PUSH( T_UNTIL,SP->v.cue );
				break;

			case TIMESTAMP:
				_ERROR(WEBVTT_EXPECTED_WHITESPACE);
				PUSH(T_UNTIL,SP->v.cue);
				goto _until;
				break;
			}
			break;

		case T_UNTIL:
			switch(token)
			{
			case WHITESPACE:
				/**
				 * This whitespace can be safely ignored
				 */
				break;

			case TIMESTAMP:
_until:
				{

					webvtt_cue cue = (webvtt_cue)SP->v.cue;
					if( !parse_timestamp( self, self->token, &cue->until ) )
					{
						_ERROR(WEBVTT_MALFORMED_TIMESTAMP);
						*mode = M_SKIP_CUE;
					}
					POP(); /* T_UNTIL */
					POP(); /* T_SEP_RIGHT */
					POP(); /* T_SEP */
					POP(); /* T_SEP_LEFT */
					POP(); /* T_FROM */
					PUSH( T_PRECUESETTING, cue );
				}
				break;
			}
			break;

		case T_SKIP_SETTING:
			switch(token)
			{
				case WHITESPACE:
				case VERTICAL:
				case ALIGN:
				case LINE:
				case SIZE:
				case POSITION:
					POP();
					skip_error = 1;
					goto _precuesetting;

				case BADTOKEN:
					++pos;
					++self->column;
					/**
					 * Ignore further garbage without reporting errors.
					 */
					break;

				default:
					break;
			}
			break;

		case T_PRECUESETTING:
_precuesetting:
			switch(token)
			{
			case WHITESPACE:
				PUSH(T_CUESETTING,SP->v.cue);
				break;
			case NEWLINE:
				*mode = M_CUETEXT;
				goto _finish;

			case VERTICAL:
			case ALIGN:
			case LINE:
			case SIZE:
			case POSITION:
				/**
				 * The error actually occurs at the column PRIOR to the token, which is where the whitespace should be.
				 * Because of this, we need to use a special error macro which will let us specify the column.
				 */
				ERROR_AT_COLUMN(WEBVTT_EXPECTED_WHITESPACE,last_column);
				PUSH(T_CUESETTING,SP->v.cue);
				PUSH(T_CUESETTING_DELIMITER,token);
				break;

			default:
				_ERROR(WEBVTT_INVALID_CUESETTING_DELIMITER);
				PUSH(T_SKIP_SETTING,0);
				goto _recheck;
			}
			break;

		case T_CUESETTING:
			switch(token)
			{
			case WHITESPACE:
				break; /* Ignore whitespace */

			case NEWLINE: /* We're finished with cue-settings her, we're expecting cuetext now. */
				POP();
				*mode = M_CUETEXT;
				goto _finish;
				break;

			case BADTOKEN: /* We got some garbage, an invalid keyword. */
				ERROR_AT_COLUMN(WEBVTT_INVALID_CUESETTING,last_column);
				PUSH(T_SKIP_SETTING, 0);
				goto _recheck;
				break;

			case COLON: /* We got a colon without a cuesetting keyword. Mark that this will be a future error. */
				missing_cuesetting_at = last_column;
				PUSH(T_CUESETTING_DELIMITER,0);
				RECHECK
				break;

			case VERTICAL:
			case ALIGN:
			case LINE:
			case SIZE:
			case POSITION:
				PUSH(T_CUESETTING_DELIMITER,token);
				break;
			}
			break;

		case T_CUESETTING_DELIMITER:
		{
			switch(token)
			{
			case COLON:
				settings_delimiter = 1;
				SP->state = T_CUESETTING_VALUE;
				break;
			case WHITESPACE:
				settings_whitespace = 1;
				settings_whitespace_at = last_column;
				/**
				 * Error recovery: just attempt to continue parsing
				 */
				break;

			case INTEGER:
			case PERCENTAGE:
			case LR:
			case RL:
			case START:
			case MIDDLE:
			case END:
			case LEFT:
			case RIGHT:
				if( !skip_error && !settings_delimiter )
				{
					settings_delimiter = !settings_whitespace;
					ERROR_AT_COLUMN(WEBVTT_MISSING_CUESETTING_DELIMITER,settings_whitespace ? settings_whitespace_at : last_column);
				}
				SP->state = T_CUESETTING_VALUE;
				RECHECK
				break;

			default:
				if(!skip_error)
				{
					settings_delimiter = 1;
					ERROR_AT_COLUMN(WEBVTT_INVALID_CUESETTING_DELIMITER,last_column);
				}
				/**
				 * Error recovery: skip this cuesetting
				 */
				PUSH(T_SKIP_SETTING,0);
				break;
			}
			break;
		}
		

		case T_CUESETTING_VALUE:
			if( settings_whitespace && settings_delimiter && !skip_error)
			{
				skip_error = 1;
				ERROR_AT_COLUMN(WEBVTT_UNEXPECTED_WHITESPACE,settings_whitespace_at);
			}
			settings_whitespace = 0;
			settings_delimiter = 0;
			
			switch(token)
			{
			case WHITESPACE:
				ERROR_AT_COLUMN(WEBVTT_UNEXPECTED_WHITESPACE,last_column);
				/**
				 * Error recovery: just attempt to continue parsing
				 */
				break;
			default:
				{
					webvtt_cue cue = FRAME(1)->v.cue;
					switch( SP->v.value )
					{
					case 0:
						/**
						 * We didn't get a cuesetting key
						 */
						switch(token)
						{
						case RL: case LR: case INTEGER: case PERCENTAGE: case START: case MIDDLE: case END: case LEFT: case RIGHT:
							ERROR_AT_COLUMN(WEBVTT_MISSING_CUESETTING_KEYWORD,missing_cuesetting_at);
							break;
						default:
							ERROR_AT_COLUMN(WEBVTT_INVALID_CUESETTING,missing_cuesetting_at);
							break;
						}
						/**
						 * In either case, we need to return to normal-ness
						 */
						POP(); /* Back to T_CUESETTING */
						POP(); /* Back to T_PRECUESETTING */
						break;

					case VERTICAL:
						switch(token)
						{
						case LR:
						case RL:
							if( self->flags & READ_VERTICAL )
							{
								_ERROR(WEBVTT_VERTICAL_ALREADY_SET);
								/**
								 * Recovery: replace vertical setting with new one.
								 */
							}
							self->flags |= READ_VERTICAL;
							cue->settings.vertical = token == LR ? WEBVTT_VERTICAL_LR : WEBVTT_VERTICAL_RL;
							break;
						default:
							/**
								* Bad value. Recovery: move to next cuesetting
								*/
							_ERROR(WEBVTT_VERTICAL_BAD_VALUE);
							find_next_whitespace(buffer,&pos,len);
							break;
						}
						POP(); /* Back to T_CUESETTING */
						POP(); /* Back to T_PRECUESETTING */
						break;

					case POSITION:
						switch(token)
						{
						case PERCENTAGE:
							if( self->flags & READ_POSITION )
							{
								_ERROR(WEBVTT_VERTICAL_ALREADY_SET);
								/**
								 * Recovery: replace vertical setting with new one.
								 */
							}
							self->flags |= READ_POSITION;
							{
								const webvtt_byte *bytes = self->token;
								webvtt_int64 v = parse_int(&bytes,0);
								if( v < 0 )
								{
									ERROR_AT_COLUMN(WEBVTT_POSITION_BAD_VALUE,last_column);
									/**
									 * Value cannot be negative
									 */
								}
								cue->settings.position = (webvtt_uint)v;
							}
							break;
						default:
							/**
							 * Bad value. Recovery: move to next cuesetting
							 */
							ERROR_AT_COLUMN(WEBVTT_POSITION_BAD_VALUE,last_column);
							find_next_whitespace(buffer,&pos,len);
							break;
						}
						POP(); /* Back to T_CUESETTING */
						POP(); /* Back to T_PRECUESETTING */
						break;

					case ALIGN:
						switch(token)
						{
						case START:
						case MIDDLE:
						case END:
						case LEFT:
						case RIGHT:
							if( self->flags & READ_ALIGN )
							{
								_ERROR(WEBVTT_ALIGN_ALREADY_SET);
								/**
								 * Recovery: replace vertical setting with new one.
								 */
							}
							self->flags |= READ_ALIGN;
							switch(token)
							{
								case START: cue->settings.align = WEBVTT_ALIGN_START; break;
								case MIDDLE: cue->settings.align = WEBVTT_ALIGN_MIDDLE; break;
								case END: cue->settings.align = WEBVTT_ALIGN_END; break;
								case LEFT: cue->settings.align = WEBVTT_ALIGN_LEFT; break;
								case RIGHT: cue->settings.align = WEBVTT_ALIGN_RIGHT; break;
							}
							break;

						default:
							/**
							 * Bad value. Recovery: move to next cuesetting
							 */
							ERROR_AT_COLUMN(WEBVTT_ALIGN_BAD_VALUE,last_column);
							find_next_whitespace(buffer,&pos,len);
							break;
						}
						POP(); /* Back to T_CUESETTING */
						POP(); /* Back to T_PRECUESETTING */
						break;

					case LINE:
						switch(token)
						{
						case INTEGER:
						case PERCENTAGE:
							if( self->flags & READ_LINE )
							{
								ERROR(WEBVTT_LINE_ALREADY_SET);
								/**
								 * Recovery: replace vertical setting with new one.
								 */
							}
							self->flags |= READ_LINE;
							{
								const webvtt_byte *bytes = self->token;
								if( token == INTEGER )
								{
									cue->settings.line.no = cue->settings.position = (webvtt_int)parse_int(&bytes,0);
									cue->settings.line_is_relative = 0;
								}
								else
								{
									webvtt_int64 v = parse_int(&bytes,0);
									if( v < 0 )
									{
										_ERROR(WEBVTT_LINE_BAD_VALUE);
										/**
										 * This value cannot be negative,
										 * but I'm not sure there's really a good reason to die over it
										 */
									}
									cue->settings.line.relative_position = (webvtt_uint)v;
									cue->settings.line_is_relative = 1;
								}
							}
							break;
						default:
							/**
							 * Bad value. Recovery: move to next cuesetting
							 */
							_ERROR(WEBVTT_LINE_BAD_VALUE);
							find_next_whitespace(buffer,&pos,len);
							break;
						}
						POP(); /* Back to T_CUESETTING */
						POP(); /* Back to T_PRECUESETTING */
						break;

					case SIZE:
						switch(token)
						{
						case PERCENTAGE:
							if( self->flags & READ_SIZE )
							{
								_ERROR(WEBVTT_SIZE_ALREADY_SET);
								/**
								 * Recovery: replace vertical setting with new one.
								 */
							}
							self->flags |= READ_SIZE;
							{
								const webvtt_byte *bytes = self->token;
								webvtt_int64 v = parse_int(&bytes,0);
								if( v < 0 )
								{
									if( !skip_error )
									{
										ERROR_AT_COLUMN(WEBVTT_SIZE_BAD_VALUE,last_column);
										skip_error = 1;
									}
									/**
									 * This value cannot be negative,
									 * but I'm not sure there's really a good reason to die over it
									 */
								}
								cue->settings.size = (webvtt_uint)v;
							}
							break;
						default:
							/**
							 * Bad value. Recovery: move to next cuesetting
							 */
							if( !skip_error )
							{
								ERROR_AT_COLUMN(WEBVTT_SIZE_BAD_VALUE,last_column);
								skip_error = 1;
							}
							find_next_whitespace(buffer,&pos,len);
							break;
						}
						POP(); /* Back to T_CUESETTING */
						POP(); /* Back to T_PRECUESETTING */
						break;
					}
					break;
				}
			}
			break; /* T_CUESETTING_VALUE */
		}

		/**
		 * reset token pos
		 */
		self->token_pos = 0;
	}


_finish:
	if( finish )
	{
		if( SP->state == T_SKIP_SETTING )
		{
			int broken = 1;
			POP(); /* T_SKIP_SETTING */
			while(broken)
			{
				switch(SP->state)
				{
					case T_CUESETTING_VALUE:
					case T_CUESETTING_DELIMITER:
					case T_CUESETTING:
						POP();
					default:
						broken = 0;
						break;
				}
			}
		}
		else if( SP->state == T_CUESETTING_VALUE )
		{
			int err = 0xFFFFFFFF;
			switch(SP->v.value)
			{
			case VERTICAL: err = WEBVTT_VERTICAL_BAD_VALUE; break;
			case ALIGN: err = WEBVTT_ALIGN_BAD_VALUE; break;
			case POSITION: err = WEBVTT_POSITION_BAD_VALUE; break;
			case SIZE: err = WEBVTT_SIZE_BAD_VALUE; break;
			case LINE: err = WEBVTT_LINE_BAD_VALUE; break;
			}
			if( err != 0xFFFFFFFF )
			{
				ERROR(err);
				POP();
				POP();
			}
		}
	}
	*ppos = pos;
	return status;
}


static WEBVTT_INTERN webvtt_status
parse_cuetext( webvtt_parser self, const webvtt_byte *buffer, webvtt_uint *ppos, webvtt_uint len, webvtt_uint *mode, int finish )
{
	/**
	 * TODO:
	 * Unify cuetext parsing
	 */
	return WEBVTT_PARSE_ERROR;
}

static WEBVTT_INTERN webvtt_status
read_cuetext( webvtt_parser self, const webvtt_byte *b, webvtt_uint *ppos, webvtt_uint len, webvtt_uint *mode, webvtt_bool finish )
{
	webvtt_status status = WEBVTT_SUCCESS;
	webvtt_uint pos = *ppos;
	int finished = 0;
	do
	{
		int v;
		if( ( v = webvtt_bytearray_getline( &self->line_buffer, b, &pos, len, &self->truncate ) ) )
		{
			if( v < 0 )
			{
				status = WEBVTT_OUT_OF_MEMORY;
				goto _finish;
			}
			
			if( self->line_buffer->text[ self->line_buffer->length - 1 ] == ASCII_LF )
			{
				/**
				 * finished
				 */
				finished = 1;
			}
			webvtt_bytearray_putc( &self->line_buffer, ASCII_LF );

			if( b[pos] == ASCII_CR )
			{
				if( len - pos >= 2 && b[pos+1] == ASCII_LF )
				{
					++pos;
				}
				++pos;
			}
			else
			{
				++pos;
			}
		}
	} while( pos < len && !finished );
_finish:
	*ppos = pos;
	return status;
}

WEBVTT_EXPORT webvtt_status
webvtt_parse_chunk( webvtt_parser self, const void *buffer, webvtt_uint len )
{
	webvtt_status status;
	webvtt_uint pos = 0;
	const webvtt_byte *b = (const webvtt_byte *)buffer;

	while( pos < len )
	{
		switch( self->mode )
		{
		case M_WEBVTT:
			if( WEBVTT_FAILED(status = parse_webvtt( self, b, &pos, len, &self->mode, 0 )) )
			{
				return status;
			}
			break;

		case M_CUETEXT:
#if 0
			if( WEBVTT_FAILED(status = parse_cuetext( self, b, &pos, len, &self->mode, 0 )) )
			{
				return status;
			}
#else
			/**
			 * read in cuetext
			 */
			if( WEBVTT_FAILED(status = read_cuetext( self, b, &pos, len, &self->mode, 0 )) )
			{
				return status;
			}
#endif
			finish_cue( self, SP->v.cue );
			break;

		case M_SKIP_CUE:
			if( WEBVTT_FAILED(status = read_cuetext( self, b, &pos, len, &self->mode, 0 )) )
			{
				return status;
			}
			webvtt_delete_bytearray( &self->line_buffer );
			self->mode = M_WEBVTT;
			break;

		case M_READ_LINE:
			{
				/**
				 * Read in a line of text into the line-buffer,
				 * we will and depending on our state, do something with it.
				 */
				int ret;
				if( ( ret = webvtt_bytearray_getline( &self->line_buffer, b, &pos, len, &self->truncate ) ) )
				{
					static const webvtt_byte separator[] = { ASCII_DASH, ASCII_DASH, ASCII_GT };
					if( ret < 0 )
					{
						ERROR(WEBVTT_ALLOCATION_FAILED);
						return WEBVTT_OUT_OF_MEMORY;
					}
					switch( self->top->state )
					{
					case T_BODY:
						/**
						 * If there's a cuetime 'separator' found in the string, we need to go directly to T_FROM
						 */
						if( find_bytes( self->line_buffer->text, self->line_buffer->length, separator, sizeof(separator) ) )
						{
							/**
							 * This should be webvtt-cuetimes, so we need to activate cuetime parsing mode.
							 */
							PUSH(T_FROM,0);
							if( WEBVTT_FAILED(status = parse_webvtt( self, self->line_buffer->text, &self->line_pos, self->line_buffer->length, 
								&self->mode, 1 )) )
							{
								return status;
							}
							self->mode =  M_WEBVTT;
						}
						else
						{
							
							/**
							 * get the first token from the line. If it's NOTE,
							 * then read out a comment.
							 */
							webvtt_uint line_pos = 0;
							webvtt_uint line_tok = webvtt_lex( self, self->line_buffer->text, &line_pos, self->line_buffer->length, 0 );
							if( line_tok == NOTE )
							{
								PUSH(T_COMMENT,0);
								continue;
							}
							else
							{
								/**
								 * If it's not a NOTE, it should be considered a cue id
								 */
								webvtt_cue cue = 0;
								if(WEBVTT_FAILED(status = webvtt_create_cue(&cue)))
								{
									if( status == WEBVTT_OUT_OF_MEMORY )
									{
										/**
										 * TODO: This will report an incorrect line/column number, fix this.
										 */
										ERROR(WEBVTT_ALLOCATION_FAILED);
									}
									return status;
								}
								PUSH(T_FROM,cue);
								self->mode = M_WEBVTT;
							}
						}
						break;
					}
					webvtt_delete_bytearray( &self->line_buffer );
				}
			}
			break;
		}
	}

	return WEBVTT_SUCCESS;
}

#undef SP
#undef AT_BOTTOM
#undef ON_HEAP
#undef STACK_SIZE
#undef FRAME
#undef PUSH
#undef POP

/**
 * Get an integer value from a series of digits.
 */
static webvtt_int64
parse_int( const webvtt_byte **pb, int *pdigits )
{
	int digits = 0;
	webvtt_int64 result = 0;
	webvtt_int64 mul = 1;
	const webvtt_byte *b = *pb;
	while( *b )
	{
		webvtt_byte ch = *b;
		if( ASCII_ISDIGIT(ch) )
		{
			/**
			 * Digit character, carry on
			 */
			result = result * 10 + ( ch - ASCII_0 );
			++digits;
		}
		else if( mul == 1 && digits == 0 && ch == ASCII_DASH )
		{
			mul = -1;
		}
		else
		{
			break;
		}
		++b;
	}
	*pb = b;
	if( pdigits )
	{
		*pdigits = digits;
	}
	return result * mul;
}

/**
 * Turn the token of a TIMESTAMP tag into something useful, and returns non-zero
 * returns 0 if it fails
 */
static int
parse_timestamp( webvtt_parser self, const webvtt_byte *b, webvtt_timestamp *result )
{
	int have_hours = 0;
	int digits;
	webvtt_int64 v[4];
    if (!ASCII_ISDIGIT(*b))
	{
		goto _malformed;
	}
	
	/* get sequence of digits */
	v[0] = parse_int( &b, &digits );

	/* assume v[0] contains hours if more or less than 2 digits, or value is greater than 59 */
	if (digits != 2 || v[0] > 59)
	{
		have_hours = 1;
	}
	
	/* fail if missing colon ':' character */
	if ( !*b || *b++ != ASCII_COLON)
	{
		goto _malformed;
	}
	
	/* fail if end of data reached, or byte is not an ASCII digit */
	if (!ASCII_ISDIGIT(*b))
	{
		goto _malformed;
	}
	
	/* get another integer value, fail if digits is not equal to 2 */
    v[1] = parse_int( &b, &digits );
	if( digits != 2 )
	{
		goto _malformed;
	}
	
	/* if we already know there's an hour component, or if the next byte is a colon ':',
	   read the next value */
	if (have_hours || (*b == ASCII_COLON))
	{
		if( *b++ != COLON )
		{
			goto _malformed;
		}
        if( !ASCII_ISDIGIT(*b) )
		{
			goto _malformed;
		}
		v[2] = parse_int( &b, &digits );
		if( digits != 2 )
		{
			goto _malformed;
		}
    }
	else
	{
		/* Otherwise, if there is no hour component, shift everything over */
		v[2] = v[1];
		v[1] = v[0];
		v[0] = 0;
    }

	/* collect the manditory seconds-frac component. fail if there is no FULL_STOP '.'
	   or if there is no ascii digit following it */
	if( *b++ != ASCII_PERIOD || !ASCII_ISDIGIT(*b))
	{
		goto _malformed;
	}
	v[3] = parse_int( &b, &digits );
	if( digits != 3 )
	{
		goto _malformed;
	}
	
	/* Ensure that minutes and seconds are acceptable values */
    if( v[1] > 59 || v[2] > 59 )
	{
		goto _malformed;
	}
	
	*result = (webvtt_timestamp)( v[0] * SECS_PER_HOUR )
			+ ( v[1] * SECS_PER_MINUTE )
			+ v[2] 
			+ ( v[3] * SECS_PER_MILLI );
	
	return 1;
_malformed:
	return 0;
}
