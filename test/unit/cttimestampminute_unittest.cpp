#include "cue_testfixture"
class CueTimeTimestampMinute : public CueTest { };

/***************************************************************************************/
/*                                     TIMESTAMP 1                                     */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component consists
 * of a non-digit
 * TIMESTAMP 1
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
TEST_F(CueTimeTimestampMinute,Nondigit)
{
  loadVtt( "cue-times/timestamp/timestamp1/minute/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a single digit between the range of allowed values (00-59)
 * TIMESTAMP 1
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
TEST_F(CueTimeTimestampMinute,OneDigit)
{
  loadVtt( "cue-times/timestamp/timestamp1/minute/one_digit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a 2 digits with an integer value greater than 59
 * TIMESTAMP 1
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
TEST_F(CueTimeTimestampMinute,GT60)
{
  loadVtt( "cue-times/timestamp/timestamp1/minute/gt_60.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of 3 digits with an integer value within the range of 0-59
 * TIMESTAMP 1
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
TEST_F(CueTimeTimestampMinute,ThreeDigits)
{
  loadVtt( "cue-times/timestamp/timestamp1/minute/three_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/***************************************************************************************/
/*                                     TIMESTAMP 2                                     */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component consists
 * of a non-digit
 * TIMESTAMP 2
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
TEST_F(CueTimeTimestampMinute,Nondigit)
{
  loadVtt( "cue-times/timestamp/timestamp2/minute/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a single digit between the range of allowed values (00-59)
 * TIMESTAMP 2
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
TEST_F(CueTimeTimestampMinute,OneDigit)
{
  loadVtt( "cue-times/timestamp/timestamp2/minute/one_digit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a 2 digits with an integer value greater than 59
 * TIMESTAMP 2
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
TEST_F(CueTimeTimestampMinute,GT60)
{
  loadVtt( "cue-times/timestamp/timestamp2/minute/gt_60.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of 3 digits with an integer value within the range of 0-59
 * TIMESTAMP 2
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
TEST_F(CueTimeTimestampMinute,ThreeDigits)
{
  loadVtt( "cue-times/timestamp/timestamp2/minute/three_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}