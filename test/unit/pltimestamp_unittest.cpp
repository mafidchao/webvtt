#include "payload_testfixture"
class PayloadTimestamp : public PayloadTest {};

/*
Verifies that multiple time stamp cue components are parsed.
Based on the WebVTT cue timestamp specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-timestamp
*/
TEST_F(PayloadTimestamp,DISABLED_MultipleTimestampTag)
{
	loadVtt( "payload/timestamp/multiple-timestamp-tag.vtt", 1 );
	ASSERT_EQ( Node::TimeStamp, getHeadOfCue( 0 )->child( 1 )->kind() );
	ASSERT_EQ( Node::TimeStamp, getHeadOfCue( 0 )->child( 3 )->kind() );
}

/*
Verifies that time stamp cue components are parsed.
Based on the WebVTT cue timestamp specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-timestamp
*/
TEST_F(PayloadTimestamp,DISABLED_TimestampTag)
{
	loadVtt( "payload/timestamp/multiple-timestamp-tag.vtt", 1 );
	ASSERT_EQ( Node::TimeStamp, getHeadOfCue( 0 )->child( 1 )->kind() );
}