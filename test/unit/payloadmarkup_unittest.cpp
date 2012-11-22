#include "test_parser"

/**
 * Sample test to demonstrate how to work with nodes.
 */
TEST(PayloadMarkup, NodeCount)
{
	ItemStorageParser parser("payload/samples/node-count.vtt");
	parser.parse();
		
	const Cue &cue = parser.getCue(0);
	InternalNode node = (InternalNode)cue->getHead();

	ASSERT_EQ(2, node.childNodeCount());
}

/**
 * Sample test to demonstrate how to work with nodes.
 */
TEST(PayloadMarkup, NodeCount)
{
	ItemStorageParser parser("payload/samples/node-kind.vtt");
	parser.parse();
		
	const Cue &cue = parser.getCue(0);
	InternalNode node = (InternalNode)cue->getHead().childAtIndex(0);

	ASSERT_EQ(Node::UnderlineNode, node.nodeKind());
}