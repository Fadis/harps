lib_LTLIBRARIES = libharps.la
libharps_la_SOURCES = exp2_table.cpp sin_table.cpp module_dir.cpp envelope.cpp

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/include -I$(top_builddir)/include

libharps_la_CPPFLAGS= @BOOST_CPPFLAGS@ @ALSA_CFLAGS@ @TBB_CPPFLAGS@

libharps_la_CXXFLAGS= -DHARPS_MODULE_DIR=$(libdir)/harps/module
# the library search path.
libharps_la_LDFLAGS = @BOOST_LDFLAGS@ $(all_libraries) \
                      @BOOST_LDFLAGS@ @BOOST_FILESYSTEM_LIB@ \
                      @BOOST_THREAD_LIB@ @ALSA_LIBS@ @TBB_LIBS@\
                      -version-info @HARPS_VERSION@ -no-undefined

pkgincludedir= $(includedir)
#pkginclude_HEADERS= iconvxx.h
pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = harps.pc
CLEANFILES = harps.pc
