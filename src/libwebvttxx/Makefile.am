lib_LTLIBRARIES = libwebvttxx.la
noinst_LTLIBRARIES = libwebvttxx-static.la
WEBVTTXX_SOURCES = abstract_parser.cpp cue.cpp file_parser.cpp
WEBVTTXX_CFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include

libwebvttxx_la_LDFLAGS = -no-undefined -shared
libwebvttxx_la_CFLAGS = -DWEBVTTXX_BUILD_LIBRARY=1 $(WEBVTTXX_CFLAGS)
libwebvttxx_la_SOURCES = $(WEBVTTXX_SOURCES)

libwebvttxx_static_la_LDFLAGS = -no-undefined -static
libwebvttxx_static_la_CFLAGS = -DWEBVTTXX_STATIC=1 $(WEBVTTXX_CFLAGS)
libwebvttxx_static_la_SOURCES = $(WEBVTTXX_SOURCES)
