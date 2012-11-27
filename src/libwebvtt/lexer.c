#include "parser_internal.h"

/**
 * There are probably enough jumps and stack pops here to fill up quite a few caches but it may still
 * be much smaller than a gigantic table-based solution.
 *
 * TODO: Replace all char literals with hex values, just in case compiling on a machine which uses an
 * incompatible character set
 */

#define ASCII_DIGIT case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
#define ASCII_WHITESPACE case 0x0D: case 0x0A: case 0x20: case 0x09:
#define ASCII_SPACE case 0x20:
#define ASCII_TAB case 0x09:
#define ASCII_CR case 0x0D:
#define ASCII_LF case 0x0A:

#define ASCII_DASH case 0x2D:
#define ASCII_PERIOD case 0x2E:
#define ASCII_GT case 0x3E:
#define ASCII_COLON case 0x3A:
#define ASCII_PERCENT case 0x25:

#define ASCII_0 case 0x30:
#define ASCII_1 case 0x31:
#define ASCII_2 case 0x32:
#define ASCII_3 case 0x33:
#define ASCII_4 case 0x34:
#define ASCII_5 case 0x35:
#define ASCII_6 case 0x36:
#define ASCII_7 case 0x37:
#define ASCII_8 case 0x38:
#define ASCII_9 case 0x39:

#define ASCII_a case 0x61:
#define ASCII_b case 0x62:
#define ASCII_c case 0x63:
#define ASCII_d case 0x64:
#define ASCII_e case 0x65:
#define ASCII_f case 0x66:
#define ASCII_g case 0x67:
#define ASCII_h case 0x68:
#define ASCII_i case 0x69:
#define ASCII_j case 0x6A:
#define ASCII_k case 0x6B:
#define ASCII_l case 0x6C:
#define ASCII_m case 0x6D:
#define ASCII_n case 0x6E:
#define ASCII_o case 0x6F:
#define ASCII_p case 0x70:
#define ASCII_q case 0x71:
#define ASCII_r case 0x72:
#define ASCII_s case 0x73:
#define ASCII_t case 0x74:
#define ASCII_u case 0x75:
#define ASCII_v case 0x76:
#define ASCII_w case 0x77:
#define ASCII_x case 0x78:
#define ASCII_y case 0x79:
#define ASCII_z case 0x7A:

#define ASCII_A case 0x41:
#define ASCII_B case 0x42:
#define ASCII_C case 0x43:
#define ASCII_D case 0x44:
#define ASCII_E case 0x45:
#define ASCII_F case 0x46:
#define ASCII_G case 0x47:
#define ASCII_H case 0x48:
#define ASCII_I case 0x49:
#define ASCII_J case 0x4A:
#define ASCII_K case 0x4B:
#define ASCII_L case 0x4C:
#define ASCII_M case 0x4D:
#define ASCII_N case 0x4E:
#define ASCII_O case 0x4F:
#define ASCII_P case 0x50:
#define ASCII_Q case 0x51:
#define ASCII_R case 0x52:
#define ASCII_S case 0x53:
#define ASCII_T case 0x54:
#define ASCII_U case 0x55:
#define ASCII_V case 0x56:
#define ASCII_W case 0x57:
#define ASCII_X case 0x58:
#define ASCII_Y case 0x59:
#define ASCII_Z case 0x5A:

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

#define BACKUP (*pos)--; self->token[--self->token_pos] = 0; self->tstate = T_INITIAL;
#define SET_STATE(X) self->tstate = X; break;
#define RETURN(X) self->tstate = T_INITIAL; return X;
#define SET_NEWLINE self->line++; self->column = 0; RETURN(NEWLINE)
#define CONTINUE continue;

#define RESET self->bytes = self->column = self->token_pos = 0; self->tstate = T_INITIAL;
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
	T_POSITION6, T_POSITION7, T_ALIGN0, T_ALIGN1, T_ALIGN2, T_ALIGN3, T_ALIGN4, T_L0, T_LINE1, T_LINE2, T_LINE3,
	T_VERTICAL0, T_VERTICAL1, T_VERTICAL2, T_VERTICAL3, T_VERTICAL4, T_VERTICAL5, T_VERTICAL6, T_VERTICAL7, T_RL0,
	T_S0, T_SIZE1, T_SIZE2, T_SIZE3, T_START1, T_START2, T_START3, T_MIDDLE0, T_MIDDLE1, T_MIDDLE2, T_MIDDLE3,
	T_MIDDLE4, T_END0, T_END1, T_TIMESTAMP1, T_TIMESTAMP2, T_TIMESTAMP3, T_TIMESTAMP4, T_TIMESTAMP5, T_RIGHT1, T_RIGHT2,
	T_RIGHT3, T_NOTE1, T_NOTE2, T_NOTE3, T_LEFT1, T_LEFT2, 
};

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
				ASCII_DIGIT { SET_STATE(T_DIGIT0) }
				ASCII_W  { SET_STATE(T_WEBVTT0) }
				ASCII_DASH { SET_STATE(T_DASH0) }
				UTF8_BOM0 { SET_STATE(T_BOM0) }
				ASCII_LF { SET_NEWLINE }
				ASCII_CR { SET_STATE(T_NEWLINE0) }
				ASCII_SPACE OR ASCII_TAB { SET_STATE(T_WHITESPACE) }
				ASCII_PERIOD { RETURN(FULL_STOP) }
				ASCII_COLON { RETURN(COLON) }
				ASCII_p { SET_STATE(T_POSITION0) }
				ASCII_a { SET_STATE(T_ALIGN0) }
				ASCII_l { SET_STATE(T_L0) }
				ASCII_v { SET_STATE(T_VERTICAL0) }
				ASCII_r { SET_STATE(T_RL0) }
				ASCII_s { SET_STATE(T_S0) }
				ASCII_m { SET_STATE(T_MIDDLE0) }
				ASCII_e { SET_STATE(T_END0) }
				ASCII_N { SET_STATE(T_NOTE1) }
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
				ASCII_E { SET_STATE(T_WEBVTT1) }
			END_STATE

			BEGIN_STATE(T_WEBVTT1)
				ASCII_B { SET_STATE(T_WEBVTT2) }
			END_STATE

			BEGIN_STATE(T_WEBVTT2)
				ASCII_V { SET_STATE(T_WEBVTT3) }
			END_STATE

			BEGIN_STATE(T_WEBVTT3)
				ASCII_T { SET_STATE(T_WEBVTT4) }
			END_STATE
		
			BEGIN_STATE(T_WEBVTT4)
				ASCII_T { RETURN(WEBVTT) }
			END_STATE
		
			BEGIN_STATE(T_DASH0)
				ASCII_DIGIT { SET_STATE(T_DIGIT0) }
				ASCII_DASH { SET_STATE(T_SEP1) }
			END_STATE

			BEGIN_STATE(T_SEP1)
				ASCII_GT { RETURN(SEPARATOR) }
			END_STATE

			BEGIN_STATE(T_DIGIT0)
				ASCII_DIGIT
				{
					OVERFLOW(INTEGER)
					SET_STATE(T_DIGIT0)
				}
				ASCII_COLON { SET_STATE(T_TIMESTAMP1) }
				ASCII_PERCENT { RETURN(PERCENTAGE) }
				DEFAULT { BACKUP AND RETURN(INTEGER) }
			END_STATE_EX

			BEGIN_STATE(T_NEWLINE0)
				ASCII_LF { SET_NEWLINE }
				DEFAULT { BACKUP AND SET_NEWLINE }
			END_STATE_EX

			BEGIN_STATE(T_WHITESPACE)
				ASCII_SPACE OR ASCII_TAB { OVERFLOW(WHITESPACE) SET_STATE(T_WHITESPACE) }
				DEFAULT { BACKUP RETURN(WHITESPACE) }
			END_STATE_EX

			BEGIN_STATE(T_POSITION0)
				ASCII_o { SET_STATE(T_POSITION1) }
			END_STATE

			BEGIN_STATE(T_POSITION1)
				ASCII_s { SET_STATE(T_POSITION2) }
			END_STATE

			BEGIN_STATE(T_POSITION2)
				ASCII_i { SET_STATE(T_POSITION3) }
			END_STATE

			BEGIN_STATE(T_POSITION3)
				ASCII_t { SET_STATE(T_POSITION4) }
			END_STATE

			BEGIN_STATE(T_POSITION4)
				ASCII_i { SET_STATE(T_POSITION5) }
			END_STATE

			BEGIN_STATE(T_POSITION5)
				ASCII_o { SET_STATE(T_POSITION6) }
			END_STATE

			BEGIN_STATE(T_POSITION6)
				ASCII_n { RETURN(POSITION) }
			END_STATE

			BEGIN_STATE(T_ALIGN0)
				ASCII_l { SET_STATE(T_ALIGN1) }
			END_STATE

			BEGIN_STATE(T_ALIGN1)
				ASCII_i { SET_STATE(T_ALIGN2) }
			END_STATE

			BEGIN_STATE(T_ALIGN2)
				ASCII_g { SET_STATE(T_ALIGN3) }
			END_STATE

			BEGIN_STATE(T_ALIGN3)
				ASCII_n { SET_STATE(T_ALIGN4) }
			END_STATE

			BEGIN_STATE(T_L0)
				ASCII_r { RETURN(LR) }
				ASCII_i { SET_STATE(T_LINE1) }
				ASCII_e { SET_STATE(T_LEFT1) }
			END_STATE

			BEGIN_STATE(T_LINE1)
				ASCII_n { SET_STATE(T_LINE2) }
			END_STATE

			BEGIN_STATE(T_LINE2)
				ASCII_e { RETURN(LINE) }
			END_STATE

			BEGIN_STATE(T_LEFT1)
				ASCII_f { SET_STATE(T_LEFT2) }
			END_STATE

			BEGIN_STATE(T_LEFT2)
				ASCII_t { RETURN(LEFT) }
			END_STATE

			BEGIN_STATE(T_VERTICAL0)
				ASCII_e { SET_STATE(T_VERTICAL1) }
			END_STATE

			BEGIN_STATE(T_VERTICAL1)
				ASCII_r { SET_STATE(T_VERTICAL2) }
			END_STATE

			BEGIN_STATE(T_VERTICAL2)
				ASCII_t { SET_STATE(T_VERTICAL3) }
			END_STATE

			BEGIN_STATE(T_VERTICAL3)
				ASCII_i { SET_STATE(T_VERTICAL4) }
			END_STATE

			BEGIN_STATE(T_VERTICAL4)
				ASCII_c { SET_STATE(T_VERTICAL5) }
			END_STATE

			BEGIN_STATE(T_VERTICAL5)
				ASCII_a { SET_STATE(T_VERTICAL6) }
			END_STATE

			BEGIN_STATE(T_VERTICAL6)
				ASCII_l { RETURN(VERTICAL) }
			END_STATE
			
			BEGIN_STATE(T_RL0)
				ASCII_l { RETURN(RL) }
				ASCII_i { SET_STATE(T_RIGHT1) }
			END_STATE

			BEGIN_STATE(T_RIGHT1)
				ASCII_g { SET_STATE(T_RIGHT2) }
			END_STATE

			BEGIN_STATE(T_RIGHT2)
				ASCII_h { SET_STATE(T_RIGHT3) }
			END_STATE

			BEGIN_STATE(T_RIGHT3)
				ASCII_t { RETURN(RIGHT) }
			END_STATE

			BEGIN_STATE(T_S0)
				ASCII_t { SET_STATE(T_START1) }
				ASCII_i { SET_STATE(T_SIZE1) }
			END_STATE

			BEGIN_STATE(T_SIZE1)
				ASCII_z { SET_STATE(T_SIZE2) }
			END_STATE

			BEGIN_STATE(T_SIZE2)
				ASCII_e { RETURN(SIZE) }
			END_STATE

			BEGIN_STATE(T_START1)
				ASCII_a { SET_STATE(T_START2) }
			END_STATE

			BEGIN_STATE(T_START2)
				ASCII_r { SET_STATE(T_START3) }
			END_STATE

			BEGIN_STATE(T_START3)
				ASCII_t { RETURN(START) }
			END_STATE

			BEGIN_STATE(T_MIDDLE0)
				ASCII_i { SET_STATE(T_MIDDLE1) }
			END_STATE

			BEGIN_STATE(T_MIDDLE1)
				ASCII_d { SET_STATE(T_MIDDLE2) }
			END_STATE

			BEGIN_STATE(T_MIDDLE2)
				ASCII_d { SET_STATE(T_MIDDLE3) }
			END_STATE

			BEGIN_STATE(T_MIDDLE3)
				ASCII_l { SET_STATE(T_MIDDLE4) }
			END_STATE

			BEGIN_STATE(T_MIDDLE4)
				ASCII_e { RETURN(MIDDLE) }
			END_STATE

			BEGIN_STATE(T_END0)
				ASCII_n { SET_STATE(T_END1) }
			END_STATE

			BEGIN_STATE(T_END1)
				ASCII_d { RETURN(END) }
			END_STATE

			BEGIN_STATE(T_TIMESTAMP1)
				ASCII_DIGIT
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP1)
				}
				ASCII_COLON
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP2)
				}
				ASCII_PERIOD
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP3)
				}
			END_STATE

			BEGIN_STATE(T_TIMESTAMP2)
				ASCII_DIGIT
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP2)
				}
				ASCII_PERIOD
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP3)
				}
			END_STATE

			BEGIN_STATE(T_TIMESTAMP3)
				ASCII_DIGIT
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP4)
				}
			END_STATE
				
			BEGIN_STATE(T_TIMESTAMP4)
				ASCII_DIGIT
				{
					OVERFLOW(BADTOKEN)
					SET_STATE(T_TIMESTAMP5)
				}
			END_STATE

			BEGIN_STATE(T_TIMESTAMP5)
				ASCII_DIGIT
				{
					OVERFLOW(BADTOKEN)
					RETURN(TIMESTAMP)
				}
			END_STATE

			BEGIN_STATE(T_NOTE1)
				ASCII_O { SET_STATE(T_NOTE2) }
			END_STATE
			
			BEGIN_STATE(T_NOTE2)
				ASCII_T { SET_STATE(T_NOTE3) }
			END_STATE

			BEGIN_STATE(T_NOTE3)
				ASCII_E { RETURN(NOTE) }
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
		}
	}
	return self->token_pos ? UNFINISHED : BADTOKEN;
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
