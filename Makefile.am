AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = autogen.sh

bin_PROGRAMS = ballistics

ballistics_CFLAGS = -I $(top_srcdir)/source \
			-I $(top_srcdir)/include

ballistics_LDADD = @OBJECTS@

ballistics_DEPENDENCIES = @OBJECTS@

ballistics_SOURCES = \
	src/bc.c \
	src/ballistics.c \
	src/bclib.c
