#include "payload_testfixture"
class PayloadFormat : public PayloadTest {};

/*
This test is to verify that no cue text is valid.
Based on the WebVTT cue text span specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-text-span
*/
TEST_F(PayloadFormat,DISABLED_NoCueText)
{
	loadVtt( "payload/payload-format/no-cue-text.vtt", 1 );
	/* Expect error. ? */
}

/*
Verifies that just a cue text span will work.
Based on the WebVTT cue text span specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-text-span
*/
TEST_F(PayloadFormat,DISABLED_BasicCueText)
{
	loadVtt( "payload/payload-format/basic-cue-text.vtt", 1 );
	ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
Verifies that just a cue text span with multiple lines will work.
Based on the WebVTT cue text span specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-text-span
*/
TEST_F(PayloadFormat,DISABLED_MultilineBasicCueText)
{
	loadVtt( "payload/payload-format/multiline-basic-cue-text.vtt", 1 );
	ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
Verifies that multiple cue components can be put in one line.
Based on the WebVTT cue components specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-components
*/
TEST_F(PayloadFormat,DISABLED_MultipleCueTextTag)
{
	loadVtt( "payload/payload-format/multiple-cue-tag.vtt", 1 );
	ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 5 );
}

/*
Verifies that multiple cue component are parsed correctly.
Based on the WebVTT cue components specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-components
*/
TEST_F(PayloadFormat,DISABLED_MultilineCueText)
{
	loadVtt( "payload/payload-format/multiline-cue-text.vtt", 1 );
	ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 4 );
}

/*
This test is to verify that multiple cue components can be nested within eachother with line terminators between them.
Based on the WebVTT cue components specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-components
*/
TEST_F(PayloadFormat,DISABLED_MultilineMultipleCueTextTag)
{
	loadVtt( "payload/payload-format/multiline-multiple-cue-text-tag.vtt" );
	
	const InternalNode *node = getHeadOfCue( 0 );
	ASSERT_EQ( Node::Underline, node->kind() );

	node = node->child( 0 )->toInternalNode();
	ASSERT_EQ( Node::Italic, node->kind() );

	node = node->child( 0 )->toInternalNode();
	ASSERT_EQ( Node::Bold, node->kind() );
}