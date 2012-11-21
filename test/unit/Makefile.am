# Unit tests to be run.
UNIT_TESTS = \
	sample_unittest \
	sample2_unittest

TESTS = $(UNIT_TESTS)
check_PROGRAMS = $(UNIT_TESTS)

sample_unittest_SOURCES = sample_unittest.cpp
sample_unittest_CPPFLAGS = -DWEBVTT_STATIC=1 -I$(top_builddir)/include -I$(top_srcdir)/src/libwebvtt $(GTEST_CPPFLAGS)
sample_unittest_CXXFLAGS = $(CXXFLAGS) $(GTEST_CXXFLAGS)
sample_unittest_LDFLAGS = -static $(GTEST_LDFLAGS)
sample_unittest_LDADD = \
  $(top_builddir)/src/libwebvtt/libwebvtt-static.la \
  $(GTEST_LIBS) \
  $(top_builddir)/test/gtest/libgtest_main.la \
  $(top_builddir)/test/gtest/libgtest.la

sample2_unittest_SOURCES = sample2_unittest.cpp
sample2_unittest_CPPFLAGS = -DWEBVTT_STATIC=1 -I$(top_builddir)/include -I$(top_srcdir)/src/libwebvtt $(GTEST_CPPFLAGS)
sample2_unittest_CXXFLAGS = $(CXXFLAGS) $(GTEST_CXXFLAGS)
sample2_unittest_LDFLAGS = $(GTEST_LDFLAGS)
sample2_unittest_LDADD = \
  $(top_builddir)/src/libwebvtt/libwebvtt-static.la \
  $(GTEST_LIBS) \
  $(top_builddir)/test/gtest/libgtest_main.la \
  $(top_builddir)/test/gtest/libgtest.la
