#include <webvttxx/nodefactory>

namespace WebVTT
{

Node NodeFactory::createNode( webvtt_node_ptr otherNode )
{
	if ( WEBVTT_IS_VALID_INTERNAL_NODE( otherNode->kind ) )
		return InternalNode( otherNode );
	else if ( otherNode->kind == Node::TextNode )
		return TextNode( otherNode );
	else if ( otherNode->kind == Node::TimeStampNode )
		return TimeStampNode( otherNode );
	return 0;
}

}