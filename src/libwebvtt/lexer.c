#include "parser.h"

/**
 * There are probably enough jumps and stack pops here to fill up quite a few caches but it may still
 * be much smaller than a gigantic table-based solution.
 *
 * TODO: Replace all char literals with hex values, just in case compiling on a machine which uses an
 * incompatible character set
 */
#define BACKUP() do { --self->bytes; --(*pos); self->token[ --self->token_pos ] = 0; self->tstate = T_INITIAL; } while(0)
#define BEGIN_STATE(state) case state: {
#define END_STATE } break;
#define STATE_IF(X,State) case X: self->tstate = State; break
#define TOKEN_IF(X,Token) case X: self->tstate = T_INITIAL; return Token; break
#define TOKEN_IFX(X,Token,Actions) case X: Actions self->tstate = T_INITIAL; return Token; break
#define TOKEN_IF_WSNL(tok) do { if( (c == 0x0D) || (c == 0x0A) || (c == 0x20) || (c == 0x09) ) { BACKUP(); return tok; } } while(0)
#define IF_DIGIT if( c >= '0' && c <= '9' ) {
#define DO_STATE(State) self->tstate = State; continue
#define SWITCHX(actions) switch(c) { actions }
#define BEGIN_BYTE switch(c) {
#define END_BYTE default: BACKUP(); return BADTOKEN; } break;
#define END_BYTE_ }
#define DEFAULT(actions) default: { actions } break;
#define ELSE } else {
#define ENDIF }
#define RESET self->column = 0; self->token_pos = 0; self->tstate = T_INITIAL; self->token[0] = 0
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
	T_MIDDLE4, T_END0, T_END1, T_TIMESTAMP1, T_TIMESTAMP2, T_TIMESTAMP3, T_TIMESTAMP4, T_TIMESTAMP5
};

webvtt_token
webvtt_lex( webvtt_parser self, webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint length, int finish )
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
				IF_DIGIT
					DO_STATE(T_DIGIT0);
				ELSE
					BEGIN_BYTE
						STATE_IF(0xEF,T_BOM0);
						STATE_IF('W',T_WEBVTT0);
						STATE_IF('-',T_DASH0);
						STATE_IF(CR,T_NEWLINE0);
						TOKEN_IFX(LF,NEWLINE,self->line++;self->column=0;);
						STATE_IF(' ',T_WHITESPACE);
						STATE_IF('\t',T_WHITESPACE);
						TOKEN_IF('.',FULL_STOP);
						STATE_IF('p',T_POSITION0);
						STATE_IF('a',T_ALIGN0);
						STATE_IF('l',T_L0);
						STATE_IF('v',T_VERTICAL0);
						STATE_IF('r',T_RL0);
						STATE_IF('s',T_S0);
						STATE_IF('m',T_MIDDLE0);
						STATE_IF('e',T_END0);
					END_BYTE
				ENDIF
			END_STATE
			BEGIN_STATE(T_BOM0)
				BEGIN_BYTE
					STATE_IF(0xBB,T_BOM1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_BOM1)
				if( c == 0xBF && self->bytes == 3 ) 
				{ 
					/* skip BOM if it is first in file */
					RESET; 
				}
				else
				BEGIN_BYTE
					TOKEN_IF(0xBF,BOM);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_WEBVTT0)
				BEGIN_BYTE
					STATE_IF('E',T_WEBVTT1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_WEBVTT1)
				BEGIN_BYTE
					STATE_IF('B',T_WEBVTT2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_WEBVTT2)
				BEGIN_BYTE
					STATE_IF('V',T_WEBVTT3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_WEBVTT3)
				BEGIN_BYTE
					STATE_IF('T',T_WEBVTT4);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_WEBVTT4)
				BEGIN_BYTE
					STATE_IF('T',T_WEBVTT5);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_WEBVTT5)
				TOKEN_IF_WSNL(WEBVTT);
			END_STATE
			BEGIN_STATE(T_DASH0)
				IF_DIGIT
					DO_STATE(T_DIGIT0);
				ELSE
					BEGIN_BYTE
						STATE_IF('-',T_SEP1);
					END_BYTE
				ENDIF
			END_STATE
			BEGIN_STATE(T_SEP1)
				BEGIN_BYTE
					TOKEN_IF('>',SEPARATOR);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_DIGIT0)
				if(self->token_pos == sizeof(self->token) - 1 ) 
				{
					return INTEGER;
				}
				IF_DIGIT
					DO_STATE(T_DIGIT0);
				ELSE
					BEGIN_BYTE
						STATE_IF(':',T_TIMESTAMP1);
						TOKEN_IF('%',PERCENTAGE);
						DEFAULT(BACKUP(); return INTEGER;)
					END_BYTE_
				ENDIF
			END_STATE
			BEGIN_STATE(T_NEWLINE0)
				BEGIN_BYTE
					TOKEN_IFX(LF,NEWLINE,self->line++;self->column=0;);
					DEFAULT(BACKUP(); self->line++; self->column=0; return NEWLINE;);
				END_BYTE_
			END_STATE
			BEGIN_STATE(T_WHITESPACE)
				BEGIN_BYTE
					STATE_IF(' ',T_WHITESPACE);
					STATE_IF('\t',T_WHITESPACE);
					DEFAULT(BACKUP(); return WHITESPACE;);
				END_BYTE_
			END_STATE
			BEGIN_STATE(T_POSITION0)
				BEGIN_BYTE
					STATE_IF('o',T_POSITION1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_POSITION1)
				BEGIN_BYTE
					STATE_IF('s',T_POSITION2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_POSITION2)
				BEGIN_BYTE
					STATE_IF('i',T_POSITION3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_POSITION3)
				BEGIN_BYTE
					STATE_IF('t',T_POSITION4);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_POSITION4)
				BEGIN_BYTE
					STATE_IF('i',T_POSITION5);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_POSITION5)
				BEGIN_BYTE
					STATE_IF('o',T_POSITION6);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_POSITION6)
				BEGIN_BYTE
					STATE_IF('n',T_POSITION7);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_POSITION7)
				BEGIN_BYTE
					TOKEN_IF(':',POSITION);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_ALIGN0)
				BEGIN_BYTE
					STATE_IF('l',T_ALIGN1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_ALIGN1)
				BEGIN_BYTE
					STATE_IF('i',T_ALIGN2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_ALIGN2)
				BEGIN_BYTE
					STATE_IF('g',T_ALIGN3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_ALIGN3)
				BEGIN_BYTE
					STATE_IF('n',T_ALIGN4);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_ALIGN4)
				BEGIN_BYTE
					TOKEN_IF(':',ALIGN);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_L0)
				BEGIN_BYTE
					TOKEN_IF('r',LR);
					STATE_IF('i',T_LINE1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_LINE1)
				BEGIN_BYTE
					STATE_IF('n',T_LINE2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_LINE2)
				BEGIN_BYTE
					STATE_IF('e',T_LINE3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_LINE3)
				BEGIN_BYTE
					TOKEN_IF(':',LINE);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL0)
				BEGIN_BYTE
					STATE_IF('e',T_VERTICAL1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL1)
				BEGIN_BYTE
					STATE_IF('r',T_VERTICAL2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL2)
				BEGIN_BYTE
					STATE_IF('t',T_VERTICAL3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL3)
				BEGIN_BYTE
					STATE_IF('i',T_VERTICAL4);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL4)
				BEGIN_BYTE
					STATE_IF('c',T_VERTICAL5);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL5)
				BEGIN_BYTE
					STATE_IF('a',T_VERTICAL6);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL6)
				BEGIN_BYTE
					STATE_IF('l',T_VERTICAL7);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_VERTICAL7)
				BEGIN_BYTE
					TOKEN_IF(':',VERTICAL);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_RL0)
				BEGIN_BYTE
					TOKEN_IF('l',RL);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_S0)
				BEGIN_BYTE
					STATE_IF('t',T_START1);
					STATE_IF('i',T_SIZE1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_SIZE1)
				BEGIN_BYTE
					STATE_IF('z',T_SIZE2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_SIZE2)
				BEGIN_BYTE
					STATE_IF('e',T_SIZE3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_SIZE3)
				BEGIN_BYTE
					TOKEN_IF(':',SIZE);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_START1)
				BEGIN_BYTE
					STATE_IF('a',T_START2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_START2)
				BEGIN_BYTE
					STATE_IF('r',T_START3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_START3)
				BEGIN_BYTE
					TOKEN_IF('t',START);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_MIDDLE0)
				BEGIN_BYTE
					STATE_IF('i',T_MIDDLE1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_MIDDLE1)
				BEGIN_BYTE
					STATE_IF('d',T_MIDDLE2);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_MIDDLE2)
				BEGIN_BYTE
					STATE_IF('d',T_MIDDLE3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_MIDDLE3)
				BEGIN_BYTE
					STATE_IF('l',T_MIDDLE4);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_MIDDLE4)
				BEGIN_BYTE
					TOKEN_IF('e',MIDDLE);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_END0)
				BEGIN_BYTE
					STATE_IF('n',T_END1);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_END1)
				BEGIN_BYTE
					TOKEN_IF('d',END);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_TIMESTAMP1)
				IF_DIGIT DO_STATE(T_TIMESTAMP1); ENDIF
				BEGIN_BYTE
					STATE_IF(':',T_TIMESTAMP2);
					STATE_IF('.',T_TIMESTAMP3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_TIMESTAMP2)
				IF_DIGIT DO_STATE(T_TIMESTAMP2); ENDIF
				BEGIN_BYTE
					STATE_IF('.',T_TIMESTAMP3);
				END_BYTE
			END_STATE
			BEGIN_STATE(T_TIMESTAMP3)
				IF_DIGIT DO_STATE(T_TIMESTAMP4); 
				ELSE
					BACKUP();
					return BADTOKEN;
				ENDIF
			END_STATE
			BEGIN_STATE(T_TIMESTAMP4)
				IF_DIGIT DO_STATE(T_TIMESTAMP5); 
				ELSE
					BACKUP();
					return BADTOKEN;
				ENDIF
			END_STATE
			BEGIN_STATE(T_TIMESTAMP5)
				IF_DIGIT
					self->tstate = T_INITIAL; 
					return TIMESTAMP;
				ELSE
					BACKUP(); 
					return TIMESTAMP;
				ENDIF
			END_STATE
		}
	}
	if( self->tstate == T_DIGIT0 && finish )
	{
		self->tstate = T_INITIAL;
		return INTEGER;
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