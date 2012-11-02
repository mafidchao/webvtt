#ifndef __WEBVTT_BYTEARRAY_H__
#	define __WEBVTT_BYTEARRAY_H__
#	include <webvtt/util.h>

#	ifndef WEBVTT_MAX_LINE
#		define WEBVTT_MAX_LINE 0x10000
#	endif

/**
 * webvtt_string - A buffer of utf16 characters
 */
typedef struct webvtt_bytearray_t *webvtt_bytearray;

/**
 * These objects are NOT reference counted, they
 * are not meant to be shared.
 *
 * If this is required by mozilla, it can be added.
 */
struct
webvtt_bytearray_t
{
	webvtt_uint32 alloc;
	webvtt_uint32 length;
	webvtt_byte *text;
	webvtt_byte array[1];
};

webvtt_status webvtt_bytearray_new( webvtt_uint32 alloc, webvtt_bytearray *ppstr );
void webvtt_bytearray_delete( webvtt_bytearray *pstr );
int webvtt_bytearray_getline( webvtt_bytearray *ppstr, const webvtt_byte *buffer,
	webvtt_uint *pos, webvtt_uint len, int *truncate );
webvtt_status webvtt_bytearray_putc( webvtt_bytearray *ppstr, webvtt_byte ch );
#endif