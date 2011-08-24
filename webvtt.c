/* WebVTT parser
   Copyright 2011 Mozilla Foundation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "webvtt.h"

#define BUFSIZE 4096

struct webvtt_parser {
  int state;
  char *buffer;
  long offset, length;
};

webvtt_parser *
webvtt_parser_new(void)
{
  webvtt_parser *ctx = malloc(sizeof(*ctx));
  if (ctx) {
  }
  return ctx;
}

void
webvtt_parser_free(webvtt_parser *ctx)
{
  if (ctx) {
    ctx->state = 0;
    if (ctx->buffer)
      free(ctx->buffer);
      ctx->buffer = NULL;
    }
    ctx->offset = 0;
    ctx->length = 0;
}

struct webvtt_cue *
webvtt_parse_file(webvtt_parser *ctx, FILE *in)
{
  struct webvtt_cue *cue = NULL;
  char *p;

  ctx->length = fread(ctx->buffer, 1, BUFSIZE, in);
  ctx->offset = 0;

  p = ctx->buffer;

  // Check for signature
  if (ctx->length < 6) {
    fprintf(stderr, "Too short. Not a webvtt file\n");
    return NULL;
  }
  if (p[0] == (char)0xef && p[1] == (char)0xbb && p[2] == (char)0xbf) {
    fprintf(stderr, "Byte order mark\n");
    p += 3;
  }
  if (memcmp(p, "WEBVTT", 6)) {
    fprintf(stderr, "Bad magic. Not a webvtt file?\n");
    return NULL;
  }

  return cue;
}

struct webvtt_cue *
webvtt_parse_filename(webvtt_parser *ctx, const char *filename)
{
  FILE *in = fopen(filename, "r");
  struct webvtt_cue *cue = NULL;
  
  if (in) {
    cue = webvtt_parse_file(ctx, in);
    fclose(in);
  }
  
  return cue;
}
