#include "cue_testfixture"
class CueTimeTimestampSecondFrac : public CueTest { };

/***************************************************************************************/
/*                                        FROM                                         */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds-frac' component contains
 * a non-digit
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
TEST_F(CueTimeTimestampSecondFrac,NondigitTimestamp1)
{
  loadVtt( "cue-times/timestamp/from/secondfrac/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds-frac' component
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
TEST_F(CueTimeTimestampSecondFrac,OneDigitTimestamp1)
{
  loadVtt( "cue-times/timestamp/from/secondfrac/one_digit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'second-frac' component
 * consists of only two digits
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
TEST_F(CueTimeTimestampSecondFrac,TwoDigitsTimestamp1)
{
  loadVtt( "cue-times/timestamp/from/secondfrac/two_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds' component
 * consists of greater than 3 digits
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
TEST_F(CueTimeTimestampSecondFrac,FourDigitsTimestamp1)
{
  loadVtt( "cue-times/timestamp/from/secondfrac/four_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/***************************************************************************************/
/*                                        UNTIL                                        */
/***************************************************************************************/

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds-frac' component contains
 * a non-digit
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
TEST_F(CueTimeTimestampSecondFrac,NondigitTimestamp2)
{
  loadVtt( "cue-times/timestamp/until/secondfrac/nondigit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds-frac' component
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
TEST_F(CueTimeTimestampSecondFrac,OneDigitTimestamp2)
{
  loadVtt( "cue-times/timestamp/until/secondfrac/one_digit.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'second-frac' component
 * consists of only two digits
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
TEST_F(CueTimeTimestampSecondFrac,TwoDigitsTimestamp2)
{
  loadVtt( "cue-times/timestamp/until/secondfrac/two_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds' component
 * consists of greater than 3 digits
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
TEST_F(CueTimeTimestampSecondFrac,FourDigitsTimestamp2)
{
  loadVtt( "cue-times/timestamp/until/secondfrac/four_digits.vtt" );
  const Error& err = getError( 0 );
  ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
}

/**
 * Test expecting parser to pass and checks the millisecond component of the time stamp
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
TEST_F(CueTimeTimestampSecondFrac,MillisecondsCheck)
{
  loadVtt( "cue-times/timestamp/from/secondfrac/good.vtt", 1 );
  ASSERT_EQ( 111, getCue(0).startTime().milliseconds() );
  EXPECT_EQ( 222, getCue(0).endTime().milliseconds() );
}

/**
 * Test expecting parser to fail when a component timestamp's 'milliseconds' component
 * consists of greater than 3 digits
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
TEST_F(CueTimeTimestampSecondFrac,FourDigitMillisecond)
{
  loadVtt( "cue-times/timestamp/from/secondfrac/four_digits_bad.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );
  const Error& err = getError( 0 );
  EXPECT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
}
