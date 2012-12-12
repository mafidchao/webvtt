#include "parser_internal.h"

/**
 * There are probably enough jumps and stack pops here to fill up quite a few caches but it may still
 * be much smaller than a gigantic table-based solution.
 *
 * TODO: Replace all char literals with hex values, just in case compiling on a machine which uses an
 * incompatible character set
 */

#define UTF8_DIGIT case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
#define UTF8_WHITESPACE case 0x0D: case 0x0A: case 0x20: case 0x09:
#define UTF8_SPACE case 0x20:
#define UTF8_TAB case 0x09:
#define UTF8_CR case 0x0D:
#define UTF8_LF case 0x0A:

#define UTF8_DASH case 0x2D:
#define UTF8_PERIOD case 0x2E:
#define UTF8_GT case 0x3E:
#define UTF8_COLON case 0x3A:
#define UTF8_PERCENT case 0x25:

#define UTF8_0 case 0x30:
#define UTF8_1 case 0x31:
#define UTF8_2 case 0x32:
#define UTF8_3 case 0x33:
#define UTF8_4 case 0x34:
#define UTF8_5 case 0x35:
#define UTF8_6 case 0x36:
#define UTF8_7 case 0x37:
#define UTF8_8 case 0x38:
#define UTF8_9 case 0x39:

#define UTF8_a case 0x61:
#define UTF8_b case 0x62:
#define UTF8_c case 0x63:
#define UTF8_d case 0x64:
#define UTF8_e case 0x65:
#define UTF8_f case 0x66:
#define UTF8_g case 0x67:
#define UTF8_h case 0x68:
#define UTF8_i case 0x69:
#define UTF8_j case 0x6A:
#define UTF8_k case 0x6B:
#define UTF8_l case 0x6C:
#define UTF8_m case 0x6D:
#define UTF8_n case 0x6E:
#define UTF8_o case 0x6F:
#define UTF8_p case 0x70:
#define UTF8_q case 0x71:
#define UTF8_r case 0x72:
#define UTF8_s case 0x73:
#define UTF8_t case 0x74:
#define UTF8_u case 0x75:
#define UTF8_v case 0x76:
#define UTF8_w case 0x77:
#define UTF8_x case 0x78:
#define UTF8_y case 0x79:
#define UTF8_z case 0x7A:

#define UTF8_A case 0x41:
#define UTF8_B case 0x42:
#define UTF8_C case 0x43:
#define UTF8_D case 0x44:
#define UTF8_E case 0x45:
#define UTF8_F case 0x46:
#define UTF8_G case 0x47:
#define UTF8_H case 0x48:
#define UTF8_I case 0x49:
#define UTF8_J case 0x4A:
#define UTF8_K case 0x4B:
#define UTF8_L case 0x4C:
#define UTF8_M case 0x4D:
#define UTF8_N case 0x4E:
#define UTF8_O case 0x4F:
#define UTF8_P case 0x50:
#define UTF8_Q case 0x51:
#define UTF8_R case 0x52:
#define UTF8_S case 0x53:
#define UTF8_T case 0x54:
#define UTF8_U case 0x55:
#define UTF8_V case 0x56:
#define UTF8_W case 0x57:
#define UTF8_X case 0x58:
#define UTF8_Y case 0x59:
#define UTF8_Z case 0x5A:

#define UTF8_BOM0 case 0xEF:
#define UTF8_BOM1 case 0xBB:
#define UTF8_BOM2 case 0xBF:

#define DEFAULT default:

/**
 * Just for semantic clarity
 */
#define OR
#define AND

#define OVERFLOW(X) \
	if( self->token_pos >= (sizeof(self->token) - 1 ) ) \
	{ \
		RETURN(X) \
	}

#define BEGIN_STATE(state) case state: { switch(c) {
#define END_STATE DEFAULT BACKUP return BADTOKEN; } } break;
#define END_STATE_EX } } break;

#define BACKUP (*pos)--; --self->column; self->token[--self->token_pos] = 0; self->tstate = T_INITIAL;
#define SET_STATE(X) self->tstate = X; break;
#define RETURN(X) self->tstate = T_INITIAL; return X;
#define SET_NEWLINE self->line++; self->column = 1; RETURN(NEWLINE)
#define CONTINUE continue;

#define RESET self->column = 1; self->bytes = self->token_pos = 0; self->tstate = T_INITIAL;
#define BREAK break;

#define CHECK_BROKEN_TIMESTAMP \
if(self->token_pos == sizeof(self->token) - 1 ) \
{ \
	ERROR(WEBVTT_MALFORMED_TIMESTAMP); \
	return BADTOKEN; \
}

/**
 * lexer state
 */
enum token_state_t
{
	T_INITIAL = 0, T_BOM0, T_BOM1, T_WEBVTT0, T_WEBVTT1, T_WEBVTT2, T_WEBVTT3, T_WEBVTT4, T_WEBVTT5, T_DASH0, T_SEP1,
	T_DIGIT0, T_NEWLINE0, T_WHITESPACE, T_POSITION0, T_POSITION1, T_POSITION2, T_POSITION3, T_POSITION4, T_POSITION5, 
	T_POSITION6, T_ALIGN0, T_ALIGN1, T_ALIGN2, T_ALIGN3, T_L0, T_LINE1, T_LINE2, T_LINE3,
	T_VERTICAL0, T_VERTICAL1, T_VERTICAL2, T_VERTICAL3, T_VERTICAL4, T_VERTICAL5, T_VERTICAL6, T_RL0,
	T_S0, T_SIZE1, T_SIZE2, T_START1, T_START2, T_START3, T_MIDDLE0, T_MIDDLE1, T_MIDDLE2, T_MIDDLE3,
	T_MIDDLE4, T_END0, T_END1, T_TIMESTAMP1, T_TIMESTAMP2, T_TIMESTAMP3, T_RIGHT1, T_RIGHT2,
	T_RIGHT3, T_NOTE1, T_NOTE2, T_NOTE3, T_LEFT1, T_LEFT2, 
};

WEBVTT_INTERN webvtt_status
webvtt_lex_word( webvtt_parser self, webvtt_bytearray *pba, const webvtt_byte *buffer, webvtt_uint *ppos, webvtt_uint length, int finish )
{
	webvtt_status status = WEBVTT_SUCCESS;
	webvtt_uint pos = *ppos;
	int d = 0;
	if( !pba )
	{
		return WEBVTT_INVALID_PARAM;
	}
	if( !*pba )
	{
		if( WEBVTT_FAILED( status = webvtt_create_bytearray( 8, pba ) ) )
		{
			return status;
		}
	}

# define ASCII_DASH (0x2D)
# define ASCII_GT (0x3E)
	while( pos < length )
	{
		webvtt_uint last_bytes = self->bytes;
		webvtt_uint last_line = self->line;
		webvtt_uint last_column = self->column;
		webvtt_uint last_pos = pos;

		webvtt_token token = webvtt_lex(self, buffer, &pos, length, finish );

		if( token == BADTOKEN )
		{
			if( WEBVTT_FAILED( status = webvtt_bytearray_putc( pba, buffer[pos] ) ) )
			{
				webvtt_delete_bytearray( pba );
				goto _finished; 
			}
			++pos;
		}
		else
		{
			pos = last_pos;
			self->bytes = last_bytes;
			self->line = last_line;
			self->column = last_column;
			goto _finished;
		}
	}

_finished:
	*ppos = pos;
	return status;
}

WEBVTT_INTERN webvtt_token
webvtt_lex( webvtt_parser self, const webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint length, int finish )
{
	while( *pos < length )
	{
		webvtt_byte c = buffer[(*pos)++];
		self->token[ self->token_pos++ ] = c;
		self->token[ self->token_pos ] = 0;
		self->column++;
		self->bytes++;
		switch( self->tstate )
		{
			BEGIN_STATE(T_INITIAL)
				UTF8_DIGIT { SET_STATE(T_DIGIT0) }
				UTF8_W  { SET_STATE(T_WEBVTT0) }
				UTF8_DASH { SET_STATE(T_DASH0) }
				UTF8_BOM0 { SET_STATE(T_BOM0) }
				UTF8_LF { SET_NEWLINE }
				UTF8_CR { SET_STATE(T_NEWLINE0) }
				UTF8_SPACE OR UTF8_TAB { SET_STATE(T_WHITESPACE) }
				UTF8_PERIOD { RETURN(FULL_STOP) }
				UTF8_COLON { RETURN(COLON) }
				UTF8_p { SET_STATE(T_POSITION0) }
				UTF8_a { SET_STATE(T_ALIGN0) }
				UTF8_l { SET_STATE(T_L0) }
				UTF8_v { SET_STATE(T_VERTICAL0) }
				UTF8_r { SET_STATE(T_RL0) }
				UTF8_s { SET_STATE(T_S0) }
				UTF8_m { SET_STATE(T_MIDDLE0) }
				UTF8_e { SET_STATE(T_END0) }
				UTF8_N { SET_STATE(T_NOTE1) }
			END_STATE

			BEGIN_STATE(T_BOM0)
				UTF8_BOM1 { SET_STATE(T_BOM1) }
			END_STATE

			BEGIN_STATE(T_BOM1)
				UTF8_BOM2
				{
					if( self->bytes == 3 )
					{
						RESET
						BREAK
					}
					RETURN(BOM)
				}
			END_STATE

			BEGIN_STATE(T_WEBVTT0)
				UTF8_E { SET_STATE(T_WEBVTT1) }
			END_STATE

			BEGIN_STATE(T_WEBVTT1)
				UTF8_B { SET_STATE(T_WEBVTT2) }
			END_STATE

			BEGIN_STATE(T_WEBVTT2)
				UTF8_V { SET_STATE(T_WEBVTT3) }
			END_STATE

			BEGIN_STATE(T_WEBVTT3)
				UTF8_T { SET_STATE(T_WEBVTT4) }
			END_STATE
		
			BEGIN_STATE(T_WEBVTT4)
				UTF8_T { RETURN(WEBVTT) }
			END_STATE
		
			BEGIN_STATE(T_DASH0)
				UTF8_DIGIT { SET_STATE(T_DIGIT0) }
				UTF8_DASH { SET_STATE(T_SEP1) }
			END_STATE

			BEGIN_STATE(T_SEP1)
				UTF8_GT { RETURN(SEPARATOR) }
			END_STATE

			BEGIN_STATE(T_DIGIT0)
				UTF8_DIGIT
				{
					OVERFLOW(INTEGER)
					SET_STATE(T_DIGIT0)
				}
				UTF8_COLON { SET_STATE(T_TIMESTAMP1) }
				UTF8_PERCENT { RETURN(PERCENTAGE) }
				DEFAULT { BACKUP AND RETURN(INTEGER) }
			END_STATE_EX

			BEGIN_STATE(T_NEWLINE0)
				UTF8_LF { SET_NEWLINE }
				DEFAULT { BACKUP AND SET_NEWLINE }
			END_STATE_EX

			BEGIN_STATE(T_WHITESPACE)
				UTF8_SPACE OR UTF8_TAB { OVERFLOW(WHITESPACE) SET_STATE(T_WHITESPACE) }
				DEFAULT { BACKUP RETURN(WHITESPACE) }
			END_STATE_EX

			BEGIN_STATE(T_POSITION0)
				UTF8_o { SET_STATE(T_POSITION1) }
			END_STATE

			BEGIN_STATE(T_POSITION1)
				UTF8_s { SET_STATE(T_POSITION2) }
			END_STATE

			BEGIN_STATE(T_POSITION2)
				UTF8_i { SET_STATE(T_POSITION3) }
			END_STATE

			BEGIN_STATE(T_POSITION3)
				UTF8_t { SET_STATE(T_POSITION4) }
			END_STATE

			BEGIN_STATE(T_POSITION4)
				UTF8_i { SET_STATE(T_POSITION5) }
			END_STATE

			BEGIN_STATE(T_POSITION5)
				UTF8_o { SET_STATE(T_POSITION6) }
			END_STATE

			BEGIN_STATE(T_POSITION6)
				UTF8_n { RETURN(POSITION) }
			END_STATE

			BEGIN_STATE(T_ALIGN0)
				UTF8_l { SET_STATE(T_ALIGN1) }
			END_STATE

			BEGIN_STATE(T_ALIGN1)
				UTF8_i { SET_STATE(T_ALIGN2) }
			END_STATE

			BEGIN_STATE(T_ALIGN2)
				UTF8_g { SET_STATE(T_ALIGN3) }
			END_STATE

			BEGIN_STATE(T_ALIGN3)
				UTF8_n { RETURN(ALIGN) }
			END_STATE

			BEGIN_STATE(T_L0)
				UTF8_r { RETURN(LR) }
				UTF8_i { SET_STATE(T_LINE1) }
				UTF8_e { SET_STATE(T_LEFT1) }
			END_STATE

			BEGIN_STATE(T_LINE1)
				UTF8_n { SET_STATE(T_LINE2) }
			END_STATE

			BEGIN_STATE(T_LINE2)
				UTF8_e { RETURN(LINE) }
			END_STATE

			BEGIN_STATE(T_LEFT1)
				UTF8_f { SET_STATE(T_LEFT2) }
			END_STATE

			BEGIN_STATE(T_LEFT2)
				UTF8_t { RETURN(LEFT) }
			END_STATE

			BEGIN_STATE(T_VERTICAL0)
				UTF8_e { SET_STATE(T_VERTICAL1) }
			END_STATE

			BEGIN_STATE(T_VERTICAL1)
				UTF8_r { SET_STATE(T_VERTICAL2) }
			END_STATE

			BEGIN_STATE(T_VERTICAL2)
				UTF8_t { SET_STATE(T_VERTICAL3) }
			END_STATE

			BEGIN_STATE(T_VERTICAL3)
				UTF8_i { SET_STATE(T_VERTICAL4) }
			END_STATE

			BEGIN_STATE(T_VERTICAL4)
				UTF8_c { SET_STATE(T_VERTICAL5) }
			END_STATE

			BEGIN_STATE(T_VERTICAL5)
				UTF8_a { SET_STATE(T_VERTICAL6) }
			END_STATE

			BEGIN_STATE(T_VERTICAL6)
				UTF8_l { RETURN(VERTICAL) }
			END_STATE
			
			BEGIN_STATE(T_RL0)
				UTF8_l { RETURN(RL) }
				UTF8_i { SET_STATE(T_RIGHT1) }
			END_STATE

			BEGIN_STATE(T_RIGHT1)
				UTF8_g { SET_STATE(T_RIGHT2) }
			END_STATE

			BEGIN_STATE(T_RIGHT2)
				UTF8_h { SET_STATE(T_RIGHT3) }
			END_STATE

			BEGIN_STATE(T_RIGHT3)
				UTF8_t { RETURN(RIGHT) }
			END_STATE

			BEGIN_STATE(T_S0)
				UTF8_t { SET_STATE(T_START1) }
				UTF8_i { SET_STATE(T_SIZE1) }
			END_STATE

			BEGIN_STATE(T_SIZE1)
				UTF8_z { SET_STATE(T_SIZE2) }
			END_STATE

			BEGIN_STATE(T_SIZE2)
				UTF8_e { RETURN(SIZE) }
			END_STATE

			BEGIN_STATE(T_START1)
				UTF8_a { SET_STATE(T_START2) }
			END_STATE

			BEGIN_STATE(T_START2)
				UTF8_r { SET_STATE(T_START3) }
			END_STATE

			BEGIN_STATE(T_START3)
				UTF8_t { RETURN(START) }
			END_STATE

			BEGIN_STATE(T_MIDDLE0)
				UTF8_i { SET_STATE(T_MIDDLE1) }
			END_STATE

			BEGIN_STATE(T_MIDDLE1)
				UTF8_d { SET_STATE(T_MIDDLE2) }
			END_STATE

			BEGIN_STATE(T_MIDDLE2)
				UTF8_d { SET_STATE(T_MIDDLE3) }
			END_STATE

			BEGIN_STATE(T_MIDDLE3)
				UTF8_l { SET_STATE(T_MIDDLE4) }
			END_STATE

			BEGIN_STATE(T_MIDDLE4)
				UTF8_e { RETURN(MIDDLE) }
			END_STATE

			BEGIN_STATE(T_END0)
				UTF8_n { SET_STATE(T_END1) }
			END_STATE

			BEGIN_STATE(T_END1)
				UTF8_d { RETURN(END) }
			END_STATE

			BEGIN_STATE(T_TIMESTAMP1)
				UTF8_DIGIT
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP1)
				}
				UTF8_COLON
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP2)
				}
				UTF8_PERIOD
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP3)
				}
			END_STATE

			BEGIN_STATE(T_TIMESTAMP2)
				UTF8_DIGIT
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP2)
				}
				UTF8_PERIOD
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP3)
				}
			END_STATE

			BEGIN_STATE(T_TIMESTAMP3)
				UTF8_DIGIT
				{
					OVERFLOW(TIMESTAMP)
					BREAK
				}
				DEFAULT
				{
					BACKUP
					RETURN(TIMESTAMP)
					BREAK
				}
			END_STATE_EX
				
			BEGIN_STATE(T_NOTE1)
				UTF8_O { SET_STATE(T_NOTE2) }
			END_STATE
			
			BEGIN_STATE(T_NOTE2)
				UTF8_T { SET_STATE(T_NOTE3) }
			END_STATE

			BEGIN_STATE(T_NOTE3)
				UTF8_E { RETURN(NOTE) }
			END_STATE
		}
	}

	/**
	 * If we got here, we've reached the end of the buffer.
	 * We therefore can attempt to finish up
	 */
	if( finish )
	{
		switch( self->tstate )
		{
			case T_DIGIT0: RETURN(INTEGER)
			case T_TIMESTAMP3: RETURN(TIMESTAMP)
			case T_WHITESPACE: RETURN(WHITESPACE)
			default:
				if(self->token_pos)
				{
					RESET
					return BADTOKEN;
				}
		}
	}
	return *pos == length || self->token_pos ? UNFINISHED : BADTOKEN;
}
/**
 * token states
T_INITIAL    + 'W' = T_WEBVTT0
T_INITIAL    + '-' = T_DASH0
T_INITIAL    + {D} = T_DIGIT0
T_INITIAL    + CR  = T_NEWLINE0
T_INITIAL    + LF  = *NEWLINE
T_INITIAL    + SP  = T_WHITESPACE
T_INITIAL    + TB  = T_WHITESPACE
T_INITIAL    + FS = *FULL_STOP
T_INITIAL    + 'p' = T_POSITION0
T_INITIAL    + 'a' = T_ALIGN0
T_INITIAL    + 'l' = T_L0
T_INITIAL    + 'v' = T_VERTICAL0
T_INITIAL    + 'r' = T_RL0
T_INITIAL    + 's' = T_S0
T_INITIAL    + 'm' = T_MIDDLE0
T_INITIAL    + 'e' = T_END0
T_WEBVTT0    + 'E' = T_WEBVTT1
T_WEBVTT1    + 'B' = T_WEBVTT2
T_WEBVTT2    + 'V' = T_WEBVTT3
T_WEBVTT3    + 'T' = T_WEBVTT4
T_WEBVTT4    + 'T' = *WEBVTT
T_DASH0      + {D} = T_DIGIT0
T_DASH0      + '-' = T_SEP1
T_SEP1       + '>' = *SEPARATOR
T_DIGIT0     + {D} = T_DIGIT0
T_NEWLINE0   + LF  = *NEWLINE
T_WHITESPACE + TB  = T_WHITESPACE
T_WHITESPACE + SP  = T_WHITESPACE
T_POSITION0  + 'o' = T_POSITION1
T_POSITION1  + 's' = T_POSITION2
T_POSITION2  + 'i' = T_POSITION3
T_POSITION3  + 't' = T_POSITION4
T_POSITION4  + 'i' = T_POSITION5
T_POSITION5  + 'o' = T_POSITION6
T_POSITION6  + 'n' = T_POSITION7
T_POSITION7  + ':' = *POSITION
T_ALIGN0     + 'l' = T_ALIGN1
T_ALIGN1     + 'i' = T_ALIGN2
T_ALIGN2     + 'g' = T_ALIGN3
T_ALIGN3     + 'n' = T_ALIGN4
T_ALIGN4     + ':' = *ALIGN
L0         + 'r' = *LR
L0         + 'i' = T_LINE1
T_LINE1      + 'n' = T_LINE2
T_LINE2      + 'e' = T_LINE3
T_LINE3      + ':' = *LINE
T_VERTICAL0  + 'e' = T_VERTICAL1
T_VERTICAL1  + 'r' = T_VERTICAL2
T_VERTICAL2  + 't' = T_VERTICAL3
T_VERTICAL3  + 'i' = T_VERTICAL4
T_VERTICAL4  + 'c' = T_VERTICAL5
T_VERTICAL5  + 'a' = T_VERTICAL6
T_VERTICAL6  + 'l' = T_VERTICAL7
T_VERTICAL7  + ':' = *VERTICAL
T_RL0        + 'l' = *RL
T_S0         + 't' = T_START1
T_S0         + 'i' = T_SIZE1
T_SIZE1      + 'z' = T_SIZE2
T_SIZE2      + 'e' = T_SIZE3
T_SIZE3      + ':' = *SIZE
T_START1     + 'a' = T_START2
T_START2     + 'r' = T_START3
T_START3     + 't' = *START
T_MIDDLE0    + 'i' = T_MIDDLE1
T_MIDDLE1    + 'd' = T_MIDDLE2
T_MIDDLE2    + 'd' = T_MIDDLE3
T_MIDDLE3    + 'l' = T_MIDDLE4
T_MIDDLE4    + 'e' = *MIDDLE
T_END0       + 'n' = T_END1
T_END1       + 'd' = *END
 */
