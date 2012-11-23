#include "payload_testfixture"

/**
 * Sample test to demonstrate how to work with nodes.
 * Asserts that the head node has only 2 childs.
 */
TEST_F(PayloadTest,NodeCount)
{
	loadVtt( "payload/samples/node-count.vtt", 1 );
	ASSERT_EQ( 2, getHeadOfCue( 0 )->childCount() );
}

/**
 * Sample test to demonstrate how to work with nodes.
 * It gets the first child of the head node and asserts that it is an underline node.
 */
TEST_F(PayloadTest,CheckNodeKind)
{
	loadVtt( "payload/samples/node-kind.vtt", 1 );
	ASSERT_EQ( Node::Italic, getHeadOfCue( 0 )->child( 0 )->toInternalNode()->kind() );
}
