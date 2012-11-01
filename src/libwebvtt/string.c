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

#include <webvtt/string.h>
#include <string.h>
#include <limits.h>

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


/**
 * Allocate new string.
 */
webvtt_status
webvtt_string_new( webvtt_uint32 alloc, webvtt_string *ppstr )
{
	webvtt_string s;
	if( !ppstr )
	{
		return WEBVTT_INVALID_PARAM;
	}
	s = (webvtt_string)webvtt_alloc( sizeof(struct webvtt_string_t) + (alloc*sizeof(webvtt_wchar)) );
	if( !s )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	
	s->alloc = alloc;
	s->length = 0;
	s->text = s->array;
	s->text[0] = 0;
	*ppstr = s;
	return WEBVTT_SUCCESS;
}

/**
 * Delete string
 */
void
webvtt_string_delete( webvtt_string pstr )
{
	if( pstr )
	{
		webvtt_free( pstr );
	}
}

/**
 * Reallocate string.
 */
static webvtt_status
grow( webvtt_uint need, webvtt_string *ppstr )
{
	/**
	 * Grow to at least 'need' characters. Power of 2 growth.
	 */
	/**
	 * 4096
	 */
	static const webvtt_uint page = 0x1000;
	webvtt_uint32 n;
	webvtt_string p = *ppstr, s;
	webvtt_uint32 grow = sizeof(*p) + sizeof(webvtt_wchar) * (p->length + need);
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
	s = (webvtt_string)webvtt_alloc( n );
	if( !s )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	s->alloc = (n - sizeof(*p)) / sizeof(webvtt_wchar);
	s->length = p->length;
	s->text = s->array;
	memcpy( s->text, p->text, sizeof(webvtt_wchar) * p->length );
	s->text[ s->length ] = 0;
	*ppstr = s;
	webvtt_free( p );
	return WEBVTT_SUCCESS;
}

/**
 * Helper macro for growing strings.
 */
#define GROW(nchar) \
	do \
	{ \
		webvtt_uint need = (webvtt_uint)(nchar); \
		if( (s->length + need) >= s->alloc ) \
		{ \
			if( (result = grow( need, ppstr )) != WEBVTT_SUCCESS ) \
			{ \
				goto _end; \
			} \
			s = *ppstr; \
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
#define PUTC(ch) s->text[ s->length++ ] = (webvtt_wchar)(ch)
webvtt_status
webvtt_string_append_utf8( webvtt_string *ppstr, 
							const webvtt_byte *buf, 
							webvtt_uint *pos, 
							webvtt_length len, 
							webvtt_utf8_reader r )
{
	webvtt_string s;
	webvtt_status result;
	webvtt_uint32 uc = 0, bytes_left = 0, nc = 0, min_uc = 0;
	const webvtt_byte *src, *end;
	if( !ppstr || !*ppstr || !buf || !pos )
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
	s = *ppstr;
	
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
				s->text[ s->length++ ] = (webvtt_wchar)(c);
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
				s->text[ s->length++ ] = (webvtt_wchar)(REPLACEMENT_CHAR);
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
						s->text[ s->length++ ] = (webvtt_wchar)(uc);
					}
					else
					{
						/* write out the surrogates */
						GROW(2);
						uc -= HALF_BASE;
						s->text[ s->length++ ] = (webvtt_wchar)( (uc >> HALF_SHIFT) + SURROGATE_HIGH_START );
						s->text[ s->length++ ] = (webvtt_wchar)( (uc & HALF_MASK) + SURROGATE_LOW_START );
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
	s->text[ s->length ] = 0x0000;
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