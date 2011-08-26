/* WebVTT parser
   Copyright 2011 Mozilla Foundation
 */

#ifndef _WEBVTT_H_
#define _WEBVTT_H_

/* webvtt files are a sequence of cues
   each cue has a start and end time for presentation
   and some text content (which my be marked up)
   there may be other attributes, but we ignore them
   we store these in a linked list */
struct webvtt_cue {
  char *text;       /** text value of the cue */
  long start, end;  /** timestamps in milliseconds */
  struct cue *next; /** pointer to the next cue */
};
typedef struct webvtt_cue webvtt_cue;


/* context structure for our parser */
typedef struct webvtt_parser webvtt_parser;

/* allocate and initialize a parser context */
webvtt_parser *webvtt_parse_new(void);

/* shut down and release a parser context */
void webvtt_parse_free(webvtt_parser *ctx);

/* read a webvtt file from an open file */
struct webvtt_cue *
webvtt_parse_file(webvtt_parser *ctx, FILE *in);

/* read a webvtt file from a named file */
struct webvtt_cue *
webvtt_parse_filename(webvtt_parser *ctx, const char *filename);

#endif /* _WEBVTT_H_ */
