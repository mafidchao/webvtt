#include <webvttxx/node>
#include <webvttxx/nodefactory>

namespace WebVTT
{	

Node * Node::parent() const
{
	return NodeFactory::createNode( nodePtr->parent );
}

Node * InternalNode::child( uint index ) const
{
	if( index <= internalNodePtr->length )
		return NodeFactory::createNode( internalNodePtr->children[index] );
	else 
		return 0;
}

const InternalNode * Node::toInternalNode() const
{
	const InternalNode *node = dynamic_cast<const InternalNode *>( this );
	if( node == 0 )
	{
		throw "Invalid cast to InternalNode.";
	}
	return node;

}

const TextNode * Node::toTextNode() const
{
	const TextNode *node = dynamic_cast<const TextNode *>( this );
	if( node == 0 )
	{
		throw "Invalid cast to TextNode.";
	}
	return node;
}

const TimeStampNode * Node::toTimeStampNode() const
{
	const TimeStampNode *node = dynamic_cast<const TimeStampNode *>( this );
	if( node == 0 )
	{
		throw "Invalid cast to TimeStampNode.";
	}
	return node;
}

}