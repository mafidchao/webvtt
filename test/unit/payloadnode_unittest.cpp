#include "payloadnode_testfixture"

/**
 * Sample test to demonstrate how to work with nodes.
 * Asserts that the head node has only 2 childs.
 */
TEST_F(PayloadNodeTest,DISABLED_NodeCount)
{
	/**
	 * Seg fault.
	 */
	loadVtt( "payload/samples/node-count.vtt", 1 );
	ASSERT_EQ( 2, getHead()->childCount() );
}

/**
 * Sample test to demonstrate how to work with nodes.
 * It gets the first child of the head node and asserts that it is an underline node.
 */
TEST_F(PayloadNodeTest,DISABLED_CheckNodeKind)
{
	/**
	 * Seg fault.
	 */
	loadVtt( "payload/samples/node-kind.vtt", 1 );
	ASSERT_EQ( Node::Underline, getHead()->child( 0 )->toInternalNode()->kind() );
}
