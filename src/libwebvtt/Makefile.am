lib_LTLIBRARIES = libwebvtt.la
noinst_LTLIBRARIES = libwebvtt-static.la
WEBVTT_SOURCES = alloc.c bytearray.c cue.c cuetext.c error.c lexer.c parser.c string.c
WEBVTT_CFLAGS = -I${top_builddir}/include -I${top_srcdir}/include

libwebvtt_la_LDFLAGS = -no-undefined -shared
libwebvtt_la_CPPFLAGS = -DWEBVTT_BUILD_LIBRARY=1 $(WEBVTT_CFLAGS)
libwebvtt_la_SOURCES = $(WEBVTT_SOURCES)

libwebvtt_static_la_LDFLAGS = -no-undefined -static
libwebvtt_static_la_CPPFLAGS = -DWEBVTT_STATIC=1 $(WEBVTT_CFLAGS)
libwebvtt_static_la_SOURCES = $(WEBVTT_SOURCES)