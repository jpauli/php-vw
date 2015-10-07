dnl $Id$
dnl config.m4 for extension vw

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(vw, for vw support,
dnl Make sure that the comment is aligned:
dnl [  --with-vw             Include vw support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(vw, whether to enable vw support,
dnl Make sure that the comment is aligned:
[  --enable-vw           Enable vw support])

if test "$PHP_VW" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-vw -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/vw.h"  # you most likely want to change this
  dnl if test -r $PHP_VW/$SEARCH_FOR; then # path given as parameter
  dnl   VW_DIR=$PHP_VW
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for vw files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       VW_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$VW_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the vw distribution])
  dnl fi

  dnl # --with-vw -> add include path
  dnl PHP_ADD_INCLUDE($VW_DIR/include)

  dnl # --with-vw -> check for lib and symbol presence
  dnl LIBNAME=vw # you may want to change this
  dnl LIBSYMBOL=vw # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $VW_DIR/$PHP_LIBDIR, VW_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_VWLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong vw lib version or lib not found])
  dnl ],[
  dnl   -L$VW_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(VW_SHARED_LIBADD)

  PHP_NEW_EXTENSION(vw, vw.c, $ext_shared)
fi
