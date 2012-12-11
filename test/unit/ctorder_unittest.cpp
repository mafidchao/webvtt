#include "cue_testfixture"
class CueTimeOrder : public CueTest { };

/**
 * Test expecting parser to fail when a cue's end timestamp has a value less than its start timestamp
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
TEST_F(CueTimeOrder,EndLTStart)
{
  loadVtt( "cue-times/order/end_lt_start.vtt", 0 );
	const Error& err = getError( 0 );
  ASSERT_EQ( 1, errorCount() );
  EXPECT_EQ( WEBVTT_INVALID_ENDTIME, err.error() );
}

/*
 * Test expecting parser to fail when a start timestamp has a value less than any prior cue's start timestamp
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
TEST_F(CueTimeOrder,StartLTPriorCue) //currently fails, throws c++ out of bounds exception
{
  loadVtt( "cue-times/order/start_lt_prior_cue.vtt", 0 );
	const Error& err = getError( 0 );
  ASSERT_EQ( 1, errorCount() );
  EXPECT_EQ( WEBVTT_INVALID_ENDTIME, err.error() ); //this should be different, but no matching one found
}
/*
 *Test expecting the parser to pass when a start timestamp has a value less than an end timestamp
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
TEST_F(CueTimeOrder,EndGTStart)
{
    loadVtt( "cue-times/order/end_gt_start.vtt", 1 );
    const Cue& cue = getCue(0);
    cue.startTime().hours();
    ASSERT_EQ( 0, errorCount() );
    EXPECT_EQ( 25, cue.startTime().seconds());
}

/*
 *Test expecting the parser to pass with two cues that start at the same time (inline) but end at different times
 *that are greater than the starting time.
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
TEST_F(CueTimeOrder,EndGTStartWithInline)
{
    loadVtt( "cue-times/order/end_gt_start_with_inline.vtt", 2 );
    ASSERT_EQ( 0, errorCount() );
}

/*
 *Test expecting the parser to pass with two cues that start immediately after each other.
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
TEST_F(CueTimeOrder, SecondCueStartsAfterFirst)
{
    loadVtt( "cue-times/order/two_cues_good.vtt", 2 );
    ASSERT_EQ( 0, errorCount() );
}

/*
 *Test expecting the parser to pass with two cues, one which starts during the 1st cue.
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
TEST_F(CueTimeOrder, SecondCueDuringFirst)
{
    loadVtt( "cue-times/order/second_cue_during_first.vtt", 2 );
    ASSERT_EQ( 0, errorCount() );
}

/*
 *Test expecting the parser to fail with one cue, where the start and end time are the same
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
TEST_F(CueTimeOrder, StartEqualsEnd)
{
  loadVtt( "cue-times/order/start_equals_end_bad.vtt", 0 );
  ASSERT_EQ( 1, errorCount() );
  const Error& err = getError( 0 );
  EXPECT_EQ( WEBVTT_INVALID_ENDTIME, err.error() );
}

/*
 *Test expecting the parser to fail with one cue, where the start time greater than the end time
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
 TEST_F(CueTimeOrder, StartGreaterEnd)
{
  loadVtt( "cue-times/order/start_greater_end_bad.vtt", 0 );
  ASSERT_EQ( 1, errorCount() );
  const Error& err = getError( 0 );
  EXPECT_EQ( WEBVTT_INVALID_ENDTIME, err.error() );
}

/*
 *Test expecting the parser to fail with one cue, where the second cue begins before the first cue
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
 TEST_F(CueTimeOrder, SecondCueBeforeFirst)
{
  loadVtt( "cue-times/order/second_cue_before_first_bad.vtt", 2 );
  ASSERT_EQ( 1, errorCount() );
  const Error& err = getError( 0 );
  EXPECT_EQ( WEBVTT_INVALID_ENDTIME, err.error() );
}
