/* WebVTT parser
   Copyright 2011 Mozilla Foundation
 */

#include <stdio.h>
#include <stdlib.h>

#include "webvtt.h"

#define FAIL(msg) { \
  fprintf(stderr, "ERROR: " msg "\n"); \
  exit(-1); \
}

int main(int argc, char *argv[])
{
  webvtt_parser *ctx = webvtt_parser_new();

  if (ctx == NULL)
    FAIL("Couldnt' allocate parser context");

  webvtt_parser_free(ctx);

  return 0;
}
