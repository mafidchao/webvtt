#ifndef __WEBVTT_STRING_H__
#	define __WEBVTT_STRING_H__
#	include "util.h"
/**
 * webvtt_wchar - A utf16 surrogate/character
 */
typedef webvtt_uint16 webvtt_wchar;

/**
 * webvtt_string - A buffer of utf16 characters
 */
typedef struct webvtt_string_t *webvtt_string;

typedef struct webvtt_utf8_reader_t *webvtt_utf8_reader;

/**
 * These objects are NOT reference counted, they
 * are not meant to be shared.
 *
 * If this is required by mozilla, it can be added.
 */
struct
webvtt_string_t
{
	webvtt_uint32 alloc;
	webvtt_uint32 length;
	webvtt_wchar *text;
	webvtt_wchar array[1];
};

struct
webvtt_utf8_reader_t
{
	webvtt_uint32 uc; /* ucs4 character */
	webvtt_uint32 bytes_left; /* remaining bytes in utf8 character sequence */
	webvtt_uint32 min_uc; /* minimum allowed codepoint given the number of bytes */
	webvtt_uint32 nc; /* number of non-characters encountered */
};

webvtt_status webvtt_string_new( webvtt_uint32 alloc, webvtt_string *ppstr );
void webvtt_string_delete( webvtt_string pstr );
webvtt_status webvtt_string_append_utf8( webvtt_string *ppstr, const webvtt_byte *buffer,
	webvtt_uint *pos, webvtt_uint len, webvtt_utf8_reader reader );

#endif