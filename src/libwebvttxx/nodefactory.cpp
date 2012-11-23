#include <webvttxx/nodefactory>

namespace WebVTT
{

const Node * NodeFactory::createNode( webvtt_node_ptr otherNode )
{
	if ( WEBVTT_IS_VALID_INTERNAL_NODE( otherNode->kind ) )
		return new InternalNode( otherNode );
	else if ( otherNode->kind == Node::Text )
		return new TextNode( otherNode );
	else if ( otherNode->kind == Node::TimeStamp )
		return new TimeStampNode( otherNode );
	return 0;
}

}