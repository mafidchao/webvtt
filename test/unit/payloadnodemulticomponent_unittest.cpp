#include "payloadnode_testfixture"

/**
This tests for the use of more than 1 cue component in the cue payload,
separated by cue text. This test should pass.

Based on WebVTT cue text specification as of October 2, 2012:
http://dev.w3.org/html5/webvtt/#webvtt-cue-text
*/
TEST_F(PayloadNodeTest, MulticomponentSeparated)
{
	loadVtt ("payload/samples/multicomponent/multiescape-separated.vtt", 1)
	
	//Sample test to demonstrate how to work with nodes.
    //Asserts that the head node has only 4 childs.
	ASSERT_EQ( 4, getHead()->childCount() );
	
	//Sample test to demonstrate how to work with nodes.
	//It gets the first child of the head node and asserts that it is an underline node.	
	//ASSERT_EQ( Node::Underline, getHead()->child( 0 )->toInternalNode()->kind() );
}