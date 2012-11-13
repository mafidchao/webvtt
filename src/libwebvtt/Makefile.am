noinst_LIBRARIES = libwebvtt.a
lib_LTLIBRARIES = libwebvtt.la
libwebvtt_la_LDFLAGS = -no-undefined
libwebvtt_a_CFLAGS = -DWEBVTT_STATIC=1 -I${top_builddir}/include -I{top_srcdir}/include
libwebvtt_a_SOURCES = alloc.c bytearray.c cue.c cuetext.c error.c lexer.c parser.c string.c
libwebvtt_la_CFLAGS = -DWEBVTT_BUILD_LIBRARY=1 -I${top_builddir}/include -I{top_srcdir}/include -DWEBVTT_BUILD_LIBRARY=1
libwebvtt_la_SOURCES = alloc.c bytearray.c cue.c cuetext.c error.c lexer.c parser.c string.c
