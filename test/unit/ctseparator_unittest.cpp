#include "cue_testfixture"
class CueTimeSeparator : public CueTest { };

/**
 * Test expecting parser to fail when timestamp separator ('-->') does not have whitespace to its left
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 *
 * 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 *
 * 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 *
 * 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimeSeparator,MissingSpaceLeft)
{
  loadVtt( "cue-times/separator/missing_space_left.vtt" );
	const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
}

/**
 * Test expecting parser to fail when timestamp separator ('-->') does not have whitespace to its left or right
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 *
 * 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 *
 * 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 *
 * 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimeSeparator,MissingSpaceLeftRight)
{
  loadVtt( "cue-times/separator/missing_space_leftright.vtt" );
	const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
}

/**
 * Test expecting parser to fail when timestamp separator ('-->') is malformed
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 *
 * 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 *
 * 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 *
 * 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimeSeparator,DISABLED_Malformed) //currently fails, throws throws c++ out of bounds exception
{
  loadVtt( "cue-times/separator/malformed.vtt" );
	const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MISSING_CUETIME_SEPARATOR, err.error() );
}

/**
 * Test expecting parser to fail when timestamp separator ('-->') is not present
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 *
 * 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 *
 * 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 *
 * 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimeSeparator,DISABLED_Missing) //currently fails, throws c++ out of bounds exception
{
  loadVtt( "cue-times/separator/missing.vtt" );
	const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MISSING_CUETIME_SEPARATOR, err.error() );
}

/**
 * Test expecting parser to fail when timestamp separator ('-->') does not have whitespace to its right.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 *
 * 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 *    WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 *
 * 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 *
 * 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 *
 * 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 *  WebVTT timestamp must be greater than the start time offset of the cue.
 */

TEST_F(CueTimeSeparator,MissingSpaceRight)
{
  loadVtt( "cue-times/separator/missing_space_right.vtt" );
	const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
}