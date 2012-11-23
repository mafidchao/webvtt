#include "cue_testfixture"
class CueSetting : public CueTest { };

/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of different types, 
 * delimited by U+0009 (tab)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-vertical-text-cue-setting (09/28/2012):
 *	The WebVTT cue settings part of a WebVTT cue consists of zero or more of the following components, in any order, separated from each other by one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters. Each component must not be included more than once per WebVTT cue settings string.
 */
TEST_F(CueSetting,MultipleCueSettings2Tab)
{
	loadVtt( "cue-settings/2-cue-settings-0x09.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
	ASSERT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of different types, 
 * delimited by U+0020 (space)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-vertical-text-cue-setting (09/28/2012):
 *	The WebVTT cue settings part of a WebVTT cue consists of zero or more of the following components, in any order, separated from each other by one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters. Each component must not be included more than once per WebVTT cue settings string.
 */
TEST_F(CueSetting,MultipleCueSettings2Space)
{
	loadVtt( "cue-settings/2-cue-settings-0x20.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
	ASSERT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of different types, 
 * delimited by a combination of U+0020 (space) and U+0009 (tab)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-vertical-text-cue-setting (09/28/2012):
 *	The WebVTT cue settings part of a WebVTT cue consists of zero or more of the following components, in any order, separated from each other by one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters. Each component must not be included more than once per WebVTT cue settings string.
 */
TEST_F(CueSetting,MultipleCueSettings2Mixed)
{
	loadVtt( "cue-settings/2-cue-settings-0x20.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
	ASSERT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (09/28/2012):
 *	A WebVTT cue consists of the following components, in the given order:
 *
 *	1. Optionally, a WebVTT cue identifier followed by a WebVTT line terminator.
 *	2. WebVTT cue timings.
 *	3. Optionally, one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters followed by WebVTT cue settings.
 *	4. A WebVTT line terminator.
 *	5. The cue payload: either WebVTT cue text, WebVTT chapter title text, or WebVTT metadata text.
 */
TEST_F(CueSetting,Delimiter0x20)
{
	loadVtt( "cue-settings/delimiter-0x20.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (09/28/2012):
 *	A WebVTT cue consists of the following components, in the given order:
 *
 *	1. Optionally, a WebVTT cue identifier followed by a WebVTT line terminator.
 *	2. WebVTT cue timings.
 *	3. Optionally, one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters followed by WebVTT cue settings.
 *	4. A WebVTT line terminator.
 *	5. The cue payload: either WebVTT cue text, WebVTT chapter title text, or WebVTT metadata text.
 */
TEST_F(CueSetting,Delimiter0x20Sequence)
{
	loadVtt( "cue-settings/delimiter-0x20-sequence.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (09/28/2012):
 *	A WebVTT cue consists of the following components, in the given order:
 *
 *	1. Optionally, a WebVTT cue identifier followed by a WebVTT line terminator.
 *	2. WebVTT cue timings.
 *	3. Optionally, one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters followed by WebVTT cue settings.
 *	4. A WebVTT line terminator.
 *	5. The cue payload: either WebVTT cue text, WebVTT chapter title text, or WebVTT metadata text.
 */
TEST_F(CueSetting,Delimiter0x09)
{
	loadVtt( "cue-settings/delimiter-0x09.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (09/28/2012):
 *	A WebVTT cue consists of the following components, in the given order:
 *
 *	1. Optionally, a WebVTT cue identifier followed by a WebVTT line terminator.
 *	2. WebVTT cue timings.
 *	3. Optionally, one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters followed by WebVTT cue settings.
 *	4. A WebVTT line terminator.
 *	5. The cue payload: either WebVTT cue text, WebVTT chapter title text, or WebVTT metadata text.
 */
TEST_F(CueSetting,Delimiter0x09Sequence)
{
	loadVtt( "cue-settings/delimiter-0x09-sequence.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (09/28/2012):
 *	A WebVTT cue consists of the following components, in the given order:
 *
 *	1. Optionally, a WebVTT cue identifier followed by a WebVTT line terminator.
 *	2. WebVTT cue timings.
 *	3. Optionally, one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters followed by WebVTT cue settings.
 *	4. A WebVTT line terminator.
 *	5. The cue payload: either WebVTT cue text, WebVTT chapter title text, or WebVTT metadata text.
 */
TEST_F(CueSetting,DelimiterMixed)
{
	loadVtt( "cue-settings/delimiter-mixed.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Test that the parser considers it an error if the same cue-setting is specified multiple
 * times in a single cue.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-settings (11/21/2012):
 *
 * The WebVTT cue settings part of a WebVTT cue consists of zero or more of the following 
 * components, in any order, separated from each other by one or more U+0020 SPACE characters 
 * or U+0009 CHARACTER TABULATION (tab) characters. Each component must not be included more than 
 * once per WebVTT cue settings string.
 */
TEST_F(CueSetting,DISABLED_SameCueSetting)
{
	loadVtt( "cue-settings/2-same-settings.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_VERTICAL_ALREADY_SET error on the 37th column of the 3rd line
	 * We can probably make this smarter, like WEBVTT_EXPECTED_CUESETTING_DELIMITER or something
	 */
	ASSERT_EQ( WEBVTT_VERTICAL_ALREADY_SET, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 37, err.column() );
}

/**
 * Test that the parser considers it an error when 2 cue-settings are separated by an invalid
 * delimiter (not whitespace)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-settings (11/21/2012):
 *
 * The WebVTT cue settings part of a WebVTT cue consists of zero or more of the following 
 * components, in any order, separated from each other by one or more U+0020 SPACE characters 
 * or U+0009 CHARACTER TABULATION (tab) characters. Each component must not be included more than 
 * once per WebVTT cue settings string.
 */
TEST_F(CueSetting,DISABLED_BadDelimiter)
{
	loadVtt( "cue-settings/bad-delimiter.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 36th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 36, err.column() );
}

/**
 * Test that the parser considers it an error when the timestamps and cue-settings are separated 
 * by an invalid delimiter (not whitespace)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-settings (11/21/2012):
 *
 * The WebVTT cue settings part of a WebVTT cue consists of zero or more of the following 
 * components, in any order, separated from each other by one or more U+0020 SPACE characters 
 * or U+0009 CHARACTER TABULATION (tab) characters. Each component must not be included more than 
 * once per WebVTT cue settings string.
 */
TEST_F(CueSetting,DISABLED_BadDelimiter2)
{
	loadVtt( "cue-settings/bad-delimiter2.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 24th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 24, err.column() );
}

/**
 * Test that the parser considers it an error when the timestamps and cue-settings are not separated
 * by any characters
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-settings (11/21/2012):
 *
 * The WebVTT cue settings part of a WebVTT cue consists of zero or more of the following 
 * components, in any order, separated from each other by one or more U+0020 SPACE characters 
 * or U+0009 CHARACTER TABULATION (tab) characters. Each component must not be included more than 
 * once per WebVTT cue settings string.
 */
TEST_F(CueSetting,DISABLED_NoDelimiter)
{
	loadVtt( "cue-settings/no-delimiter.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 24th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 24, err.column() );
}