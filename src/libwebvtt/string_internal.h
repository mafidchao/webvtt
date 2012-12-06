#ifndef __INTERN_STRING_H__
#	define __INTERN_STRING_H__
#	include <webvtt/string.h>

#	define UTF16_AMPERSAND       (0x0026)
#	define UTF16_LESS_THAN       (0x003C)
#	define UTF16_GREATER_THAN    (0x003E)
#	define UTF16_LEFT_TO_RIGHT   (0x200E)
#	define UTF16_RIGHT_TO_LEFT   (0x200F)
#	define UTF16_NO_BREAK_SPACE  (0x00A0)
#	define UTF16_NULL_BYTE       (0x0000)
#	define UTF16_SEMI_COLON      (0x003B)
#	define UTF16_TAB             (0x0009)
#	define UTF16_FORM_FEED       (0x000C)
#	define UTF16_LINE_FEED       (0x000A)
#	define UTF16_CARRIAGE_RETURN (0x000D)
#	define UTF16_FULL_STOP       (0x002E)
#	define UTF16_SOLIDUS         (0x002F)
#	define UTF16_SPACE           (0x0020)
#	define UTF16_DIGIT_ZERO      (0x0030)
#	define UTF16_DIGIT_NINE      (0x0039)

#	define UTF16_CAPITAL_A       (0x0041)
#	define UTF16_CAPITAL_Z       (0x005A)

#	define UTF16_A               (0x0061)
#	define UTF16_B               (0x0062)
#	define UTF16_C               (0x0063)
#	define UTF16_D               (0x0064)
#	define UTF16_E               (0x0065)
#	define UTF16_F               (0x0066)
#	define UTF16_G               (0x0067)
#	define UTF16_H               (0x0068)
#	define UTF16_I               (0x0069)
#	define UTF16_J               (0x006A)
#	define UTF16_K               (0x006B)
#	define UTF16_L               (0x006C)
#	define UTF16_M               (0x006D)
#	define UTF16_N               (0x006E)
#	define UTF16_O               (0x006F)
#	define UTF16_P               (0x0070)
#	define UTF16_Q               (0x0071)
#	define UTF16_R               (0x0072)
#	define UTF16_S               (0x0073)
#	define UTF16_T               (0x0074)
#	define UTF16_U               (0x0075)
#	define UTF16_V               (0x0076)
#	define UTF16_W               (0x0077)
#	define UTF16_X               (0x0078)
#	define UTF16_Y               (0x0079)
#	define UTF16_Z               (0x007A)

#	ifdef WEBVTT_INLINE
#		define __WEBVTT_STRING_INLINE WEBVTT_INLINE
#	else
#		define __WEBVTT_STRING_INLINE
#	endif

static __WEBVTT_STRING_INLINE int
webvtt_isalpha( webvtt_wchar ch )
{
	return ( ( ( ch >= UTF16_CAPITAL_A ) && ( ch <= UTF16_CAPITAL_Z ) ) || ( ( ch >= UTF16_A ) && ( ch <= UTF16_Z ) ) );
}
static __WEBVTT_STRING_INLINE int
webvtt_isdigit( webvtt_wchar ch )
{
	return ( ( ch >= UTF16_DIGIT_ZERO ) && ( ch <= UTF16_DIGIT_NINE ) );
}

static __WEBVTT_STRING_INLINE int
webvtt_isalphanum( webvtt_wchar ch )
{
	return ( webvtt_isalpha( ch ) || webvtt_isdigit( ch ) );
}

static __WEBVTT_STRING_INLINE int
webvtt_iswhite( webvtt_wchar ch )
{
	return ( ( ch == UTF16_CARRIAGE_RETURN ) || ( ch == UTF16_LINE_FEED ) || ( ch == UTF16_FORM_FEED ) 
			|| ( ch == UTF16_TAB ) || ( ch == UTF16_SPACE ) ) ;
}

/**
 * This will only work on null-terminated strings, remember that!
 */
static __WEBVTT_STRING_INLINE void
webvtt_skipwhite( webvtt_wchar **position_pptr )
{
	webvtt_wchar *p = *position_pptr;
	while( *p && webvtt_iswhite(*p) )
	{
		++p;
	}
	*position_pptr = p;
}

#	undef __WEBVTT_STRING_INLINE
#endif
