#ifndef __INTERN_PARSER_H__
#	define __INTERN_PARSER_H__
#	include <webvtt/parser.h>
#	include "bytearray_internal.h"

typedef enum webvtt_token_t webvtt_token;

#define ASCII_0 (0x30)
#define ASCII_9 (0x39)
#define ASCII_ISDIGIT(c) ( ((c) >= ASCII_0) && ((c) <= ASCII_9) )

enum
webvtt_token_t
{
	BADTOKEN = -2,
	UNFINISHED = -1, /* not-token */
	BOM,
	WEBVTT, /* 'WEBVTT' */
	NOTE, /* 'NOTE' */
	INTEGER, /* /-?\d+/ */
	NEWLINE, /* /[\r\n]|(\r\n)/ */
	WHITESPACE, /* /[\t ]/ */
	FULL_STOP, /* '.' */
	POSITION, /* 'position:' */
	ALIGN, /* 'align:' */
	SIZE, /* 'size:' */
	LINE, /* 'line:' */
	VERTICAL, /* 'vertical:' */
	RL, /* 'rl' */
	LR, /* 'lr' */
	START, /* 'start' */
	MIDDLE, /* 'middle' */
	END, /* 'end' */
	LEFT, /* 'left' */
	RIGHT, /* 'right' */
	SEPARATOR, /* '-->' */
	TIMESTAMP,
	PERCENTAGE, /* '\d+%' */
	COLON /* ':' */
};

/**
 * Flags indicating which settings have been read
 */
#define READ_VERTICAL (1<<0)
#define READ_SIZE (1<<1)
#define READ_POSITION (1<<2)
#define READ_LINE (1<<3)
#define READ_ALIGN (1<<4)

typedef struct webvtt_state
{
	webvtt_uint state;
	union
	{
		webvtt_cue cue;
		webvtt_leaf_node *lf;
		webvtt_internal_node *in;
		webvtt_uint value;
		void *pointer;
	} v;
} webvtt_state;

struct
webvtt_parser_t
{
	webvtt_uint state;
	webvtt_uint bytes; /* number of bytes read. */
	webvtt_uint line;
	webvtt_uint column;
	webvtt_cue_fn_ptr read;
	webvtt_error_fn_ptr error;
	void *userdata;

	/**
	 * 'mode' can have several states, it is not boolean.
	 */
	webvtt_uint mode;

	/**
	 * I'm not sure 'finish' is actually needed at all.
	 */
	webvtt_bool finish;
	webvtt_uint flags;

	webvtt_state *top; /* Top parse state */
	webvtt_state astack[0x100];
	webvtt_state *stack; /* dynamically allocated stack, if 'astack' fills up */
	webvtt_uint stack_alloc; /* item capacity in 'stack' */

	/**
	 * Current cue
	 */
	webvtt_cue cue;

	/**
	 * line
	 */
	int truncate;
	webvtt_uint line_pos;
	webvtt_bytearray line_buffer;

	/**
	 * tokenizer
	 */
	webvtt_uint tstate;
	webvtt_uint token_pos;
	webvtt_byte token[0x100];
};

WEBVTT_INTERN webvtt_token webvtt_lex( webvtt_parser self, const webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint length, int finish );

#define BAD_TIMESTAMP(ts) ( ( ts ) == 0xFFFFFFFFFFFFFFFF )

#define ERROR(Code) \
do \
{ \
	if( !self->error || self->error(self->userdata,self->line,self->column,Code) < 0 ) \
		return WEBVTT_PARSE_ERROR; \
} while(0)
#define ERROR_AT_COLUMN(Code,Column) \
do \
{ \
	if( !self->error || self->error(self->userdata,self->line,(Column),Code) < 0 ) \
		return WEBVTT_PARSE_ERROR; \
} while(0)

#endif
