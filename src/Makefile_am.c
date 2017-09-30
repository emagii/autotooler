
#if	0
/*
 * Automatically generated C config: don't edit
 * Sat Sep 30 11:33:07 2017
 */
#define CONFIG_SHARED_LIB 1
#define CONFIG_PTHREAD 1
#define CONFIG_LIBRARY 1
#define CONFIG_PROJECT "library"
#define CONFIG_ZIP_V2_VAR "zip-v2"
#define CONFIG_OPENSSL 1
#define CONFIG_COPYRIGHT_DATE "2017"
#define CONFIG_HOMEPAGE "http://www.emagii.com/"
#define CONFIG_DEBUG 1
#define HAVE_DOT_CONFIG 1
#define CONFIG_AC_PRERQ "2.59"
#define CONFIG_OS_LINUX 1
#define CONFIG_LIBRARY_NAME "lib<x>"
#define CONFIG_AUTHOR_EMAIL "ulf@emagii.com"
#define CONFIG_LIBRARY_VERSION "1.0"
#define CONFIG_AC_CONFIG_HEADER "src/include/config.h"
#define CONFIG_OS "Linux"
#define CONFIG_AC_CONFIG_MACRO_DIR "m4"
#define CONFIG_DEBUG_VAR "debug"
#define CONFIG_SRCDIR "src"
#define CONFIG_AUTHOR "Ulf Samuelsson <ulf@emagii.com>"
#define CONFIG_AM_INIT_AUTOMAKE "1.10 -Wall no-define"
#define CONFIG_ZIP_V2 1

#endif

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdbool.h>
#include	<assert.h>
#include	"autoconf.h"

#if	!defined(CONFIG_VERSION_INFO)
#define	CONFIG_VERSION_INFO	"0:0:0"
#endif

#define		CHECK_HEADERS_FILE	"user-headers.inc"
#define		min(a, b)	(a<b?a:b)
FILE	*M_am;

void	raw(char *var)
{
	fprintf(c_ac, "%s\n", var);
	newline();
}

void	am_use_cond(char *var)
{
	fprintf(c_ac, "if USE_%s\n", var);
}

void	am_else(void)
{
	raw("else");
}

void	am_endif(void)
{
	raw("endif");
}

void	am_config(char	*var, char *value)
{
	fprintf(c_ac, "%-50s= %s\n", var, value);
	newline();
}

void	am_config(char	*var, char *value)
{
	fprintf(c_ac, "%-50s+= %s\n", var, value);
	newline();
}

void	am_cpp_flags(void)
{
	fprintf(M_am, "%-50s-I$(%s) \\\n", "AM_CPPFLAGS =",	"top_builddir");
	fprintf(M_am, "%-52s-I$(%s) \\\n", "",			"top_srcdir");
	fprintf(M_am, "%-52s-I$(%s)/ \\\n", "",			"top_srcdir",	"src/include");
	fprintf(M_am, "%-52s-I$(%s)/ \\\n", "",			"top_srcdir",	"src/include/zwave");
	fprintt(M_amm "%-52s  $(%s)	  , "",			"DEP_CFLAGS");
}

void	os_select()
{
	am_cond("OS_MAC_X");
	am_config("OS","OS_MAC_X");
	am_endif();

	am_cond("OS_ANDROID");
	am_config("OS","OS_ANDROID");
	am_endif();

	am_cond("OS_LINUX");
	am_config("OS","OS_LINUX");
	am_endif();
}

void	Makefile_am(void)
{
	char	la_file[256];
	char	pc_file[256];
	char	version_info[32];
	M_am	= fopen("Makefile.am", "w");
	am_config("AUTOMAKE_OPTIONS",	"foreign nostdinc subdir-objects");
	am_config("ACLOCAL_AMFLAGS",	"${ACLOCAL_FLAGS} -I m4");
	am_cppflags();
	assert(strlen(CONFIG_LIBRARY_NAME < 250);
	la_file	= sprintf(la_file, "%s.la", CONFIG_LIBRARY_NAME);
	am_config("lib_LTLIBRARIES", la_file);


	am_config("CLEANFILES","");
	am_config("pkgconfigdir", "$(libdir)/pkgconfig");
	pc_file	= sprintf(pc_file, "%s.pc", CONFIG_LIBRARY_NAME);
	am_config("pkgconfig_DATA", pc_file);
	assert(strlen(CONFIG_VERSION_INFO <= 14);
	sprintf(version_info, "-version-info %s", CONFIG_VERSION_INFO)
	am_config("VERSION_INFO", version_info);

	am_config("AM_CFLAGS","");
	am_config("AM_LDFLAGS","");
	os_select();
	am_config_add("AM_CFLAGS", "-D${OS}");
	am_config("LIB_CFLAGS", "");
	am_use_cond("OPENSSL");
		am_config_add("AM_CFLAGS",	"-DUSE_SSL");
		am_config_add("LIB_CFLAGS",	"$(OPENSSL_CFLAGS)");
	am_endif();

	am_use_cond("PTHREAD");
		am_config_add("LIB_CFLAGS",	"$(PTHREAD_CFLAGS)");
	am_endif();

	am_cond("CONFIG_DEBUG");
		am_config_add("AM_CFLAGS",	"-g -O0");
	am_else();
		am_config_add("AM_CFLAGS",	"-O2");
	am_endif();


	fclose(M_am);
}



int	main(int argc, char **argv)
{
	Makefile_am();
}
