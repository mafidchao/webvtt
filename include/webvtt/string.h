#ifndef __WEBVTT_STRING_H__
#	define __WEBVTT_STRING_H__
#	include "util.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
 
/**
 * webvtt_wchar - A utf16 surrogate/character
 */
typedef webvtt_uint16 webvtt_wchar, *webvtt_wchar_ptr;

/**
 * webvtt_string - A buffer of utf16 characters
 */
typedef struct webvtt_string_t webvtt_string;
typedef struct webvtt_utf8_reader_t *webvtt_utf8_reader;
typedef struct webvtt_string_data_t webvtt_string_data;

struct
webvtt_string_data_t
{
	struct webvtt_refcount_t refs;
	webvtt_uint32 alloc;
	webvtt_uint32 length;
	webvtt_wchar *text;
	webvtt_wchar array[1];
};

struct
webvtt_string_t
{
	webvtt_string_data *d;
};

#	ifdef WEBVTT_INLINE
static WEBVTT_INLINE const webvtt_wchar *
webvtt_string_text(const webvtt_string *s)
{
	return s->d->text;
}

static WEBVTT_INLINE const webvtt_uint32
webvtt_string_length(const webvtt_string *s)
{
	return s->d->length;
}

static WEBVTT_INLINE const webvtt_uint32
webvtt_string_capacity(const webvtt_string *s)
{
	return s->d->alloc;
}

#	else
#		define webvtt_string_text(s) ((s)->d->text)
#		define webvtt_string_length(s) ((s)->d->length)
#		define webvtt_string_capacity(s) ((s)->d->alloc)
#	endif

struct
webvtt_utf8_reader_t
{
	webvtt_uint32 uc; /* ucs4 character */
	webvtt_uint32 bytes_left; /* remaining bytes in utf8 character sequence */
	webvtt_uint32 min_uc; /* minimum allowed codepoint given the number of bytes */
	webvtt_uint32 nc; /* number of non-characters encountered */
};

WEBVTT_EXPORT void webvtt_init_string( webvtt_string *result );
WEBVTT_EXPORT void webvtt_copy_string( webvtt_string *left, const webvtt_string *right );
WEBVTT_EXPORT webvtt_status webvtt_create_string( webvtt_uint32 alloc, webvtt_string *result );

/**
 * I'm sorry to impose COM-style stuff :(
 */
WEBVTT_EXPORT void webvtt_ref_string( webvtt_string *str );
WEBVTT_EXPORT void webvtt_release_string( webvtt_string *str );

/**
 * "Unshare" a shared string, meaning allocate a new copy of the string if it's shared,
 * so that we are not manipulating someone elses text
 */
WEBVTT_EXPORT webvtt_status webvtt_string_detach( webvtt_string *str );

/**
 * Methods for appending data to strings.
 */
WEBVTT_EXPORT webvtt_status webvtt_string_append_utf8( webvtt_string *str, const webvtt_byte *buffer,
	webvtt_uint *pos, webvtt_uint len, webvtt_utf8_reader reader );

WEBVTT_EXPORT webvtt_status webvtt_string_append( webvtt_string *str, const webvtt_wchar *to_append, webvtt_uint len );
WEBVTT_EXPORT webvtt_status webvtt_string_putc( webvtt_string *str, webvtt_wchar to_append );

#	ifdef WEBVTT_INLINE
static WEBVTT_INLINE webvtt_status
webvtt_string_append_string( webvtt_string *str, const webvtt_string *other )
{
	if( !str || !other )
	{
		return WEBVTT_INVALID_PARAM;
	}
	return webvtt_string_append( str, webvtt_string_text( other ), webvtt_string_length( other ) );
}	 
#	else
#		define webvtt_string_append_string(str,other) ( ((str) && (other)) ? (webvtt_string_append( (str), webvtt_string_text( other ), \
			webvtt_string_length( other ) ) : WEBVTT_INVALID_PARAM )
#	endif

/**
 * string lists
 */
struct
webvtt_string_list_t
{
	webvtt_uint alloc;
	webvtt_uint length;
	webvtt_string *items;
};
typedef struct webvtt_string_list_t webvtt_string_list, *webvtt_string_list_ptr;
 
WEBVTT_EXPORT webvtt_status webvtt_create_string_list( webvtt_string_list_ptr *string_list_pptr );
WEBVTT_EXPORT void webvtt_delete_string_list( webvtt_string_list_ptr *string_list_ptr );
WEBVTT_EXPORT webvtt_status webvtt_add_to_string_list( webvtt_string_list_ptr string_list_ptr, webvtt_string *string );

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif
