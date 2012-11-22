#include <webvttxx/node>
#include <webvttxx/nodefactory>

namespace WebVTT
{	

Node * Node::parentNode()
{
	return NodeFactory::createNode( nodePtr->parent );
}

Node * InternalNode::childAtIndex( uint index )
{
	if( index <= internalNodePtr->length )
		return NodeFactory::createNode( internalNodePtr->children[index] );
	else 
		return 0;
}

}