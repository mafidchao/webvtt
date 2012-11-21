#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([webvtt], [0.0.3])
AC_CANONICAL_HOST

linux="no"
osx="no"
win32="no"

AS_CASE([$host],
  [*-*-linux*],[linux=true gtk=true],
  [*-*-darwin*],[osx=true qt=true],
  [*-mingw*|*-winnt*],[win32=true])

AM_CONDITIONAL(LINUX,test x$linux = xtrue)
AM_CONDITIONAL(OSX,test x$osx = xtrue)
AM_CONDITIONAL(WIN32,test x$win32 = xtrue)

AC_CONFIG_MACRO_DIR([build/autoconf])
AM_INIT_AUTOMAKE([1.11 -Wall -Wno-extra-portability foreign subdir-objects])
AC_CONFIG_SRCDIR([src/libwebvtt/alloc.c])
AC_CONFIG_HEADERS([config.h])

LT_INIT([win32-dll])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_SED
AC_PROG_INSTALL
AC_PROG_MKDIR_P

# Enable debugging (currently only gdb)
AC_ARG_ENABLE([debug],
    [  --enable-debug           build with additional debugging code],
    [CFLAGS='-g'; AC_DEFINE([DEBUG],[1],[Defined if debugging is enabled])])
# Enable profiling (currently only gdb)
AC_ARG_ENABLE([gprof],
	[ --enable-gprof            build with gprof profiling engine],
	[CFLAGS='-pg'; AC_DEFINE([GPROF],[1],[Defined if using gprof profiling engine])])

# Checks for libraries.
# * Check for pthreads library.
ACX_PTHREAD([have_pthread=yes], [heve_pthread=no])
AC_CHECK_FUNC([nanosleep],[HAVE_NANOSLEEP="yes"],[HAVE_NANOSLEEP="no"])

# Define variables for unit test using gtest
GTEST_VERSION="1.6.0"
if [test "x$have_pthread" = "xyes"] && [test "$HAVE_NANOSLEEP" = "yes"]; then
  GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=1 $PTHREAD_CFLAGS"
  GTEST_LIBS="$PTHREAD_LIBS"
  if [test "$PTHREAD_CFLAGS" = "-pthread"]; then
    GTEST_LIBS="$PTHREAD_CFLAGS $GTEST_LIBS"
  fi
else
  GTEST_CPPFLAGS=""
  GTEST_LIBS=""
fi
AC_SUBST([GTEST_VERSION])
AC_SUBST([GTEST_CPPFLAGS])
AC_SUBST([GTEST_LIBS])

# Checks for header files.
AC_CHECK_HEADER([stdint.h],[],[])
AC_CHECK_HEADER([stdlib.h],[],[AC_ERROR([error: missing 'stdlib.h'])])
AC_CHECK_HEADER([string.h],[],[AC_ERROR([error: missing 'string.h'])])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNC([memset],[],[AC_ERROR([error: missing function 'memset'])])
AC_CHECK_FUNC([malloc],[],[AC_ERROR([error: missing function 'malloc'])])
AC_CHECK_FUNC([free],[],[AC_ERROR([error: missing function 'free'])])
AC_CHECK_FUNC([strerror],[AC_DEFINE([HAVE_STRERROR],[1],[Define if strerror() is available])])
# Generate Makefiles
AC_CONFIG_FILES([
  Makefile
  include/Makefile
  src/Makefile
  src/libwebvtt/Makefile
  src/libwebvttxx/Makefile
  src/parsevtt/Makefile
  test/Makefile
  test/gtest/Makefile
  test/unit/Makefile
])

AC_OUTPUT
