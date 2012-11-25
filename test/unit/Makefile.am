# Unit tests to be run.
AM_CPPFLAGS = \
  -DWEBVTT_STATIC=1 \
  -I$(top_builddir)/include \
  -I$(top_srcdir)/include \
  -I$(top_srcdir)/src/libwebvtt \
  -I$(top_srcdir)/test/gtest \
  $(GTEST_CPPFLAGS)
  
AM_CXXFLAGS = $(AM_CPPFLAGS) $(CXXFLAGS)
AM_LDFLAGS = -static -lm

LIBS = \
  $(top_builddir)/src/libwebvtt/libwebvtt-static.la \
  $(top_builddir)/src/libwebvttxx/libwebvttxx-static.la \
  $(top_builddir)/test/gtest/libgtest_main.la \
  $(top_builddir)/test/gtest/libgtest.la \
  $(GTEST_LIBS)

LDADD = $(LIBS)

CUESETTINGS_TESTS = \
  csgeneric_unittest \
  csline_unittest \
  cssize_unittest \
  csposition_unittest \
  csvertical_unittest \
  csalign_unittest

CUETIMES_TESTS = \
  ctorder_unittest \
  ctseparator_unittest

UNIT_TESTS = \
  sample_unittest \
  sample2_unittest \
  $(CUESETTINGS_TESTS) \
  $(CUETIMES_TESTS) \
  payloadnode_unittest

TESTS = $(UNIT_TESTS)
check_PROGRAMS = $(UNIT_TESTS)

sample_unittest_SOURCES = sample_unittest.cpp
sample2_unittest_SOURCES = sample2_unittest.cpp

# Cue Settings tests
csgeneric_unittest_SOURCES = csgeneric_unittest.cpp
csline_unittest_SOURCES = csline_unittest.cpp
cssize_unittest_SOURCES = cssize_unittest.cpp
csposition_unittest_SOURCES = csposition_unittest.cpp
csvertical_unittest_SOURCES = csvertical_unittest.cpp
csalign_unittest_SOURCES = csalign_unittest.cpp

#Payload Tests
payloadnode_unittest_SOURCES = payloadnode_unittest.cpp

# Cue Times tests
ctorder_unittest_SOURCES = ctorder_unittest.cpp
ctseparator_unittest_SOURCES = ctseparator_unittest.cpp