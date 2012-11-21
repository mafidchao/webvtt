# Unit tests to be run.
AM_CPPFLAGS = -DWEBVTT_STATIC=1 -I${top_builddir}/include -I${top_srcdir}/include -I${top_srcdir}/src/libwebvtt -I${top_srcdir}/test/gtest $(GTEST_CPPFLAGS)
AM_CXXFLAGS = $(CXXFLAGS)
AM_LDFLAGS = -static

LIBS = \
${top_builddir}/src/libwebvtt/libwebvtt-static.la \
${top_builddir}/test/gtest/libgtest_main.la \
${top_builddir}/test/gtest/libgtest.la \
$(GTEST_LIBS)

UNIT_TESTS = \
	sample_unittest \
	sample2_unittest

TESTS = $(UNIT_TESTS)
check_PROGRAMS = $(UNIT_TESTS)

sample_unittest_SOURCES = sample_unittest.cpp
sample_unittest_LDADD = $(LIBS)

sample2_unittest_SOURCES = sample2_unittest.cpp
sample2_unittest_LDADD = $(LIBS)
