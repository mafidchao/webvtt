#include <stdlib.h>
#include <string.h>
#include "cue_internal.h"

WEBVTT_EXPORT webvtt_status
webvtt_create_cue( webvtt_cue *pcue )
{
	webvtt_cue cue;
	if( !pcue )
	{
		return WEBVTT_INVALID_PARAM;
	}
	cue = (webvtt_cue)webvtt_alloc0( sizeof(*cue) );
	if( !cue )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	/**
	 * From http://dev.w3.org/html5/webvtt/#parsing (10/25/2012)
	 *
	 * Let cue's text track cue snap-to-lines flag be true.
	 *
	 * Let cue's text track cue line position be auto.
	 *
	 * Let cue's text track cue text position be 50.
	 *
	 * Let cue's text track cue size be 100.
	 *
	 * Let cue's text track cue alignment be middle alignment.
	 */
	webvtt_ref( &cue->refs );
	webvtt_init_string( &cue->id );
	webvtt_init_string( &cue->payload );
	cue->snap_to_lines = 1;
	cue->settings.position = 50;
	cue->settings.size = 100;
	cue->settings.align = WEBVTT_ALIGN_MIDDLE;
	cue->settings.line.no = WEBVTT_AUTO;
	cue->settings.vertical = WEBVTT_HORIZONTAL;

	*pcue = cue;
	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT void
webvtt_ref_cue( webvtt_cue cue )
{
	if( cue )
	{
		webvtt_ref( &cue->refs );
	}
}

WEBVTT_EXPORT void
webvtt_release_cue( webvtt_cue *pcue )
{
	if( pcue && *pcue )
	{
		webvtt_cue cue = *pcue;
		*pcue = 0;
		if( webvtt_deref( &cue->refs ) == 0 )
		{
			webvtt_release_string( &cue->id );
			webvtt_release_string( &cue->payload );
			webvtt_delete_node( cue->node_head );
			webvtt_free( cue );
		}
	}
}

WEBVTT_EXPORT int
webvtt_validate_cue( webvtt_cue cue )
{
	if( cue )
	{
		/**
		 * validate cue-times (Can't do checks against previously parsed cuetimes. That's the applications responsibility
		 */
		if( cue->until <= cue->from )
		{
			goto error;
		}

		/**
		 * Don't do any payload validation, because this would involve parsing the payload, which is optional.
		 */
		return 1;
	}

error:
	return 0;
}

WEBVTT_INTERN webvtt_status  
webvtt_create_node( webvtt_node_ptr *node_pptr, void *concrete_node, webvtt_node_kind kind, webvtt_node_ptr parent_ptr )
{
	webvtt_node_ptr temp_node_ptr = (webvtt_node_ptr)malloc(sizeof(*temp_node_ptr));

	if( !temp_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	temp_node_ptr->concrete_node = concrete_node;
	temp_node_ptr->kind = kind;
	temp_node_ptr->parent = parent_ptr;
	*node_pptr = temp_node_ptr;
		
	return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status  
webvtt_create_internal_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_node_kind kind, webvtt_string_list_ptr css_classes_ptr, webvtt_string annotation )
{
	webvtt_internal_node_ptr internal_node_ptr = (webvtt_internal_node_ptr)malloc(sizeof(*internal_node_ptr));

	if( !internal_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	internal_node_ptr->css_classes_ptr = css_classes_ptr;
	internal_node_ptr->annotation = annotation;
	internal_node_ptr->children = NULL;
	internal_node_ptr->length = 0;
	internal_node_ptr->alloc = 0;

	return webvtt_create_node( node_pptr, (void *)internal_node_ptr, kind, parent_ptr );
}

WEBVTT_INTERN webvtt_status 
webvtt_create_head_node( webvtt_node_ptr *node_pptr )
{
	webvtt_internal_node_ptr internal_node_ptr = (webvtt_internal_node_ptr)webvtt_alloc(sizeof(*internal_node_ptr));

	if ( !internal_node_ptr )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}

	webvtt_init_string(&internal_node_ptr->annotation);
	internal_node_ptr->css_classes_ptr = NULL;
	internal_node_ptr->children = NULL;
	internal_node_ptr->length = 0;
	internal_node_ptr->alloc = 0;

	return webvtt_create_node( node_pptr, (void *)internal_node_ptr, WEBVTT_HEAD_NODE, NULL );	
}

WEBVTT_INTERN webvtt_status  
webvtt_create_time_stamp_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_timestamp time_stamp )
{
	webvtt_leaf_node_ptr leaf_node_ptr = (webvtt_leaf_node_ptr)webvtt_alloc(sizeof(*leaf_node_ptr));

	if( !leaf_node_ptr )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}

	leaf_node_ptr->time_stamp = time_stamp;

	return webvtt_create_node( node_pptr, (void *)leaf_node_ptr, WEBVTT_TIME_STAMP, parent_ptr );		
}

WEBVTT_INTERN webvtt_status  
webvtt_create_text_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_string text )
{
	webvtt_leaf_node_ptr leaf_node_ptr = (webvtt_leaf_node_ptr)malloc(sizeof(*leaf_node_ptr));

	if( !leaf_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	leaf_node_ptr->text = text;
	webvtt_create_node( node_pptr, (void *)leaf_node_ptr, WEBVTT_TEXT, parent_ptr );

	return WEBVTT_SUCCESS;

}

WEBVTT_INTERN void 
webvtt_delete_node( webvtt_node_ptr node_ptr )
{
	if( node_ptr )
	{
		if( WEBVTT_IS_VALID_LEAF_NODE( node_ptr->kind ) )
		{
			webvtt_delete_leaf_node( (webvtt_leaf_node_ptr)node_ptr->concrete_node );
		}
		else if( WEBVTT_IS_VALID_INTERNAL_NODE( node_ptr->kind ) )
		{
			webvtt_delete_internal_node( (webvtt_internal_node_ptr)node_ptr->concrete_node );
		}
		free( node_ptr );
	}
}

WEBVTT_INTERN void 
webvtt_delete_internal_node( webvtt_internal_node_ptr internal_node_ptr )
{
	webvtt_uint i ;

	if( internal_node_ptr )
	{
		webvtt_delete_string_list( &internal_node_ptr->css_classes_ptr );

		if( webvtt_string_length(&internal_node_ptr->annotation) )
		{
			webvtt_release_string( &internal_node_ptr->annotation );
		}
		for( i = 0; i < internal_node_ptr->length; i++ )
		{
			webvtt_delete_node( *(internal_node_ptr->children + i) );
		}
		webvtt_free( internal_node_ptr );
	}
}

WEBVTT_INTERN void 
webvtt_delete_leaf_node( webvtt_leaf_node_ptr leaf_node_ptr )
{
	if( leaf_node_ptr )
	{
		if( webvtt_string_length( &leaf_node_ptr->text ) )
		{
			webvtt_release_string( &leaf_node_ptr->text );
		}
		webvtt_free( leaf_node_ptr );
	}
}

WEBVTT_INTERN webvtt_status 
webvtt_attach_internal_node( webvtt_internal_node_ptr current_ptr, webvtt_node_ptr to_attach_ptr )
{
	if( !current_ptr || !to_attach_ptr )
	{
		return WEBVTT_INVALID_PARAM;
	}

	if( current_ptr->length + 1 >= ( current_ptr->alloc / 3 ) * 2 )
	{
		webvtt_node_ptr *arr, *old;
		current_ptr->alloc = current_ptr->alloc ? current_ptr->alloc * 2 : 8;
		arr = (webvtt_node_ptr *)webvtt_alloc0( sizeof(webvtt_node_ptr) * (current_ptr->alloc));
		if( !arr )
		{
			return WEBVTT_OUT_OF_MEMORY;
		}

		old = current_ptr->children;
		memcpy( arr, old, current_ptr->length * sizeof(webvtt_node_ptr) );
		current_ptr->children = arr;
		webvtt_free( old );
	}

	current_ptr->children[current_ptr->length++] = to_attach_ptr;

	return WEBVTT_SUCCESS;
}