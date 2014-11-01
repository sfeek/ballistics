AC_PREREQ([2.69])
AC_INIT([ballistics], [0.1.0], [shane.feek@gmail.com])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for platforms.
AS_CASE([$host_os],
	[*cygwin* | *mingw*], [dnl
		is_msw=yes
		LDFLAGS="$LDFLAGS -static-libgcc"
		LIBS="$LIBS -lws2_32"],
	[*linux*], [],
	[AC_MSG_ERROR(your operating system is unsupported.)])

# Checks for libraries.
AC_SEARCH_LIBS([cos], [m], [], [
	AC_MSG_ERROR([unable to find the cos() function.])
])

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdint.h stdlib.h string.h sys/time.h sys/timeb.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([clock_gettime gettimeofday memset])

for SOURCE in $SOURCES; do
	DIRNAME=`echo $(dirname $SOURCE)`
	BASENAME=`echo $(basename $SOURCE)`
	OBJECTS=`echo $OBJECTS $DIRNAME/client-${BASENAME%.*}.$OBJEXT`
done

AC_SUBST(OBJECTS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
