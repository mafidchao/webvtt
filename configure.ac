#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([webvtt], [0.0.2])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/libwebvtt/alloc.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_SED
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_MKDIR_P

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER([stdint.h],[],[])
AC_CHECK_HEADER([stdlib.h],[],[AC_ERROR([error: missing 'stdlib.h'])])
AC_CHECK_HEADER([string.h],[],[AC_ERROR([error: missing 'string.h'])])
AC_CHECK_HEADER([limits.h],[],[AC_ERROR([error: missing 'limits.h'])])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNC([memset],[],[AC_ERROR([error: missing function 'memset'])])
AC_CHECK_FUNC([malloc],[],[AC_ERROR([error: missing function 'malloc'])])
AC_CHECK_FUNC([free],[],[AC_ERROR([error: missing function 'free'])])
AC_CHECK_FUNC([strerror],[AC_DEFINE([HAVE_STRERROR],[1],[Define if strerror() is available])])
AC_CONFIG_FILES([Makefile include/Makefile src/Makefile src/libwebvtt/Makefile src/parsevtt/Makefile])
AC_OUTPUT
