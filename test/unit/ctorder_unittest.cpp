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
  loadVtt( "cue-times/order/end_lt_start.vtt" );
	const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_INVALID_ENDTIME, err.error() );
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
TEST_F(CueTimeOrder,EndLTStart)
{
  loadVtt( "cue-times/order/start_lt_prior_cue.vtt" );
	const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_INVALID_CUETIME, err.error() ); //this should be different, but matching one found
}