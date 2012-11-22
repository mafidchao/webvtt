#include <webvttxx/nodefactory>

namespace WebVTT
{

Node * NodeFactory::createNode( webvtt_node_ptr otherNode )
{
	if ( WEBVTT_IS_VALID_INTERNAL_NODE( otherNode->kind ) )
		return new InternalNode( otherNode );
	else if ( otherNode->kind == Node::TextNode )
		return new TextNode( otherNode );
	else if ( otherNode->kind == Node::TimeStampNode )
		return new TimeStampNode( otherNode );
	return 0;
}

}