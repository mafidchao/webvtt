# Install locations
webvttincludedir = $(includedir)/webvtt
webvttxxincludedir = $(includedir)/webvttxx

# C API headers
webvttinclude_HEADERS = \
$(top_builddir)/include/webvtt/webvtt-config.h \
  webvtt/cue.h \
  webvtt/error.h \
  webvtt/parser.h \
  webvtt/string.h \
  webvtt/util.h

# C++ bindings headers
webvttxxinclude_HEADERS = \
  webvttxx/abstract_parser \
  webvttxx/base \
  webvttxx/cue \
  webvttxx/error \
  webvttxx/file_parser \
  webvttxx/string \
  webvttxx/timestamp

if WIN32
webvttinclude_HEADERS += webvtt/webvtt-config-win32.h
endif
