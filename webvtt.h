/* WebVTT parser
   Copyright 2011 Mozilla Foundation

   This Source Code Form is subject to the terms of the Mozilla
   Public License, v. 2.0. If a copy of the MPL was not distributed
   with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

 */

#ifndef _WEBVTT_H_
#define _WEBVTT_H_

/* webvtt files are a sequence of cues
   each cue has a start and end time for presentation
   and some text content (which my be marked up)
   there may be other attributes, but we ignore them
   we store these in a linked list */
typedef struct webvtt_cue webvtt_cue;
struct webvtt_cue {
  char *text;       /** text value of the cue */
  long start, end;  /** timestamps in milliseconds */
  webvtt_cue *next; /** pointer to the next cue */
};


/* context structure for our parser */
typedef struct webvtt_parser webvtt_parser;

/* allocate and initialize a parser context */
webvtt_parser *webvtt_parse_new(void);

/* shut down and release a parser context */
void webvtt_parse_free(webvtt_parser *ctx);

/* read a webvtt file stored in a buffer */
struct webvtt_cue *
webvtt_parse_buffer(webvtt_parser *ctx, char *buffer, long length);

/* read a webvtt file from an open file */
struct webvtt_cue *
webvtt_parse_file(webvtt_parser *ctx, FILE *in);

/* read a webvtt file from a named file */
struct webvtt_cue *
webvtt_parse_filename(webvtt_parser *ctx, const char *filename);

#endif /* _WEBVTT_H_ */
