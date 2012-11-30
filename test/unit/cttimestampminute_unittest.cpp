#include "cue_testfixture"
class CueTimeTimestampMinute : public CueTest { };

/***************************************************************************************/
/*                                        FROM                                         */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component consists
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
TEST_F(CueTimeTimestampMinute,DISABLED_NondigitTimestamp1)//C++ exception "std::bad_alloc"
{
  loadVtt( "cue-times/timestamp/from/minute/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a single digit between the range of allowed values (00-59)
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
TEST_F(CueTimeTimestampMinute,OneDigitTimestamp1)
{
  loadVtt( "cue-times/timestamp/from/minute/one_digit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a 2 digits with an integer value greater than 59
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
TEST_F(CueTimeTimestampMinute,DISABLED_GT60Timestamp1)//C++ exception "std::bad_alloc"
{
  loadVtt( "cue-times/timestamp/from/minute/gt_60.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of 3 digits with an integer value within the range of 0-59
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
TEST_F(CueTimeTimestampMinute,ThreeDigitsTimestamp1)
{
  loadVtt( "cue-times/timestamp/from/minute/three_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/***************************************************************************************/
/*                                        UNTIL                                        */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component consists
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
TEST_F(CueTimeTimestampMinute,DISABLED_NondigitTimestamp2)//C++ exception "std::bad_alloc"
{
  loadVtt( "cue-times/timestamp/until/minute/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a single digit between the range of allowed values (00-59)
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
TEST_F(CueTimeTimestampMinute,OneDigitTimestamp2)
{
  loadVtt( "cue-times/timestamp/until/minute/one_digit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a 2 digits with an integer value greater than 59
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
TEST_F(CueTimeTimestampMinute,GT60Timestamp2)
{
  loadVtt( "cue-times/timestamp/until/minute/gt_60.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of 3 digits with an integer value within the range of 0-59
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
TEST_F(CueTimeTimestampMinute,ThreeDigitsTimestamp2)
{
  loadVtt( "cue-times/timestamp/until/minute/three_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to pass and checks the minutes component of the time stamp
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
TEST_F(CueTimeTimestampMinute,MinutesCheck)
{
  loadVtt( "cue-times/timestamp/from/minute/good.vtt", 1 );
  ASSERT_EQ( 1, getCue(0).startTime().minutes() );
  EXPECT_EQ( 2, getCue(0).endTime().minutes() );
}