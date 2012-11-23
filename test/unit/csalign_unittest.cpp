#include "cue_testfixture"
class CueSettingAlign : public CueTest { };

/**
 * Test properly formatted align start cue setting
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,Start)
{
	loadVtt( "cue-settings/align/start.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isAlignedToStart() );
}

/**
 * Test properly formatted align middle cue setting
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,Middle)
{
	loadVtt( "cue-settings/align/middle.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
}

/**
 * Test properly formatted align end cue setting
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,End)
{
	loadVtt( "cue-settings/align/end.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isAlignedToEnd() );
}

/**
 * Test properly formatted align end cue setting
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,DISABLED_Left)
{
	loadVtt( "cue-settings/align/left.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isAlignedToLeft() );
}

/**
 * Test properly formatted align end cue setting
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,DISABLED_Right)
{
	loadVtt( "cue-settings/align/right.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
	ASSERT_TRUE( getCue( 0 ).isAlignedToRight() );
}

/**
 * Test that we properly report an error for an align value with no keyword
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,DISABLED_NoKeyword)
{
	loadVtt( "cue-settings/align/no-keyword.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
	 * We could return a smarter error, after a little bit of refactoring, perhaps.
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 25, err.column() );
}

/**
 * Test that we properly report an error for an invalid 'align' setting value (star)
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,DISABLED_BadValue)
{
	loadVtt( "cue-settings/align/bad-value.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_ALIGN_BAD_VALUE error on the 31st column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_ALIGN_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 31, err.column() );
}

/**
 * Test that we properly report an error for an align keyword with no value
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,DISABLED_NoValue)
{
	loadVtt( "cue-settings/align/no-value.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_ALIGN_BAD_VALUE error on the 31st column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_ALIGN_BAD_VALUE, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 31, err.column() );
}

/**
 * Test that we properly report an error for an align cuesetting with no delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,DISABLED_BadDelimiter)
{
	loadVtt( "cue-settings/align/bad-delimiter.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 25, err.column() );
}

/**
 * Test that we properly report an error for an align cuesetting with no delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#the-webvtt-file-format (11/21/2012):
 * A WebVTT alignment cue setting consists of the following components, in the order given:
 * The string "align".
 *
 * A U+003A COLON character (:).
 * One of the following strings: "start", "middle", "end", "left", "right"
 */
TEST_F(CueSettingAlign,DISABLED_NoDelimiter)
{
	loadVtt( "cue-settings/align/no-delimiter.vtt" );
	const Error& err = getError( 0 );
	/**
	 * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
	 */
	ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
	ASSERT_EQ( 3, err.line() );
	ASSERT_EQ( 25, err.column() );
}
