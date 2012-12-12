#ifndef __INTERN_CUE_H__
#	define __INTERN_CUE_H__
#	include <webvtt/string.h>
#	include <webvtt/cue.h>

/**
 * Routines for creating nodes.
 */
WEBVTT_INTERN webvtt_status webvtt_create_node( webvtt_node_ptr *node_pptr, void *concrete_node, webvtt_node_kind kind, webvtt_node_ptr parent_ptr );
WEBVTT_INTERN webvtt_status webvtt_create_internal_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_node_kind kind, webvtt_string_list_ptr css_classes_ptr, webvtt_string annotation );
WEBVTT_INTERN webvtt_status webvtt_create_head_node( webvtt_node_ptr *node_pptr );
WEBVTT_INTERN webvtt_status webvtt_create_time_stamp_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_timestamp time_stamp );
WEBVTT_INTERN webvtt_status webvtt_create_text_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_string text );

/**
 * Attaches a node to the internal node list of another node.
 */
WEBVTT_INTERN webvtt_status webvtt_attach_internal_node( webvtt_internal_node_ptr current, webvtt_node_ptr to_attach );

/**
 * Routines for deleting nodes.
 */
WEBVTT_INTERN void webvtt_delete_node( webvtt_node_ptr node_ptr );
WEBVTT_INTERN void webvtt_delete_leaf_node( webvtt_leaf_node_ptr leaf_node_prt );

/**
 * Deletes an internal node as well as it's child nodes. 
 */
WEBVTT_INTERN void webvtt_delete_internal_node( webvtt_internal_node_ptr internal_node_ptr );

/**
 * Private cue flags
 */
enum
{
	CUE_HAVE_VERTICAL = (1<<0),
	CUE_HAVE_SIZE = (1<<1),
	CUE_HAVE_POSITION = (1<<2),
	CUE_HAVE_LINE = (1<<3),
	CUE_HAVE_ALIGN = (1<<4),

	CUE_HAVE_SETTINGS = (CUE_HAVE_VERTICAL|CUE_HAVE_SIZE|CUE_HAVE_POSITION|CUE_HAVE_LINE|CUE_HAVE_ALIGN),

	CUE_HAVE_CUEPARAMS = 0x40000000,
	CUE_HAVE_ID = 0x80000000,
};

#endif