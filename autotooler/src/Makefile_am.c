
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

#define	REQUIRED	1
#define	OPTIONAL	0

#if	!defined(CONFIG_VERSION_INFO)
#define	CONFIG_VERSION_INFO	"0:0:0"
#endif

#define		CHECK_HEADERS_FILE	"user/user-headers.inc"
#define		min(a, b)	(a<b?a:b)
FILE	*M_am;

#define	INDENT	"%-24s"
void	newline(void)
{
	fprintf(M_am, "\n");
}

void	raw(char *var)
{
	fprintf(M_am, "%s\n", var);
}

void	am_use_cond(char *var)
{
	fprintf(M_am, "if USE_%s\n", var);
}

void	am_cond(char *var)
{
	fprintf(M_am, "if %s\n", var);
}

void	am_else(void)
{
	raw("else");
}

void	am_endif(void)
{
	raw("endif");
	newline();
}

void	am_config(char	*var, char *value)
{
	fprintf(M_am, INDENT "= %s\n", var, value);
}

void	am_config_add(char	*var, char *value)
{
	fprintf(M_am, INDENT "+= %s\n", var, value);
}

void	am_cppflags(void)
{
	fprintf(M_am, INDENT "-I$(%s) \\\n",	"AM_CPPFLAGS =",	"top_builddir");
	fprintf(M_am, INDENT "-I$(%s) \\\n",	"",			"top_srcdir");
	fprintf(M_am, INDENT "  $(%s)\n",	 	"",		"DEP_CFLAGS");
	newline();
}

void	os_select()
{
	am_cond("CONFIG_OS_ANDROID");
	am_config_add("AM_CFLAGS","-DOS_ANDROID");
	am_endif();

	am_cond("CONFIG_OS_LINUX");
	am_config_add("AM_CFLAGS","-DOS_LINUX");
	am_endif();

	am_cond("CONFIG_MAC_OS_X");
	am_config_add("AM_CFLAGS","-DMAC_OS_X");
	am_endif();


}

void api_headers(void)
{
	FILE	*API	= fopen("api_headers.dat", "r");
	char	*line, *p;
	char	header_name[256];
	int	len,i;

	fprintf(M_am, INDENT " \\\n", CONFIG_LIBRARY_NAME "_la_HEADERS =");
	while(1) {
		line = fgets(header_name, 250, API);
		if (line == NULL)
			break;
		len = strlen(line);
		for (i = 0, p = line; i < len; p++, i++) {
			if (*p == '\n')
				*p = '\0';
			if (*p == '\r')
				*p = '\0';
		}
		printf("\t%s\n", line);
		fprintf(M_am, "\t%s \\\n", line);
	}
	fclose(API);
}

int	include_raw(char	*filename, int required)
{
	FILE	*f;
	char	*line, *p;
	char	buffer[1030];

	f = fopen(filename, "r");
	if (f == NULL) {
		if (required == REQUIRED) {
			return	-1;
		} else {
			return	0;
		}
	}
	while(1) {
		line = fgets(buffer, 1024, f);
		if (line == NULL)
			break;
		fprintf(M_am, "%s", line);
	}
	newline();
	fclose(f);
	return	0;
}


am_installdir ()
{
	char	*p = CONFIG_LIBRARY_INSTALLDIR;
	char	*installdir;
	if (*p) {
		installdir = "$(include)" "/" CONFIG_LIBRARY_INSTALLDIR;
	} else {
		installdir = "$(include)";
	}
	am_config("INSTALLdir",		installdir);
}

void	Makefile_am(void)
{
	char	version_info[32];
	int	sts;
	M_am	= fopen("Makefile.am", "w");
	am_config("AUTOMAKE_OPTIONS",	"foreign nostdinc subdir-objects");
	newline();
	am_config("ACLOCAL_AMFLAGS",	"${ACLOCAL_FLAGS} -I m4");
	newline();
	am_config("AM_CFLAGS","");
	am_config("AM_LDFLAGS","");
	am_cppflags();
	newline();
	am_config("lib_LTLIBRARIES", CONFIG_LIBRARY_NAME ".la");
	newline();
	am_config("CLEANFILES","");
	newline();
	am_config("pkgconfigdir", "$(libdir)/pkgconfig");
	am_config("pkgconfig_DATA", CONFIG_LIBRARY_NAME ".pc");
	newline();
	sprintf(version_info, "-version-info %s", CONFIG_VERSION_INFO);
	am_config("VERSION_INFO", version_info);
	newline();

	os_select();
	newline();
	am_config("LIB_CFLAGS", "");
	newline();
	am_use_cond("OPENSSL");
		am_config_add("AM_CFLAGS",	"-DUSE_SSL");
		am_config_add("LIB_CFLAGS",	"$(OPENSSL_CFLAGS)");
	am_endif();

	am_use_cond("PTHREAD");
		am_config_add("AM_CFLAGS",	"-pthread");
		am_config_add("LIB_CFLAGS",	"$(PTHREAD_CFLAGS)");
	am_endif();

	am_cond("CONFIG_DEBUG");
		am_config_add("AM_CFLAGS",	"-g -O0 -DDEBUG -DCONFIG_DEBUG");
	am_else();
		am_config_add("AM_CFLAGS",	"-O2");
	am_endif();

#include	"user/user-code-am.inc"
	newline();
	am_config_add("AM_CFLAGS",				"$(LIB_CFLAGS)");
	newline();
	am_config(CONFIG_LIBRARY_NAME "_la_LDFLAGS",		"$(AM_LDFLAGS)");
	am_config(CONFIG_LIBRARY_NAME "_la_CFLAGS",		"$(AM_CFLAGS)");
	am_config(CONFIG_LIBRARY_NAME "_la_CPPFLAGS",		"$(AM_CPPFLAGS)");

	am_installdir();

	raw("# Sources.inc provides the CSOURCES, HHEADERS and INSTALL_HEADERS defines");

	if(include_raw("user/Sources.inc",REQUIRED)) {
		perror("Source and Header definitions missing");
		goto	exit;
	}

	am_config(CONFIG_LIBRARY_NAME "_la_SOURCES",		"$(CSOURCES) $(HHEADERS)");

#if	defined(CONFIG_INCLUDE_DIR)
	am_config(CONFIG_LIBRARY_NAME "_ladir",			"$(includedir)/" CONFIG_INCLUDE_DIR);
#else
	am_config(CONFIG_LIBRARY_NAME "_ladir",			"$(includedir)");
#endif

	am_config(CONFIG_LIBRARY_NAME "_la_HEADERS",		"$(INSTALL_HEADERS)\n");

	raw("clean-local:");
exit:
	fclose(M_am);
}

int	main(int argc, char **argv)
{
	Makefile_am();
}
