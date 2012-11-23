#include "cue_testfixture"
class CueSettingSize : public CueTest { };

/**
 * Successfully parse a properly formatted single digit percentage 'size:5%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,SingleDigitPercentage)
{
	loadVtt( "cue-settings/size/single-digit-pct.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 5, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'size:9%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,SingleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/size/single-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 9, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'size:0%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,SingleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/size/single-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 0, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'size:50%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DoubleDigitPercentage)
{
	loadVtt( "cue-settings/size/double-digit-pct.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 50, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'size:99%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DoubleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/size/double-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 99, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'size:00%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DoubleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/size/double-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 00, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'size:555%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,TripleDigitPercentage)
{
	loadVtt( "cue-settings/size/triple-digit-pct.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 555, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'size:999%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,TripleDigitPercentageHighBoundary)
{
	loadVtt( "cue-settings/size/triple-digit-pct-high-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 999, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'size:000%'
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,TripleDigitPercentageLowBoundary)
{
	loadVtt( "cue-settings/size/double-digit-pct-low-boundary.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_EQ( 000, getCue( 0 ).sizePercentage() );
}

/**
 * Test that we consider it an error if we encounter a 'size' value which is outside of the ASCII
 * digit range (0x30-0x39) - In this case, fail on 0x3A (COLON)
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DISABLED_AsciiDigitBeyondHighBoundary)
{
	loadVtt( "cue-settings/size/above-0x39.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 30, err.column() );
}

/**
 * Test that we consider it an error if we encounter a 'size' value which is outside of the ASCII
 * digit range (0x30-0x39) - In this case, fail on 0x2F (FORWARD SLASH)
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DISABLED_AsciiDigitBeyondLowBoundary)
{
	loadVtt( "cue-settings/size/below-0x30.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 30, err.column() );
}

/**
 * Test that we consider it an error if the key:value delimiter U+003A COLON is omitted.
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DISABLED_NoDelimiter)
{
	loadVtt( "cue-settings/size/below-0x30.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
	 * This should be a different error, like WEBVTT_EXPECTED_CUESETTING_DELIMITER, or something.
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 25, err.column() );
}

/**
 * Test that we consider it an error if we encounter a value that is not a percentage
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DISABLED_NoPercentSign)
{
	loadVtt( "cue-settings/size/no-percent-sign.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 30th column of the 3rd line
	 * We can probably make this smarter, like WEBVTT_EXPECTED_PERCENTAGE or something
	 */
	ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 30, err.column() );
}

/**
 * Test that we consider it an error if we encounter a key:value pair where the delimiter is not
 * U+003A COLON
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-size-cue-setting (11/21/2012):
 * A WebVTT size cue setting consists of the following components, in the order given:
 *
 * 1. The string "size".
 * 2. A U+003A COLON character (:).
 * 3. One or more ASCII digits.
 * 4. A U+0025 PERCENT SIGN character (%).
 */
TEST_F(CueSettingSize,DISABLED_BadDelimiter)
{
	loadVtt( "cue-settings/size/bad-delimiter.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
	 * We can probably make this smarter, like WEBVTT_EXPECTED_CUESETTING_DELIMITER or something
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 25, err.column() );
}

