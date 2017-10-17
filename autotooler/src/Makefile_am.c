
#if	0
/*
 * Automatically generated C config: don't edit
 * Mon Oct  2 22:28:59 2017
 */
#define CONFIG_SHARED_LIB 1
#define CONFIG_LIBRARY 1
#define CONFIG_PROJECT "libed25519-donna"
#define CONFIG_WORKDIR "${HOME}/projects/autotooler"
#define CONFIG_OPENSSL 1
#define TARGET_PLATFORM_RASPBERRYPI 1
#define CONFIG_COPYRIGHT_DATE "2017"
#define TARGET_PLATFORM_MT7620 1
#define CONFIG_HOMEPAGE "http://www.emagii.com/"
#define CONFIG_DEBUG 1
#define TARGET_PLATFORM_PC 1
#define CONFIG_LIBRARY_INSTALLDIR ""
#define HAVE_DOT_CONFIG 1
#define CONFIG_AC_PRERQ "2.59"
#define CONFIG_OS_LINUX 1
#define CONFIG_LIBRARY_NAME "libed25519-donna"
#define TARGET_PLATFORM_BEAGLEBONE 1
#define CONFIG_AUTHOR_EMAIL "ulf@emagii.com"
#define CONFIG_LIBRARY_VERSION "1.0"
#define CONFIG_AC_CONFIG_HEADER "src/include/config.h"
#define CONFIG_AC_CONFIG_MACRO_DIR "m4"
#define CONFIG_DEBUG_VAR "debug"
#define CONFIG_PROJECT_TYPE "library"
#define CONFIG_SRCDIR "src"
#define CONFIG_SRC_URI_REPO ""
#define CONFIG_AUTHOR "Ulf Samuelsson"
#define CONFIG_SRC_URI_HOST "https://www.github.com/emagii"
#define CONFIG_AM_INIT_AUTOMAKE "1.10 -Wall no-define"

#endif

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdbool.h>
#include	<assert.h>
#include	"autoconf.h"
#include	<malloc.h>

#define	REQUIRED	1
#define	OPTIONAL	0

#if	!defined(CONFIG_VERSION_INFO)
#define	CONFIG_VERSION_INFO	"0:0:0"
#endif

#define		min(a, b)	(a<b?a:b)
#if	defined(CONFIG_LIBRARY)
#define	STRING_LEN	128
char	library[STRING_LEN];
char	LIBRARY[STRING_LEN];
#endif

FILE	*M_am;

char	*concat(char *s1, char *s2)
{
	int	len1 = strlen(s1);
	int	len2 = strlen(s2);
	char	*s = malloc(len1+len2+1);
	char	*p = s;
	int	i;

	for (i = 0 ; i < len1; i++) {
		*p++ = *s1++;
	}
	for (i = 0 ; i <= len2; i++) {
		*p++ = *s2++;
	}
	return	s;
}

void	sanitize_names(char *arg, int maxlen, char	*name, char *NAME)
{
	int	i, len;
	char	c;
	len=strlen(arg);
	for (i = 0; i <= len ; i++) {	/* also copy trailing NULL char */
		if (i >= maxlen) {
			name[i] = '\0';
			NAME[i] = '\0';
			break;
		}
		c = arg[i];
		if (c == '-')
			c = '_';
		name[i] = c;
		NAME[i] = toupper(c);
	}
}

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
	int	len = strlen(var);
	char	*p = malloc(len+1);
	int	i;
	char	c;
	for (i = 0 ; i <= len; i++) {
		c=var[i];
		if (c == '-') {
			c = '_';
		}
		p[i] = c;
	}

	fprintf(M_am, INDENT "= %s\n", p, value);
	free(p);
}

void	am_config2(char *var1, char *var2, char *value)
{
	char	*name = concat(var1,var2);
	am_config(name, value);
	free(name);
}

void	am_config_add(char	*var, char *value)
{
	int	len = strlen(var);
	char	*p = malloc(len+1);
	int	i;
	char	c;
	for (i = 0 ; i <= len; i++) {
		c=var[i];
		if (c == '-') {
			c = '_';
		}
		p[i] = c;
	}

	fprintf(M_am, INDENT "+= %s\n", p, value);
	free(p);
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
#if	defined(CONFIG_OS_ANDROID)
	am_cond("CONFIG_OS_ANDROID");
	am_config_add("AM_CFLAGS","-DOS_ANDROID");
	am_endif();
#endif
#if	defined(CONFIG_OS_LINUX)
	am_cond("CONFIG_OS_LINUX");
	am_config_add("AM_CFLAGS","-DOS_LINUX");
	am_endif();
#endif
#if	defined(CONFIG_OS_MAC_X)
	am_cond("CONFIG_MAC_OS_X");
	am_config_add("AM_CFLAGS","-DMAC_OS_X");
	am_endif();
#endif
#if	defined(CONFIG_WINDOWS)
#endif

#if	defined(CONFIG_OS_OTHER)
#endif
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
#if	defined(CONFIG_LIBRARY)
	sanitize_names(CONFIG_LIBRARY_NAME, STRING_LEN-1, library, LIBRARY);
	am_config2(LIBRARY,"_VERSION", "$(VERSION)");
#endif
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
#if	defined(CONFIG_OPENSSL)
	am_use_cond("OPENSSL");
		am_config_add("AM_CFLAGS",	"-DUSE_SSL");
		am_config_add("LIB_CFLAGS",	"$(OPENSSL_CFLAGS)");
	am_endif();
#endif
#if	defined(CONFIG_PTHREAD)
	am_use_cond("PTHREAD");
		am_config_add("AM_CFLAGS",	"-pthread");
		am_config_add("LIB_CFLAGS",	"$(PTHREAD_CFLAGS)");
	am_endif();
#endif

#if	defined(CONFIG_DEBUG)
	am_cond("CONFIG_DEBUG");
		am_config_add("AM_CFLAGS",	"-g -O0 -DDEBUG -DCONFIG_DEBUG");
	am_else();
		am_config_add("AM_CFLAGS",	"-O2");
	am_endif();
#endif

#include	"user/user-code-am.inc"
	newline();
	am_config_add("AM_CFLAGS",				"$(LIB_CFLAGS)");
	am_config_add("AM_CFLAGS",				"-Isrc");
	am_config_add("AM_CFLAGS",				"-Isrc/include");
	am_config_add("AM_CFLAGS",				"-Iinclude");
	newline();
	am_config(CONFIG_LIBRARY_NAME "_la_LDFLAGS",		"$(AM_LDFLAGS)");
	am_config(CONFIG_LIBRARY_NAME "_la_CFLAGS",		"$(AM_CFLAGS)");
	am_config(CONFIG_LIBRARY_NAME "_la_CPPFLAGS",		"$(AM_CPPFLAGS)");

	am_installdir();

	raw("# 'csource+headers-am.inc' provides the CSOURCES, HHEADERS and INSTALL_HEADERS defines");

	if(include_raw("user/csource+headers-am.inc",REQUIRED)) {
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
