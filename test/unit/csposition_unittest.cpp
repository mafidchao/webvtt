#include "cue_testfixture"
class CueSettingPosition : public CueTest { };

/**
 * Successfully parse a properly formatted single digit percentage 'position:5%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,SingleDigitPercentage)
{
	loadVtt( "cue-settings/position/single-digit-pct.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 5, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'position:9%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,SingleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/position/single-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 9, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'position:0%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,SingleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/position/single-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 0, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'position:50%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,DoubleDigitPercentage)
{
	loadVtt( "cue-settings/position/double-digit-pct.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'position:99%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,DoubleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/position/double-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 99, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'position:00%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,DoubleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/position/double-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 00, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'position:555%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,TripleDigitPercentage)
{
	loadVtt( "cue-settings/position/triple-digit-pct.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 555, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'position:999%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,TripleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/position/triple-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 999, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'position:000%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,TripleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/position/double-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 000, getCue( 0 ).textPositionPercentage() );
}

/**
 * Test that we consider it an error if the key:value delimiter U+003A COLON is omitted.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,NoDelimiter)
{
	loadVtt( "cue-settings/position/no-delimiter.vtt", 1 );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_MISSING_CUESETTING_DELIMITER error on the 33rd column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_MISSING_CUESETTING_DELIMITER, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 33, err.column() );
}

/**
 * Test that we consider it an error if we encounter a value without a 'position' key.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,NoKeyword)
{
	loadVtt( "cue-settings/position/no-keyword.vtt", 1 );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_MISSING_CUESETTING_KEYWORD error on the 25th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_MISSING_CUESETTING_KEYWORD, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 25, err.column() );
}

/**
 * Test that we consider it an error if we encounter a value that is not a percentage
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,NoPercentSign)
{
	loadVtt( "cue-settings/position/no-percent-sign.vtt", 1 );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
	 * We can probably make this smarter, like WEBVTT_EXPECTED_PERCENTAGE or something
	 */
	ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 34, err.column() );
}

/**
 * Test that we consider it an error if we encounter a key:value pair where the delimiter is not
 * U+003A COLON
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,BadDelimiter)
{
	loadVtt( "cue-settings/position/bad-delimiter.vtt", 1 );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING_DELIMITER error on the 33rd column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING_DELIMITER, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 33, err.column() );
}

/**
 * Test that we consider it an error if we encounter a 'position' value which is outside of the ASCII
 * digit range (0x30-0x39) - In this case, fail on 0x3A (COLON)
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,AsciiDigitBeyondHighBoundary)
{
	loadVtt( "cue-settings/position/above-0x39.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 34, err.column() );
}

/**
 * Test that we consider it an error if we encounter a 'position' value which is outside of the ASCII
 * digit range (0x30-0x39) - In this case, fail on 0x2F (FORWARD SLASH)
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-text-position-cue-setting (11/21/2012):
 * A WebVTT text position cue setting consists of the following components, in the order given:
 * 1. The string "position".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingPosition,AsciiDigitBeyondLowBoundary)
{
	loadVtt( "cue-settings/position/below-0x30.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 34, err.column() );
}