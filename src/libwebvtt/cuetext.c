#include "parser.h"

#define UTF16_AMPERSAND    (0x0026)
#define UTF16_LESSTHAN     (0x003C)
#define UTF16_GREATERTHAN  (0x003E)
#define UTF16_LEFTTORIGHT  (0x200E)
#define UTF16_RIGHTTOLEFT  (0x200F)

/**
 * TODO:
 *
 * Finish cue-text tokenizer and parser so that validation of WebVTT cue-text
 * is a possibility.
 */

/**
 * ERROR macro used for webvtt_parse_cuetext
 */
#undef ERROR
#define ERROR(code) \
do \
{ \
	if( self->error ) \
		if( self->error( self->userdata, line, col, code ) < 0 ) \
			return WEBVTT_PARSE_ERROR; \
} while(0)

webvtt_status
webvtt_parse_cuetext( webvtt_parser self, webvtt_uint line, const webvtt_wchar *pch,
	const webvtt_uint len, webvtt_node *pnode )
{
	if( !pch )
	{
		return WEBVTT_INVALID_PARAM;
	}
	
	/**
	 * Routine not implemented yet.
	 */
	return WEBVTT_NOT_SUPPORTED;
}