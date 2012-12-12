#include "cue_testfixture"
class CueTimeTimestampHour : public CueTest { };

/***************************************************************************************/
/*                                        FROM                                         */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'hours' component consists
 * of a non-digit
 *    FROM    
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), 
 *    representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the 
 *    seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the 
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimeTimestampHour,NondigitTimestamp1)
{
  loadVtt( "cue-times/timestamp/from/hour/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/***************************************************************************************/
/*                                        UNTIL                                        */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'hours' component consists
 * of a non-digit
 *    UNTIL   
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), 
 *    representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the 
 *    seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the 
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimeTimestampHour,NondigitTimestamp2)
{
  loadVtt( "cue-times/timestamp/until/hour/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to pass and checks the hours component of the time stamp
 *    UNTIL   
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), 
 *    representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the 
 *    seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the 
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimeTimestampHour,HoursCheck)
{
  loadVtt( "cue-times/timestamp/from/hour/good.vtt", 1 );
  ASSERT_EQ( 2, getCue(0).startTime().hours() );
  EXPECT_EQ( 10, getCue(0).endTime().hours() );
}

/*
 *Test expecting the parser to fail with an invalid start time (alphabet and symbols)
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
 TEST_F(CueTimeTimestampHour,InvalidHour)
{
  loadVtt( "cue-times/timestamp/from/hour/nondigit_bad.vtt", 1 ); 
  ASSERT_NE( 0, errorCount() ); 
  const Error& err = getError( 0 );
  EXPECT_EQ( WEBVTT_INVALID_ENDTIME, err.error() );
}