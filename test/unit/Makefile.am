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
  ctseparator_unittest \
  cttimestampdelimiter_unittest \
  cttimestamphour_unittest \
  cttimestampminute_unittest \
  cttimestampsecond_unittest \
  cttimestampsecondfrac_unittest

CUEIDS_TESTS = \
  ciarrow_unittest \
  cigeneral_unittest \
  cilanguage_unittest \
  cilineendings_unittest

PAYLOAD_TESTS = \
  plboldtag_unittest \
  plclasstag_unittest \
  plescapecharacter_unittest \
  plformat_unittest \
  plitalictag_unittest \
  pltagformat_unittest \
  pltimestamp_unittest \
  plunderlinetag_unittest \
  plvoicetag_unittest \
  plrubytag_unittest

UNIT_TESTS = \
  sample_unittest \
  sample2_unittest \
  $(CUESETTINGS_TESTS) \
  $(CUETIMES_TESTS) \
  $(CUEIDS_TESTS) \
  $(PAYLOAD_TESTS)

# On TravisCI, we run valgrind for unit tests with --exit-exitcode=1,
# which means otherwise passing tests fail when valgrind fails leak-check.
# Tests added to KNOWN_VALGRIND_TEST_FAILURES will not cause the test run
# to fail. You can run tests with valgrind like so:
#
#   ./configure --enable-valgrind-testing
#   make && make check
KNOWN_VALGRIND_TEST_FAILURES =
if VALGRIND_TESTING
KNOWN_VALGRIND_TEST_FAILURES += \
	csgeneric_unittest \
	csline_unittest \
	cssize_unittest \
	csposition_unittest \
	csvertical_unittest \
	csalign_unittest \
  ctorder_unittest \
  ctseparator_unittest \
  cttimestampminute_unittest \
  cttimestampsecond_unittest \
  cttimestampsecondfrac_unittest \
  ciarrow_unittest \
  cigeneral_unittest \
  cilanguage_unittest \
  cilineendings_unittest
endif

# Tests we expect to fail (i.e., known-fails)
XFAIL_TESTS = $(KNOWN_VALGRIND_TEST_FAILURES)

# TODO: OS X needs to filer gtest valgrind warnings:
# valgrind ... <unittest> 2>&1 | sed -e "/warning: addVar:/d"
TESTS = $(UNIT_TESTS)
TESTS_ENVIRONMENT = $(VALGRIND_ENVIRONMENT)
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

# Cue Times tests
ctorder_unittest_SOURCES = ctorder_unittest.cpp
ctseparator_unittest_SOURCES = ctseparator_unittest.cpp
cttimestampdelimiter_unittest_SOURCES = cttimestampdelimiter_unittest.cpp
cttimestamphour_unittest_SOURCES = cttimestamphour_unittest.cpp
cttimestampminute_unittest_SOURCES = cttimestampminute_unittest.cpp
cttimestampsecond_unittest_SOURCES = cttimestampsecond_unittest.cpp
cttimestampsecondfrac_unittest_SOURCES = cttimestampsecondfrac_unittest.cpp

# Cue Ids Tests
ciarrow_unittest_SOURCES = ciarrow_unittest.cpp
cigeneral_unittest_SOURCES = cigeneral_unittest.cpp
cilanguage_unittest_SOURCES = cilanguage_unittest.cpp
cilineendings_unittest_SOURCES = cilineendings_unittest.cpp

#Payload Tests
plboldtag_unittest_SOURCES = plboldtag_unittest.cpp
plclasstag_unittest_SOURCES = plclasstag_unittest.cpp
plescapecharacter_unittest_SOURCES = plescapecharacter_unittest.cpp
plformat_unittest_SOURCES  = plformat_unittest.cpp
plitalictag_unittest_SOURCES = plitalictag_unittest.cpp
pltagformat_unittest_SOURCES = pltagformat_unittest.cpp
pltimestamp_unittest_SOURCES = pltimestamp_unittest.cpp
plunderlinetag_unittest_SOURCES = plunderlinetag_unittest.cpp
plvoicetag_unittest_SOURCES = plvoicetag_unittest.cpp
plrubytag_unittest_SOURCES = plrubytag_unittest.cpp
