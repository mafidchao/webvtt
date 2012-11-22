#include "test_parser"
#include <stdio.h>

/**
 * These node tests will be really complex as it's currently set up right now as there may be a lot of 
 * nodes nested in trees that we need to get to. We should probably simplify either the inheritance structure 
 * of the nodes or provide some kind of utilities to quickly traverse trees, etc.
 *
 * Personally I'm thinking that we need to rethink the whole node structure within the parser and within
 * these C bindings.
 */

/**
 * Sample test to demonstrate how to work with nodes.
 * Asserts that the head node has only 2 childs.
 */
TEST(PayloadMarkup,DISABLED_NodeCount)
{
	/**
	 * Seg fault.
	 */
	ItemStorageParser parser("payload/samples/node-count.vtt");
	parser.parse();
		
	const Cue &cue = parser.getCue(0);
	InternalNode * node = (InternalNode *)cue.getHead();

	ASSERT_EQ(2, node->childNodeCount());
}

/**
 * Sample test to demonstrate how to work with nodes.
 * It gets the first child of the head node and asserts that it is an underline node.
 */
TEST(PayloadMarkup,DISABLED_CheckNodeKind)
{
	/**
	 * Seg fault.
	 */
	ItemStorageParser parser("payload/samples/node-kind.vtt");
	parser.parse();
		
	const Cue &cue = parser.getCue(0);
	InternalNode * headNode = (InternalNode *)cue.getHead();
	InternalNode * childNode = (InternalNode *)headNode->childAtIndex(0);

	ASSERT_EQ(Node::UnderlineNode, childNode->kind());
}
