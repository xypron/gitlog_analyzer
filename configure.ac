dnl Git Log Analyzer

dnl Initialization
AC_INIT([gitlog_analyzer], [0.1], [xypron.glpk@gmx.de])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

dnl Archiver support.
AM_PROG_AR

dnl Enhanced libtool support.
LT_INIT

dnl Compiler check
AC_PROG_CC
AC_CHECK_PROG([have_cc],[$CC],[yes],[no])
if test [$have_cc] != [yes]; then
  AC_MSG_ERROR([$CC is missing])
fi
AC_PROG_CXX
AC_CHECK_PROG([have_cxx],[$CXX],[yes],[no])
if test [$have_cxx] != [yes]; then
  AC_MSG_ERROR([$CXX is missing])
fi

dnl Provide $(LN_S)
AC_PROG_LN_S

dnl Configure macros
AC_CONFIG_MACRO_DIR([m4])

dnl Load pkg.m4
PKG_PROG_PKG_CONFIG

dnl Create config.h
AC_CONFIG_HEADERS([config.h])

dnl Set compiler flags
dnl adjust include path
CPPFLAGS="-I. $CPPFLAGS"

dnl set linker flags
LDFLAGS="-g $LDFLAGS"

AC_MSG_NOTICE([CPPFLAGS = $CPPFLAGS])
AC_MSG_NOTICE([LDFLAGS = $LDFLAGS])

dnl Makefiles
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  ])

dnl Generate files
AC_OUTPUT
