#include "cue_testfixture"
class CueSettingLine : public CueTest { };

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * U+002D '-', followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9') each positioned correctly.
 *
 * testing multiple digits at the center of the range
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,DoubleDigit)
{
	loadVtt( "cue-settings/line/double-digit.vtt", 1 );
	ASSERT_EQ( 54, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * U+002D '-', followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9') each positioned correctly.
 *
 * testing multiple digits at the upper boundary of the range
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,DoubleDigitHighBoundary)
{
	loadVtt( "cue-settings/line/double-digit-high-boundary.vtt", 1 );
	ASSERT_EQ( 99, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * U+002D '-', followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9') each positioned correctly.
 *
 * testing multiple digits at the lower boundary of the range
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,DoubleDigitLowBoundary)
{
	loadVtt( "cue-settings/line/double-digit-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9'), each positioned correctly.
 *
 * testing multiple digits at the center of the range, negated
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,DoubleDigitNegative)
{
	loadVtt( "cue-settings/line/double-digit-negative.vtt", 1 );
	ASSERT_EQ( -54, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9'), each positioned correctly.
 *
 * testing multiple digits at the upper boundary of the range, negated
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,DoubleDigitNegativeHighBoundary)
{
	loadVtt( "cue-settings/line/double-digit-negative-high-boundary.vtt", 1 );
	ASSERT_EQ( -99, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9'), each positioned correctly.
 *
 * testing multiple digits at the lower boundary of the range, negated
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,DoubleDigitNegativeLowBoundary)
{
	loadVtt( "cue-settings/line/double-digit-negative-low-boundary.vtt", 1 );
	ASSERT_EQ( -00, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * 1 or more ASCII digits (U+0030-U+0039 '0'-'9') followed by U+0025 '%', each positioned correctly.
 *
 * the digit characters are in the middle of the allowed digit characters range.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,DoubleDigitPercentage)
{
	loadVtt( "cue-settings/line/double-digit-pct.vtt", 1 );
	ASSERT_EQ( 54, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * 1 or more ASCII digits (U+0030-U+0039 '0'-'9') followed by U+0025 '%', each positioned correctly.
 *
 * the digit characters are at the upper edge of the allowed digit characters range.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,DoubleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/line/double-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 99, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * 1 or more ASCII digits (U+0030-U+0039 '0'-'9') followed by U+0025 '%', each positioned correctly.
 *
 * the digit characters are at the lower edge of the allowed digit characters range.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,DoubleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/line/double-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * U+002D '-', followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9') each positioned correctly.
 *
 * testing single digit at the center of the range
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,SingleDigit)
{
	loadVtt( "cue-settings/line/single-digit.vtt", 1 );
	ASSERT_EQ( 5, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * U+002D '-', followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9') each positioned correctly.
 *
 * testing single digit at the upper boundary of the range
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,SingleDigitHighBoundary)
{
	loadVtt( "cue-settings/line/single-digit-high-boundary.vtt", 1 );
	ASSERT_EQ( 9, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * U+002D '-', followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9') each positioned correctly.
 *
 * testing single digit at the lower boundary of the range
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,SingleDigitLowBoundary)
{
	loadVtt( "cue-settings/line/single-digit-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9'), each positioned correctly.
 *
 * testing single digit at the center boundary of the range, negated
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,SingleDigitNegative)
{
	loadVtt( "cue-settings/line/single-digit-negative.vtt", 1 );
	ASSERT_EQ( -5, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9'), each positioned correctly.
 *
 * testing single digit at the upper boundary of the range, negated
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,SingleDigitNegativeHighBoundary)
{
	loadVtt( "cue-settings/line/single-digit-negative-high-boundary.vtt", 1 );
	ASSERT_EQ( -9, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * followed by 1 or more ASCII digits (U+0030-U+0039 '0'-'9'), each positioned correctly.
 *
 * testing single digit at the lower boundary of the range, negated
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a line number
 *		1. Optionally a U+002D HYPHEN-MINUS character (-).
 *		2. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 */
TEST_F(CueSettingLine,SingleDigitNegativeLowBoundary)
{
	loadVtt( "cue-settings/line/single-digit-negative-low-boundary.vtt", 1 );
	ASSERT_EQ( -0, getCue( 0 ).lineNumber() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * 1 ASCII digits (U+0030-U+0039 '0'-'9') followed by U+0025 '%', each positioned correctly.
 *
 * the digit character is in the middle of the allowed digit characters range.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,SingleDigitPercentage)
{
	loadVtt( "cue-settings/line/single-digit-pct.vtt", 1 );
	ASSERT_EQ( 5, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * 1 ASCII digits (U+0030-U+0039 '0'-'9') followed by U+0025 '%', each positioned correctly.
 *
 * the digit character is at the upper edge of the allowed digit characters range.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,SingleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/line/single-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 9, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a single "line" setting with U+003A ':', 
 * 1 ASCII digits (U+0030-U+0039 '0'-'9') followed by U+0025 '%', each positioned correctly.
 *
 * the digit character is at the lower edge of the allowed digit characters range.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,SingleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/line/single-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Test if parser fails when an unknown keyword is used for the otherwise correct 'line' cue setting.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,BadKeyword)
{
	loadVtt( "cue-settings/line/bad-keyword.vtt", 1 );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 25, err.column() );
}

/**
 * Test if parser fails when the key/value delimiter is incorrect for an otherwise correct 'line' cue setting.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,BadDelimiter)
{
	loadVtt( "cue-settings/line/bad-delimiter.vtt", 1 );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING_DELIMITER error on the 29th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING_DELIMITER, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 29, err.column() );
}

/**
 * Test if parser fails when the 'line' setting value (for a percentage value) does not contain a numeric
 * percentage made up of characters in the U+0030 - U+0039 range.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,BadValue)
{
	loadVtt( "cue-settings/line/bad-value.vtt", 1 );
	const Error& err = getError( 0 );

	/**
	 * We're expecting a WEBVTT_LINE_BAD_VALUE error on the 30th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_LINE_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 30, err.column() );
}

/**
 * Test if parser fails when the 'line' setting value has an incorrect character
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,BadValueSuffix)
{
	loadVtt( "cue-settings/line/bad-value-suffix.vtt", 1 );
	const Error& err = getError( 0 );

	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING_DELIMITER error on the 32nd column of the 3rd line
	 *
	 * Should this be a "*_BAD_VALUE" error? It does find a valid INTEGER token, so technically, the
	 * 'line' setting is perfectly valid. The real error is the garbage on the end of it.
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING_DELIMITER, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 32, err.column() );
}

/**
 * Test if parser fails when the key/value delimiter is not present
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,WhitespaceDelimiter)
{
	loadVtt( "cue-settings/line/bad-whitespace-delimiter.vtt", 1 );
	const Error& err = getError( 0 );

	/**
	 * We're expecting a WEBVTT_MISSING_CUESETTING_DELIMITER error on the 29th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_MISSING_CUESETTING_DELIMITER, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 29, err.column() );
}

/**
 * Test if parser fails when the key/value delimiter is preceded by whitespace.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,BadWhitespaceBeforeDelimiter)
{
	loadVtt( "cue-settings/line/bad-whitespace-before-delimiter.vtt", 1 );
	const Error& err = getError( 0 );

	/**
	 * We're expecting a WEBVTT_UNEXPECTED_WHITESPACE error on the 29th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_UNEXPECTED_WHITESPACE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 29, err.column() );
}

/**
 * Test if parser fails when the key/value delimiter is next to a space.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-line-position-cue-setting (09/28/2012):
 *	1. The string "line".
 *	2. A U+003A COLON character (:).
 *	3.
 *		To represent a specific position relative to the video frame
 *		1. One or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9).
 *		2. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingLine,BadWhitespaceAfterDelimiter)
{
	loadVtt( "cue-settings/line/bad-whitespace-after-delimiter.vtt", 1 );
	const Error& err = getError( 0 );

	/**
	 * We're expecting a WEBVTT_UNEXPECTED_WHITESPACE error on the 30th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_UNEXPECTED_WHITESPACE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 30, err.column() );
}
