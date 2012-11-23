#include "payload_testfixture"
class PayloadTagFormat : public PayloadTest {};

/*
This test is to verify that multiple cue text tags can be nested within eachother.
Based on the WebVTT cue components specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-components
*/
TEST_F(PayloadTagFormat,DISABLED_MultipleCueTextTag)
{
	loadVtt( "payload/tag-format/multiple-cue-text-tag.vtt" );
	ASSERT_EQ( Node::Italic, getHeadOfCue( 0 )->child( 0 )->kind() );
	ASSERT_EQ( Node::Bold, getHeadOfCue( 0 )->child( 0 )->toInternalNode()->child( 0 )->kind() );
}

/*
This test is to verify that a single subclass can be used on cue text tags.
Based on the WebVTT cue span start tag specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag
*/
TEST_F(PayloadTagFormat,DISABLED_SingleSubclass)
{
	loadVtt( "payload/tag-format/cue-text-single-subclass.vtt" );

	StringList cssClasses = getHeadOfCue( 0 )->child( 0 )->toInternalNode()->cssClasses();
	String cssClass = String( (const byte *)"class", 5 );

	ASSERT_TRUE( cssClasses.length() == 1 );
	ASSERT_EQ(  cssClass.text(), cssClasses.stringAtIndex( 0 ).text() );
}

/*
This tests verifies that multiple subclasses can be placed on a cue text tag. 
Based on the WebVTT cue components specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag
*/
TEST_F(PayloadTagFormat,DISABLED_MultiSubclass)
{
	loadVtt( "payload/tag-format/cue-text-multi-subclass.vtt" );

	StringList cssClasses = getHeadOfCue( 0 )->child( 0 )->toInternalNode()->cssClasses();
	String cssClass = String( (const byte *)"class", 5 );

	ASSERT_TRUE( cssClasses.length() == 1 );

	ASSERT_EQ(  cssClass.text(), cssClasses.stringAtIndex( 0 ).text() );

	cssClass = String( (const byte *)"subclass", 8 );
	ASSERT_EQ( cssClass.text(), cssClasses.stringAtIndex( 1 ).text() );
}

/*
Verifies that italic cue components are parsed.
Based on the WebVTT cue italics span specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-italics-span
*/
TEST_F(PayloadTagFormat,DISABLED_ItalicCueTextTag)
{
	loadVtt( "payload/tag-format/italic-tag.vtt" );
	ASSERT_EQ( Node::Italic, getHeadOfCue( 0 )->child( 1 )->kind() );
}

/*
Verifies that bold cue components are parsed.
Based on the WebVTT cue bold span specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-bold-span
*/
TEST_F(PayloadTagFormat,DISABLED_BoldcCueTextTag)
{
	loadVtt( "payload/tag-format/bold-tag.vtt" );
	ASSERT_EQ( Node::Bold, getHeadOfCue( 0 )->child( 1 )->kind() );
}

/*
Verifies that voice cue components are parsed.
Based on the WebVTT cue voice span specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-voice-span
*/
TEST_F(PayloadTagFormat,DISABLED_VoiceCueTextTag)
{
	loadVtt( "payload/tag-format/voice-tag.vtt" );
	ASSERT_EQ( Node::Voice, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
Verifies that a class cue text tags will be parsed correctly.
Based on the WebVTT cue class span specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-class-span
*/
TEST_F(PayloadTagFormat,DISABLED_ClassCueTextTag)
{
	loadVtt( "payload/tag-format/class-tag.vtt" );
	ASSERT_EQ( Node::Class, getHeadOfCue( 0 )->child( 1 )->kind() );
}

/*
Verifies that cue text end tags that are out of order will be ignored.

Relevant cue text specification rules:
	1. End tags that do not close the current open tag are ignored.
	2. If tags are not closed then the tag will be valid until the end of the cue text.

Based on the WebVTT cue text specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-text
*/
TEST_F(PayloadTagFormat,DISABLED_BadTagNesting)
{
	loadVtt( "payload/tag-format/bad-tag-nesting.vtt" );
	const InternalNode *head = getHeadOfCue( 0 );

	ASSERT_TRUE( head->childCount() == 2 );

	const InternalNode *italicNode = head->child( 1 )->toInternalNode();
	ASSERT_EQ( Node::Italic, italicNode->kind() );

	ASSERT_EQ( Node::Bold, italicNode->kind() );
	ASSERT_EQ( Node::Text, italicNode->child( 0 )->kind() );
}

/*
Verifies that cue text end tags that are malformed are ignored.

Relevant cue text specification rules:
	1. End tags that do not close the current open tag are ignored.
	2. If tags are not closed then the tag will be valid until the end of the cue text.

Based on the WebVTT cue span end tag sepcficication as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-end-tag
*/
TEST_F(PayloadTagFormat,DISABLED_EndTagNoBackSlashNoEndBrace)
{
	loadVtt( "payload/tag-format/end-tag-no-back-slash-no-end-brace.vtt.vtt" );
	const InternalNode *head = getHeadOfCue( 0 );

	ASSERT_TRUE( head->childCount() == 2 );

	const InternalNode *italicNode = head->child( 1 )->toInternalNode();
	ASSERT_EQ( Node::Italic, italicNode->kind() );

	ASSERT_TRUE( italicNode->childCount() == 2 );
	ASSERT_TRUE( Node::Text, italicNode->child( 0 )->kind() );
	ASSERT_TRUE( Node::Text, italicNode->child( 1 )->kind() );
}

/*
Verifies that a cue text end tage with no end brace will be ignored.

Relevant cue text specification rules:
	1. End tags that do not close the current open tag are ignored.
	2. If tags are not closed then the tag will be valid until the end of the cue text.

Based on the WebVTT cue span end tag sepcficication as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-end-tag
*/
TEST_F(PayloadTagFormat,DISABLED_EndTagNoEndBrace)
{
	loadVtt( "payload/tag-format/end-tag-no-end-brace.vtt.vtt" );
	const InternalNode *head = getHeadOfCue( 0 );

	ASSERT_TRUE( head->childCount() == 2 );

	const InternalNode *italicNode = head->child( 1 )->toInternalNode();
	ASSERT_EQ( Node::Italic, italicNode->kind() );

	ASSERT_TRUE( italicNode->childCount() == 2 );
	ASSERT_TRUE( Node::Text, italicNode->child( 0 )->kind() );
	ASSERT_TRUE( Node::Text, italicNode->child( 1 )->kind() );
}

/*
Verifies that a cue text end tag that is formatted incorrectly will be ignored.

Relevant cue text specification rules:
	1. End tags that do not close the current open tag are ignored.
	2. If tags are not closed then the tag will be valid until the end of the cue text.

Based on the WebVTT cue span end tag sepcficication as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-end-tag
*/
TEST_F(PayloadTagFormat,DISABLED_EndTagNoStartBrace)
{
	loadVtt( "payload/tag-format/end-tag-no-start-brace.vtt" );
	const InternalNode *head = getHeadOfCue( 0 );

	ASSERT_TRUE( head->childCount() == 2 );

	const InternalNode *italicNode = head->child( 1 )->toInternalNode();
	ASSERT_EQ( Node::Italic, italicNode->kind() );

	ASSERT_TRUE( italicNode->childCount() == 2 );
	ASSERT_TRUE( Node::Text, italicNode->child( 0 )->kind() );
	ASSERT_TRUE( Node::Text, italicNode->child( 1 )->kind() );
}

/*
Verifies that cue text tags that do not have end tags will be valid until the end of the cue text.

Relevant cue text specification rules:
	1. If tags are not closed then the tag will be valid until the end of the cue text.

Based on the WebVTT cue span end tag sepcficication as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-end-tag
*/
TEST_F(PayloadTagFormat,DISABLED_MultiTagNoEndTag)
{
	loadVtt( "payload/tag-format/multi-tag-no-end-tag.vtt" );
	const InternalNode *head = getHeadOfCue( 0 );

	ASSERT_TRUE( head->childCount() == 2 );

	const InternalNode *italicNode = head->child( 1 )->toInternalNode();
	ASSERT_EQ( Node::Italic, italicNode->kind() );

	ASSERT_TRUE( italicNode->childCount() == 2 );
	ASSERT_TRUE( Node::Text, italicNode->child( 0 )->kind() );
	ASSERT_TRUE( Node::Italic, italicNode->child( 1 )->kind() );
	ASSERT_TRUE( Node::Text, italicNode->child( 1 )->child( 0 )->kind() );
}

/*
Verifies that a cue text start tag with an invalid name will be ignored.

Relevant cue text specification rules:
	1. Malformed cue text start tags are ignored.
	2. Characters that come after the '<' and before a white space are considered to be apart of the tag name.
	3. Tag names that are not valid are ignored.

Based on the WebVTT cue span start tag specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag
*/
TEST_F(PayloadTagFormat,DISABLED_StartTagNoEndBrace)
{
	loadVtt( "payload/tag-format/start-tag-no-end-brace.vtt" );
	const InternalNode *head = getHeadOfCue( 0 );

	ASSERT_TRUE( head->childCount() == 2 );

	ASSERT_EQ( Node::Text, head->child( 0 )->kind() );
	ASSERT_EQ( Node::Text, head->child( 1 )->kind() );
}

/*
Tests a common situation where the '>' of a start tag is left out and the tag name is immediatley followed by a space.
These are able to be parsed correctly but will not have the intended results.
In this situation the characters after the space are parsed as an annotation and the '>' becomes the closing
brace of the start tag.

Relevant cue text specification rules:
	1. Characters that come after a space in a start tag are considered to be an annotation. 

Based on the WebVTT cue span start tag specification as of October 3, 2012.
http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag
*/
TEST_F(PayloadTagFormat,DISABLED_StartTagNoEndBraceSpace)
{
	loadVtt( "payload/tag-format/start-tag-no-end-brace-space.vtt" );
	const InternalNode *head = getHeadOfCue( 0 );

	ASSERT_TRUE( head->childCount() == 2 );

	const InternalNode *italicNode = head->child( 1 )->toInternalNode();
	ASSERT_EQ( Node::Italic, italicNode->kind() );

	ASSERT_TRUE( italicNode->childCount() == 1 );
	ASSERT_EQ( Node::Text, italicNode->child( 0 )->kind() );
}