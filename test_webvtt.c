/* WebVTT parser
   Copyright 2011 Mozilla Foundation

   This Source Code Form is subject to the terms of the Mozilla
   Public License, v. 2.0. If a copy of the MPL was not distributed
   with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
  webvtt_parser *ctx = webvtt_parse_new();

  if (ctx == NULL)
    FAIL("Couldnt' allocate parser context");

  if (argc > 1) {
    webvtt_cue *cue = webvtt_parse_filename(ctx, argv[1]);
    if (cue == NULL)
      FAIL("No cues returned");
    free(cue);
  }

  webvtt_parse_free(ctx);

  return 0;
}
