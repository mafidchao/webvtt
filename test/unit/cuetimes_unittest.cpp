#include "cue_testfixture"
class CueTimes : public CueTest { };

/**
 * 'From' timestamp'
 */

/**
 * Bounds checking - 'from' hour
 */
TEST_F(CueTimes,FromHourBeyondLowBoundary)
{
  loadVtt( "cue-times/from/hour-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromHourBeyondHighBoundary)
{
  loadVtt( "cue-times/from/hour-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromHourWithinLowBoundary)
{
  loadVtt( "cue-times/from/hour-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 5  );
}

TEST_F(CueTimes,FromHourWithinHighBoundary)
{
  loadVtt( "cue-times/from/hour-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 9, 56, 5 );
}

/**
 * Bounds checking - 'from' minute
 */
TEST_F(CueTimes,FromMinuteBeyondLowBoundary)
{
  loadVtt( "cue-times/from/minute-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromMinuteBeyondHighBoundary)
{
  loadVtt( "cue-times/from/minute-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromMinuteWithinLowBoundary)
{
  loadVtt( "cue-times/from/minute-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 56, 5  );
}

TEST_F(CueTimes,FromMinuteWithinHighBoundary)
{
  loadVtt( "cue-times/from/minute-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 005 );
}


/**
 * Bounds checking - 'from' second
 */
TEST_F(CueTimes,FromSecondBeyondLowBoundary)
{
  loadVtt( "cue-times/from/second-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromSecondBeyondHighBoundary)
{
  loadVtt( "cue-times/from/second-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromSecondWithinLowBoundary)
{
  loadVtt( "cue-times/from/second-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 0, 5  );
}

TEST_F(CueTimes,FromSecondWithinHighBoundary)
{
  loadVtt( "cue-times/from/second-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 59, 5 );
}

/**
 * Bounds checking - 'from' millisecond
 */
TEST_F(CueTimes,FromMillisecondBeyondLowBoundary)
{
  loadVtt( "cue-times/from/millisecond-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromMillisecondBeyondHighBoundary)
{
  loadVtt( "cue-times/from/millisecond-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromMillisecondWithinLowBoundary)
{
  loadVtt( "cue-times/from/millisecond-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 0  );
}

TEST_F(CueTimes,FromMillisecondWithinHighBoundary)
{
  loadVtt( "cue-times/from/millisecond-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 999 );
}

/**
 * Format - 'from' numbers of minute digits
 */
TEST_F(CueTimes,FromOneDigitMinute)
{
  loadVtt( "cue-times/from/minute-1-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromTwoDigitMinute)
{
  loadVtt( "cue-times/from/minute-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 1, 0, 0 );
}

TEST_F(CueTimes,FromThreeDigitMinute)
{
  loadVtt( "cue-times/from/minute-3-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Format - 'from' numbers of seconds digits
 */
TEST_F(CueTimes,FromOneDigitSecond)
{
  loadVtt( "cue-times/from/second-1-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromTwoDigitSecond)
{
  loadVtt( "cue-times/from/second-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 0, 25, 0 );
}

TEST_F(CueTimes,FromThreeDigitSecond)
{
  loadVtt( "cue-times/from/second-3-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Format - 'from' numbers of milliseconds digits
 */
TEST_F(CueTimes,FromTwoDigitMillisecond)
{
  loadVtt( "cue-times/from/millisecond-2-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromThreeDigitMillisecond)
{
  loadVtt( "cue-times/from/millisecond-3-digit.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 0, 0, 111 );
}

TEST_F(CueTimes,FromFourDigitMillisecond)
{
  loadVtt( "cue-times/from/millisecond-4-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Range checking
 */
TEST_F(CueTimes,FromMinuteGreaterThan59)
{
  loadVtt( "cue-times/from/minute-greater-than-59.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromSecondGreaterThan59)
{
  loadVtt( "cue-times/from/second-greater-than-59.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromMillisecondGreaterThan999)
{
  loadVtt( "cue-times/from/millisecond-greater-than-999.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Bad delimiter
 */
TEST_F(CueTimes,FromBadDelimiterHourMinute)
{
  loadVtt( "cue-times/from/bad-delimiter-hour-minute.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromBadDelimiterMinuteSecond)
{
  loadVtt( "cue-times/from/bad-delimiter-minute-second.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,FromBadDelimiterSecondMillisecond)
{
  loadVtt( "cue-times/from/bad-delimiter-second-millisecond.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * 'Until' timestamp'
 */

/**
 * Bounds checking - 'until' hour
 */
TEST_F(CueTimes,UntilHourBeyondLowBoundary)
{
  loadVtt( "cue-times/until/hour-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilHourBeyondHighBoundary)
{
  loadVtt( "cue-times/until/hour-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilHourWithinLowBoundary)
{
  loadVtt( "cue-times/until/hour-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 5  );
}

TEST_F(CueTimes,UntilHourWithinHighBoundary)
{
  loadVtt( "cue-times/until/hour-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 9, 56, 5 );
}

/**
 * Bounds checking - 'until' minute
 */
TEST_F(CueTimes,UntilMinuteBeyondLowBoundary)
{
  loadVtt( "cue-times/until/minute-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilMinuteBeyondHighBoundary)
{
  loadVtt( "cue-times/until/minute-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilMinuteWithinLowBoundary)
{
  loadVtt( "cue-times/until/minute-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 56, 5  );
}

TEST_F(CueTimes,UntilMinuteWithinHighBoundary)
{
  loadVtt( "cue-times/until/minute-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 005 );
}


/**
 * Bounds checking - 'until' second
 */
TEST_F(CueTimes,UntilSecondBeyondLowBoundary)
{
  loadVtt( "cue-times/until/second-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilSecondBeyondHighBoundary)
{
  loadVtt( "cue-times/until/second-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilSecondWithinLowBoundary)
{
  loadVtt( "cue-times/until/second-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 0, 5  );
}

TEST_F(CueTimes,UntilSecondWithinHighBoundary)
{
  loadVtt( "cue-times/until/second-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 59, 5 );
}

/**
 * Bounds checking - 'until' millisecond
 */
TEST_F(CueTimes,UntilMillisecondBeyondLowBoundary)
{
  loadVtt( "cue-times/until/millisecond-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilMillisecondBeyondHighBoundary)
{
  loadVtt( "cue-times/until/millisecond-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilMillisecondWithinLowBoundary)
{
  loadVtt( "cue-times/until/millisecond-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 0  );
}

TEST_F(CueTimes,UntilMillisecondWithinHighBoundary)
{
  loadVtt( "cue-times/until/millisecond-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 9, 56, 999 );
}

/**
 * Format - 'until' numbers of minute digits
 */
TEST_F(CueTimes,UntilOneDigitMinute)
{
  loadVtt( "cue-times/until/minute-1-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilTwoDigitMinute)
{
  loadVtt( "cue-times/until/minute-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 1, 0, 0 );
}

TEST_F(CueTimes,UntilThreeDigitMinute)
{
  loadVtt( "cue-times/until/minute-3-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Format - 'until' numbers of seconds digits
 */
TEST_F(CueTimes,UntilOneDigitSecond)
{
  loadVtt( "cue-times/until/second-1-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilTwoDigitSecond)
{
  loadVtt( "cue-times/until/second-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 0, 25, 0 );
}

TEST_F(CueTimes,UntilThreeDigitSecond)
{
  loadVtt( "cue-times/until/second-3-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Format - 'until' numbers of milliseconds digits
 */
TEST_F(CueTimes,UntilTwoDigitMillisecond)
{
  loadVtt( "cue-times/until/millisecond-2-digit.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilThreeDigitMillisecond)
{
  loadVtt( "cue-times/until/millisecond-3-digit.vtt", 1 );
  assertEquals( getCue( 0 ).fromTime(), 0, 0, 0, 111 );
}

TEST_F(CueTimes,UntilFourDigitMillisecond)
{
  loadVtt( "cue-times/until/millisecond-4-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Range checking
 */
TEST_F(CueTimes,UntilMinuteGreaterThan59)
{
  loadVtt( "cue-times/until/minute-greater-than-59.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilSecondGreaterThan59)
{
  loadVtt( "cue-times/until/second-greater-than-59.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilMillisecondGreaterThan999)
{
  loadVtt( "cue-times/until/millisecond-greater-than-999.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

/**
 * Bad delimiter
 */
TEST_F(CueTimes,UntilBadDelimiterHourMinute)
{
  loadVtt( "cue-times/until/bad-delimiter-hour-minute.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilBadDelimiterMinuteSecond)
{
  loadVtt( "cue-times/until/bad-delimiter-minute-second.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}

TEST_F(CueTimes,UntilBadDelimiterSecondMillisecond)
{
  loadVtt( "cue-times/until/bad-delimiter-second-millisecond.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
}