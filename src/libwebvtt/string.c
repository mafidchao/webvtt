/**
 * ICU License - ICU 1.8.1 and later
 *
 * COPYRIGHT AND PERMISSION NOTICE
 *
 * Copyright (c) 1995-2012 International Business Machines Corporation and others
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and *
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of the Software and that both the above
 * copyright notice(s) and this permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD
 * PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY
 * CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder shall not be used in advertising or
 * otherwise to promote the sale, use or other dealings in this Software without prior written authorization 
 * of the copyright holder.
 */
 
/**
 * As stated above, portions of this code are derived from ICU:
 * http://source.icu-project.org/repos/icu/icu/trunk/source/common/ucnv_u8.c
 * Specifically, routine void ucnv_toUnicode_UTF8
 *
 * As such, the entire file is MIT-licensed.
 */

#include "string_internal.h"
#include <stdlib.h>
#include <string.h>

#define REPLACEMENT_CHAR     (0xFFFD)
#define MAXIMUM_UCS2         (0x0000FFFF)
#define MAXIMUM_UTF          (0x0010FFFF)
#define MAXIMUM_UCS4         (0x7FFFFFFF)
#define HALF_SHIFT           (10)
#define HALF_BASE            (0x0010000)
#define HALF_MASK            (0x3FF)
#define SURROGATE_HIGH_START (0xD800)
#define SURROGATE_HIGH_END   (0xDBFF)
#define SURROGATE_LOW_START  (0xDC00)
#define SURROGATE_LOW_END    (0xDFFF)

/* -SURROGATE_LOW_START + HALF_BASE */
#define SURROGATE_LOW_BASE   (9216)

/* from http://source.icu-project.org/repos/icu/icu/trunk/source/common/unicode/utf8.h */
#define U8_IS_TRAIL(c) (((c)&0xc0)==0x80)

/* from http://source.icu-project.org/repos/icu/icu/trunk/source/common/unicode/utf.h */
#define U_IS_SURROGATE(c) (((c)&0xfffff800)==0xd800)

static webvtt_string_data empty_string =
{
	{ 1 },
	0,
	0,
	empty_string.array,
	{ 0x0000 }
};

WEBVTT_EXPORT void
webvtt_init_string( webvtt_string *result )
{
	if( result )
	{
		result->d = &empty_string;
		webvtt_ref( &result->d->refs );
	}
}

WEBVTT_EXPORT void
webvtt_copy_string( webvtt_string *left, const webvtt_string *right )
{
	if( left )
	{
		webvtt_string_data *d = left->d;
		if( right )
		{
			left->d = right->d;
		}
		else
		{
			left->d = &empty_string;
		}
		webvtt_ref( &left->d->refs );
		if( webvtt_deref( &d->refs ) == 0 )
		{
			/**
			 * We don't try to check if we're freeing a static string or not.
			 * Static strings should be initialized with a reference count of '1',
			 * and should be ref'd or deref'd properly.
			 *
			 * If this is difficult, use the C++ bindings!
			 */
			webvtt_free( d );
		}
	}
}

/**
 * "Detach" a shared string, so that it's safely mutable
 */
WEBVTT_EXPORT webvtt_status
webvtt_string_detach( /* in-out */ webvtt_string *str )
{
	webvtt_string_data *d, *q;
	if( !str )
	{
		return WEBVTT_INVALID_PARAM;
	}
	q = str->d;
	if( q->refs.value == 1 )
	{
		return WEBVTT_SUCCESS;
	}
	d = (webvtt_string_data *)webvtt_alloc( sizeof( webvtt_string_data ) + ( sizeof(webvtt_wchar) * str->d->alloc ) );
	d->refs.value = 1;
	d->text = d->array;
	d->alloc = q->alloc;
	d->length = q->length;
	memcpy( d->text, q->text, q->length );
	str->d = d;
	if( webvtt_deref(&q->refs) == 0 )
	{
		webvtt_free( q );
	}
	return WEBVTT_SUCCESS;
}


/**
 * Allocate new string.
 */
WEBVTT_EXPORT webvtt_status
webvtt_create_string( webvtt_uint32 alloc, webvtt_string *s )
{
	webvtt_string_data *d;
	if( !s )
	{
		return WEBVTT_INVALID_PARAM;
	}
	d = (webvtt_string_data *)webvtt_alloc( sizeof(webvtt_string_data) + (alloc*sizeof(webvtt_wchar)) );
	if( !d )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	
	d->alloc = alloc;
	d->length = 0;
	d->text = d->array;
	d->text[0] = 0;
	s->d = d;
	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status 
webvtt_string_from_utf8( webvtt_string *result, const webvtt_byte *buffer, webvtt_uint len )
{
	webvtt_uint pos = 0; 

	webvtt_init_string( result );

	if( !result )
		return WEBVTT_OUT_OF_MEMORY;

	return webvtt_string_append_utf8( result, buffer, &pos, len, 0 );
}

WEBVTT_EXPORT void
webvtt_ref_string( webvtt_string *str )
{
	if( str )
	{
		webvtt_ref( &str->d->refs );
	}
}

/**
 * Delete string
 */
WEBVTT_EXPORT void
webvtt_release_string( webvtt_string *str )
{
	if( str )
	{
		webvtt_string_data *d = str->d;
		str->d = &empty_string;
		webvtt_ref( &str->d->refs );
		if( d && webvtt_deref( &d->refs ) == 0 )
		{
			webvtt_free( d );
		}
	}
}

/**
 * Reallocate string.
 */
static webvtt_status
grow( webvtt_uint need, webvtt_string *str )
{
	/**
	 * Grow to at least 'need' characters. Power of 2 growth.
	 */
	/**
	 * 4096
	 */
	static const webvtt_uint page = 0x1000;
	webvtt_uint32 n;
	webvtt_string_data *p, *d = str->d;
	webvtt_uint32 grow = sizeof(*d) + ( sizeof(webvtt_wchar) * (d->length + need) );
	if( grow < page )
	{
		n = page;
		do
		{
			n = n / 2;
		} while( n > grow );
		if( n < 1<<6 )
		{
			n = 1 << 6;
		}
		else
		{
			n = n * 2;
		}
	}
	else
	{
		n = page;
		do
		{
			n = n * 2;
		} while ( n < grow );
	}
	p = (webvtt_string_data *)webvtt_alloc( n );
	if( !p )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}

	p->refs.value = 1;
	p->alloc = (n - sizeof(*p)) / sizeof(webvtt_wchar);
	p->length = d->length;
	p->text = p->array;
	memcpy( p->text, d->text, sizeof(webvtt_wchar) * p->length );
	p->text[ p->length ] = 0;
	str->d = p;
	if( webvtt_deref( &d->refs ) == 0 )
	{
		webvtt_free( d );
	}
	return WEBVTT_SUCCESS;
}

/**
 * Helper macro for growing strings.
 */
#define GROW(nchar) \
	do \
	{ \
		webvtt_uint need = (webvtt_uint)(nchar); \
		if( (str->d->length + need) >= str->d->alloc ) \
		{ \
			if( (result = grow( need, str )) != WEBVTT_SUCCESS ) \
			{ \
				goto _end; \
			} \
		} \
	} while(0)
	
static const webvtt_byte utf8_seqlen[256] = {
/*      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
/* 0 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0x00 - 0x7F: 1byte sequence */
/* 1 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0x80 - 0xBF: 0byte sequence -- Noncharacters? */
/* 2 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xC0 - 0xDF: 2byte sequence */
/* 3 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xE0 - 0xEF: 3byte sequence */
/* 4 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xF0 - 0xF7: 4byte sequence */
/* 5 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xF8 - 0xFB: 5byte sequence */
/* 6 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xFC - 0xFD: 6byte sequence */
/* 7 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xFE - 0xFF: 0byte sequence -- Noncharacters? */
/* 8 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
/* 9 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* A */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
/* B */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* C */ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
/* D */ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
/* E */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
/* F */ 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0
/* ----------------------------------------------------*/
};
static const webvtt_uint32 utf8_min_uc[] =
{ 0, 0, 0x80, 0x800, 0x10000, 0xffffffff, 0xffffffff };

/**
 * Append UTF8 text to string, reallocating as needed.
 */
#define PUTC(ch) str->d->text[ str->d->length++ ] = (webvtt_wchar)(ch)

WEBVTT_EXPORT webvtt_status
webvtt_string_append_utf8( webvtt_string *str, 
							const webvtt_byte *buf, 
							webvtt_uint *pos, 
							webvtt_length len, 
							webvtt_utf8_reader r )
{
	webvtt_status result;
	webvtt_uint32 uc = 0, bytes_left = 0, nc = 0, min_uc = 0;
	const webvtt_byte *src, *end;
	if( !str || !buf || !pos )
	{
		return WEBVTT_INVALID_PARAM;
	}
	if( r )
	{
		uc = r->uc;
		bytes_left = r->bytes_left;
		nc = r->nc;
		min_uc = r->min_uc;
	}
	
	src = buf + *pos;
	end = buf + len;
	/**
	 * Ensure that we have at least 'len' characters available.
	 */
	GROW(end - src);
	while( src < end )
	{
		webvtt_byte c = *(src)++;
		if( !bytes_left )
		{
			if( c < 0x80 )
			{
				/* ASCII character. */
				GROW(1);
				str->d->text[ str->d->length++ ] = (webvtt_wchar)(c);
			}
			else
			{
				/**
				 * retrieve number of remaining bytes required, and minimum codepoint for that
				 * number of bytes.
				 */
				uc = c;
				bytes_left = utf8_seqlen[c];
				min_uc = utf8_min_uc[bytes_left];
			}
		}
		else
		{
			if( !U8_IS_TRAIL(c) )
			{
				/**
				 * well something is wrong... let's add a replacement character and reset.
				 */
				GROW(1);
				str->d->text[ str->d->length++ ] = (webvtt_wchar)(REPLACEMENT_CHAR);
				bytes_left = 0;
				++nc;
				continue;
			}
			uc = (uc << 6) + uc;
			if( --bytes_left == 0 )
			{
				/**
				 * Legal UTF-8 byte sequences in Unicode 3.0.1 and up:
				 * - use only trail bytes after a lead byte (checked above)
				 * - use the right number of trail bytes for a given lead byte
				 * - encode a code point <= U+10ffff
				 * - use the fewest possible number of bytes for their code points
				 * - use at most 4 bytes (for i>=5 it is 0x10ffff<utf8_minChar32[])
				 *
				 * CESU-8 accomodation as skipped, as we are only dealing with external data.
				 */
				if( uc <= MAXIMUM_UTF && uc >= min_uc && !U_IS_SURROGATE(uc) )
				{
					/* Normal valid byte when the loop has not prematurely terminated */
					if( uc <= MAXIMUM_UCS2 )
					{
						/* fits in 16 bits */
						GROW(1);
						PUTC(uc);
					}
					else
					{
						/* write out the surrogates */
						GROW(2);
						uc -= HALF_BASE;
						PUTC( (uc >> HALF_SHIFT) + SURROGATE_HIGH_START );
						PUTC( (uc & HALF_MASK) + SURROGATE_LOW_START );
					}
				}
			}
		}
	}
_end:
	/**
	 * NULL-terminate the string (Should always be room for this as there is always one
	 * more 16bit character than 'alloc' indicates.
	 */
	str->d->text[ str->d->length ] = 0x0000;
	if( r )
	{
		r->uc = uc;
		r->min_uc = min_uc;
		r->bytes_left = bytes_left;
		r->nc += nc;
	}
	*pos = (webvtt_uint)(src - buf);
	return result;
}

WEBVTT_EXPORT webvtt_status 
webvtt_string_append( webvtt_string *str, const webvtt_wchar *to_append, webvtt_uint len )
{
	webvtt_status result;

	if( !to_append || !str )
		return WEBVTT_INVALID_PARAM;

	webvtt_string_detach( str );

	GROW(len);
	memcpy( str->d->text + str->d->length, to_append, sizeof(webvtt_wchar) * len );
	str->d->length += len;
	str->d->text[ str->d->length ] = 0;

	return WEBVTT_SUCCESS;
_end:
	return result;
}

WEBVTT_EXPORT webvtt_status 
webvtt_string_putc( webvtt_string *str, webvtt_wchar to_append )
{
	webvtt_status result;
	if( !str )
	{
		return WEBVTT_INVALID_PARAM;
	}

	if( WEBVTT_FAILED(result = webvtt_string_detach( str ) ) )
	{
		return result;
	}

	GROW(1);
	PUTC(to_append);
	str->d->text[ str->d->length ] = 0;
_end:
	return result;
}

/**
 * String lists
 */
WEBVTT_EXPORT webvtt_status 
webvtt_create_string_list( webvtt_string_list_ptr *result )
{
	webvtt_string_list_ptr list;
	if( !result )
	{
		return WEBVTT_INVALID_PARAM;
	}

	list = (webvtt_string_list_ptr)webvtt_alloc0( sizeof(*list) );

	if( !list )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}

	*result = list;

	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT void 
webvtt_delete_string_list( webvtt_string_list_ptr *list )
{
	webvtt_uint i;

	if( list && *list )
	{
		webvtt_string_list_ptr l = *list;
		*list = 0;
		if( l->items )
		{
			for( i = 0; i < l->length; i++ )
			{
				webvtt_release_string( &l->items[i] );
			}
			webvtt_free( l->items );
		}
		webvtt_free( l );
	}
}

WEBVTT_EXPORT webvtt_status 
webvtt_add_to_string_list( webvtt_string_list_ptr list, webvtt_string *str )
{
	if( !list || !str )
	{
		return WEBVTT_INVALID_PARAM;
	}

	if( list->length + 1 >= ( (list->alloc / 3) * 2 ) )
	{
		webvtt_string *arr, *old;
		list->alloc = list->alloc == 0 ? 8 : list->alloc * 2;
		arr = (webvtt_string *)webvtt_alloc0( sizeof(webvtt_string) * list->alloc );
		if( !arr )
		{
			return WEBVTT_OUT_OF_MEMORY;
		}
		memcpy( arr, list->items, sizeof(webvtt_string) * list->length );
		old = list->items;
		list->items = arr;
		webvtt_free( old );
	}
	
	list->items[list->length].d = str->d;
	webvtt_ref_string( list->items + list->length++ );
	return WEBVTT_SUCCESS;
}
