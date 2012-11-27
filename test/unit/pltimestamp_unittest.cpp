#include "payload_testfixture"
class PayloadTimestampTag : public PayloadTest {};

/*
 * Verifies that time stamp cue components are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timestamp (11/27/2012)
 */
TEST_F(PayloadTimestampTag,DISABLED_TimestampTag)
{
	loadVtt( "payload/timestamp/timestamp-tag.vtt", 1 );

	const TimeStampNode *timeStamp = getHeadOfCue( 0 )->child( 1 )->toTimeStampNode();

	ASSERT_EQ( Node::TimeStamp, timeStamp->kind() );
	ASSERT_TRUE( timeStamp->timeStamp().toSeconds() == 720 );
}

/*
 * Verifies that multiple time stamp cue components are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timestamp (11/27/2012)
*/
TEST_F(PayloadTimestampTag,DISABLED_MultipleTimestampTag)
{
	loadVtt( "payload/timestamp/multiple-timestamp-tag.vtt", 1 );
	const TimeStampNode *timeStamp = getHeadOfCue( 0 )->child( 1 )->toTimeStampNode();

	ASSERT_EQ( Node::TimeStamp, timeStamp->kind() );
	ASSERT_TRUE( timeStamp->timeStamp().toSeconds() == 720 );

	timeStamp = getHeadOfCue( 0 )->child( 3 )->toTimeStampNode();

	ASSERT_EQ( Node::TimeStamp, getHeadOfCue( 0 )->child( 3 )->kind() );
	ASSERT_TRUE( timeStamp->timeStamp().toSeconds() == 780 );
}