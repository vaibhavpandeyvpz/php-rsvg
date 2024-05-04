dnl $Id$
dnl config.m4 for extension rsvg

sinclude(./autoconf/pecl.m4)
sinclude(./autoconf/php-executable.m4)

PECL_INIT([rsvg])

PHP_ARG_ENABLE(rsvg, whether to enable rsvg, [ --enable-rsvg   Enable rsvg])

if test "$PHP_RSVG" != "no"; then
  AC_DEFINE(HAVE_RSVG, 1, [whether rsvg is enabled])
  PHP_NEW_EXTENSION(rsvg, rsvg.c, $ext_shared)

  PHP_ADD_MAKEFILE_FRAGMENT
  PHP_INSTALL_HEADERS([ext/rsvg], [php_rsvg.h])

  if pkg-config --exists librsvg-2.0; then
    RSVG_VERSION=`pkg-config --modversion librsvg-2.0`
    AC_MSG_RESULT([found RSVG version $RSVG_VERSION pre-installed])
    RSVG_INCS=`pkg-config --cflags-only-I librsvg-2.0`
    RSVG_LIBS=`pkg-config --libs librsvg-2.0`
    PHP_EVAL_INCLINE($RSVG_INCS)
    PHP_EVAL_LIBLINE($RSVG_LIBS, RSVG_SHARED_LIBADD)
    PHP_SUBST(RSVG_SHARED_LIBADD)

    CAIRO_VERSION=`pkg-config --modversion cairo`
    AC_MSG_RESULT([found Cairo version $CAIRO_VERSION pre-installed])
    CAIRO_INCS=`pkg-config --cflags-only-I cairo`
    CAIRO_LIBS=`pkg-config --libs cairo`
    PHP_EVAL_INCLINE($CAIRO_INCS)
    PHP_EVAL_LIBLINE($CAIRO_LIBS, RSVG_SHARED_LIBADD)

    AC_DEFINE(HAVE_LIBRSVG, 1, [whether librsvg exists in the system])
    PHP_SUBST(RSVG_SHARED_LIBADD)
  fi
fi
