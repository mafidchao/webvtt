#include <webvtt/cue.h>

webvtt_status
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
	cue->snap_to_lines = 1;
	cue->settings.position = 50;
	cue->settings.size = 100;
	cue->settings.align = WEBVTT_ALIGN_MIDDLE;
	cue->settings.line.no = WEBVTT_AUTO;
	cue->settings.vertical = WEBVTT_HORIZONTAL;

	*pcue = cue;
	return WEBVTT_SUCCESS;
}

void
webvtt_delete_cue( webvtt_cue *pcue )
{
	if( pcue && *pcue )
	{
		webvtt_cue cue = *pcue;
		*pcue = 0;
		webvtt_string_delete( cue->id );
		webvtt_string_delete( cue->payload );
		webvtt_free( cue );
	}
}

int
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