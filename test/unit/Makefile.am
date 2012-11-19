# Unit tests to be run.
UNIT_TESTS = \
	sample_test \
	sample_test2

TESTS = $(UNIT_TESTS)
check_PROGRAMS = $(UNIT_TESTS)

sample_test_SOURCES = sample_test.cpp
sample_test_CPPFLAGS = -DWEBVTT_STATIC=1 -I$(top_builddir)/include -I$(top_srcdir)/src/libwebvtt $(GTEST_CPPFLAGS)
sample_test_CXXFLAGS = $(GTEST_CXXFLAGS)
sample_test_LDFLAGS = -static $(GTEST_LDFLAGS)
sample_test_LDADD = \
  $(top_builddir)/src/libwebvtt/libwebvtt-static.la \
  $(GTEST_LIBS) \
  $(top_builddir)/test/gtest/libgtest_main.la \
  $(top_builddir)/test/gtest/libgtest.la

sample_test2_SOURCES = sample_test2.cpp
sample_test2_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/include $(GTEST_CPPFLAGS)
sample_test2_CXXFLAGS = $(GTEST_CXXFLAGS)
sample_test2_LDFLAGS = $(GTEST_LDFLAGS)
sample_test2_LDADD = \
  $(top_builddir)/src/libwebvtt/libwebvtt-static.la \
  $(GTEST_LIBS) \
  $(top_builddir)/test/gtest/libgtest_main.la \
  $(top_builddir)/test/gtest/libgtest.la
