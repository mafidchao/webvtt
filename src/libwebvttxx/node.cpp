#include <webvttxx/node>
#include <webvttxx/nodefactory>

namespace WebVTT
{	

const Node * Node::parent() const
{
	return NodeFactory::createNode( nodePtr->parent );
}

const Node * InternalNode::child( uint index ) const
{
	if( index <= internalNodePtr->length )
		return NodeFactory::createNode( internalNodePtr->children[index] );
	else 
		return 0;
}

const InternalNode * Node::toInternalNode() const
{
	if( WEBVTT_IS_VALID_INTERNAL_NODE( this->kind() ) )
		return (const InternalNode *)this;
	else
		throw "Invalid cast to InternalNode.";
}

const TextNode * Node::toTextNode() const
{
	if( this->kind() == WEBVTT_TEXT )
		return (const TextNode *)this;
	else
		throw "Invalid cast to TextNode.";
}

const TimeStampNode * Node::toTimeStampNode() const
{
	if( this->kind() == WEBVTT_TIME_STAMP )
		return (const TimeStampNode *)this;
	else
		throw "Invalid cast to TimeStampNode.";
}

}