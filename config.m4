dnl $Id$
dnl config.m4 for extension tcpwrap

PHP_ARG_WITH(tcpwrap, for tcpwrap support,
[  --with-tcpwrappers             Include tcpwrappers support])

if test "$PHP_TCPWRAP" != "no"; then

  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/include/tcpd.h"  # you most likely want to change this
  if test -r $PHP_TCPWRAP/; then # path given as parameter
    TCPWRAP_DIR=$PHP_TCPWRAP
  else # search default path list
    AC_MSG_CHECKING([for tcpwrappers files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        TCPWRAP_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$TCPWRAP_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the tcpwrappers distribution])
  fi

  PHP_ADD_INCLUDE($TCPWRAP_DIR/include)

  LIBNAME=wrap
  LIBSYMBOL=request_init

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TCPWRAP_DIR/$PHP_LIB, TCPWRAP_SHARED_LIBADD)
    AC_DEFINE(HAVE_TCPWRAPLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong tcpwrappers lib version or lib not found])
  ],[
    -L$TCPWRAP_DIR/lib -lm -ldl
  ])

  AC_CHECK_FUNC(gethostbyname_r, [have_gethostbyname_r=yes], [have_gethostbyname_r=no])
  if test "$have_gethostbyname_r" = "no"; then
	AC_MSG_ERROR([this extension requires system to support gethostbyname_r function])
  fi

  PHP_SUBST(TCPWRAP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(tcpwrap, tcpwrap.c, $ext_shared)
fi
