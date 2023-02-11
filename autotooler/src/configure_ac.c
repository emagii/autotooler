
#if	0
/*
 * Automatically generated C config: don't edit
 * Sun Oct  1 10:14:27 2017
 */
#define CONFIG_SHARED_LIB 1
#define CONFIG_OS_ANDROID 1
#define CONFIG_OS_MAC_X 1
#define CONFIG_OS_LINUX 1
#define CONFIG_SIMPLE_AV_VAR "simple-av"
#define CONFIG_PTHREAD 1
#define CONFIG_LIBRARY 1
#define CONFIG_PROJECT "libzip_api"
#define CONFIG_TCP_PORTAL 1
#define CONFIG_ZIP_V2_VAR "zip-v2"
#define CONFIG_WORKDIR "${HOME}/projects/autotooler"
#define CONFIG_OPENSSL 1
#define CONFIG_COPYRIGHT_DATE "2017"
#define CONFIG_HOMEPAGE "http://www.emagii.com/"
#define CONFIG_TCP_PORTAL_VAR "tcp-portal"
#define CONFIG_DEBUG 1
#define HAVE_DOT_CONFIG 1
#define CONFIG_AC_PRERQ "2.59"
#define CONFIG_LIBRARY_NAME "libzip_api"
#define CONFIG_AUTHOR_EMAIL "ulf@emagii.com"
#define CONFIG_LIBRARY_VERSION "7.38"
#define CONFIG_AC_CONFIG_HEADER "src/user/config.h"
#define CONFIG_AC_CONFIG_MACRO_DIR "m4"
#define CONFIG_DEBUG_VAR "debug"
#define CONFIG_PROJECT_TYPE "library"
#define CONFIG_SIMPLE_AV 1
#define CONFIG_SRCDIR "src"
#define CONFIG_SRC_URI_REPO ""
#define CONFIG_AUTHOR "Ulf Samuelsson"
#define CONFIG_SRC_URI_HOST "https://www.github.com/emagii"
#define CONFIG_AM_INIT_AUTOMAKE "1.10 -Wall no-define"
#define CONFIG_ZIP_V2 1
#endif

#include	<stdio.h>
#include	<stdint.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdbool.h>
#include	<ctype.h>
#include	<assert.h>
#include	"autoconf.h"
#include	<malloc.h>


#define		CHECK_HEADERS_FILE	"user/user-headers-ac.inc"
#define		min(a, b)	(a<b?a:b)
FILE	*c_ac;
#define	STRING_LEN	128
char	LIBRARY[STRING_LEN];
char	library[STRING_LEN];

#define	INDENT	"%-24s"

#define	F_CC	(1 << 0)
#define	F_CXX	(1 << 1)
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

void	ac_simple(char	*s)
{
	fprintf(c_ac, "%s\n", s);
}

void	newline(void)
{
	ac_simple("");
}

void	ac_assign(char	*var, char *value)
{
	fprintf(c_ac, INDENT "= %s\n", var, value);
}

void	ac_assign2(char	*var1, char *var2, char *value)
{
	char	*name = concat(var1, var2);
	ac_assign(name, value);
	free(name);
}

#if	defined(CONFIG_LIBRARY)
void	ac_init_library(void)
{
	fprintf(c_ac, "AC_INIT(");
	fprintf(c_ac, "[%s],\n", CONFIG_LIBRARY_NAME);
	fprintf(c_ac, "\t[%s],\n", CONFIG_LIBRARY_VERSION);
	fprintf(c_ac, "\t[%s],\n", CONFIG_AUTHOR);
	fprintf(c_ac, "\t[%s-%s],\n", CONFIG_LIBRARY_NAME, CONFIG_LIBRARY_VERSION);
	fprintf(c_ac, "\t[%s]", CONFIG_HOMEPAGE);
	fprintf(c_ac, ")\n");
	newline();
}
#endif
#if	defined(CONFIG_APP)
void	ac_init_app(void)
{
	fprintf(c_ac, "AC_INIT(");
	fprintf(c_ac, "[%s],\n", CONFIG_APP_NAME);
	fprintf(c_ac, "\t[%s],\n", CONFIG_APP_VERSION);
	fprintf(c_ac, "\t[%s],\n", CONFIG_AUTHOR);
	fprintf(c_ac, "\t[%s-%s],\n", CONFIG_APP_NAME, CONFIG_APP_VERSION);
	fprintf(c_ac, "\t[%s]", CONFIG_HOMEPAGE);
	fprintf(c_ac, ")\n");
	newline();
}
#endif

void	ac_init(void)
{
#if	defined(CONFIG_LIBRARY)
	ac_init_library();
#endif
#if	defined(CONFIG_APP)
	ac_init_app();
#endif
}

void	ac_define(char *var)
{
	fprintf(c_ac, "AC_DEFINE(%s)\n", var);
}

void	ac_subst(char *var)
{
	fprintf(c_ac, "AC_SUBST(%s)\n", var);
}

void	ac_subst2(char *var1, char *var2)
{
	fprintf(c_ac, "AC_SUBST(%s%s)\n", var1, var2);
}

void	ac_subst_val(char *var, char *value)
{
	fprintf(c_ac, "AC_SUBST(%s, %s)\n", var, value);
}

void	ac_subst2_val(char *var1, char *var2, char *value)
{
	fprintf(c_ac, "AC_SUBST(%s%s, %s)\n", var1, var2, value);
}

void	ac_define3(char *var, char *value, char *description)
{
	fprintf(c_ac, "AC_DEFINE(%s, %s, [%s])\n", var, value, description);
}

void	ac_config(char	*var, char *value)
{
	fprintf(c_ac, "%s([%s])\n", var, value);
	newline();
}

void	ac_check_lib (char *func, char *library)
{
	fprintf(c_ac, "AC_CHECK_LIB(%s, %s)\n", func, library);
	newline();
}

void	ac_check_sizeof(char	*type)
{
	fprintf(c_ac, "AC_CHECK_SIZEOF(%s)\n", type);
	newline();
}

void	ac_config_macro_dir()
{
	char	*p = CONFIG_AC_CONFIG_MACRO_DIR;
	if (*p) {
		ac_config("AC_CONFIG_MACRO_DIR",p);
	}
	newline();
}

void	default_includes (void)
{
	ac_simple("#ifdef HAVE_SYS_TYPES_H");
	ac_simple("#include <sys/types.h>");
	ac_simple("#endif");
	ac_simple("#ifdef HAVE_SYS_TIME_H");
	ac_simple("#include <sys/time.h>");
	ac_simple("#endif");
	ac_simple("dnl We do this default-include simply to make sure that the nameser_compat.h");
	ac_simple("dnl header *REALLY* can be include after the new nameser.h. It seems AIX 5.1");
	ac_simple("dnl (and others?) is not designed to allow this.");
	ac_simple("#ifdef HAVE_ARPA_NAMESER_H");
	ac_simple("#include <arpa/nameser.h>");
	ac_simple("#endif");
	ac_simple("");
	ac_simple("dnl *Sigh* these are needed in order for net/if.h to get properly detected.");
	ac_simple("#ifdef HAVE_SYS_SOCKET_H");
	ac_simple("#include <sys/socket.h>");
	ac_simple("#endif");
	ac_simple("#ifdef HAVE_NETINET_IN_H");
	ac_simple("#include <netinet/in.h>");
	ac_simple("#endif");
}

void	ac_check_headers(char *headers_file)
{
	FILE	*headers;
	char	 header_name[256];
	char	*line = header_name;
	char	*p;
	int	len, i;
	headers	= fopen(headers_file, "r");
	printf("Opening %s for headers\n", headers_file);
	if (headers == NULL) {
		fprintf(stderr, "Could not open '%s', not checking headers\n", headers_file);
		return;
	}
	strcpy(header_name, "Cannot open header file");

	fprintf(c_ac, "AC_CHECK_HEADERS( \\\n");
	while(1) {
		line = fgets(header_name, 250, headers);
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
		fprintf(c_ac, "\t%s \\\n", line);
	}
	fclose(headers);

	fprintf(c_ac, "\t,\n");
	fprintf(c_ac, "dnl to do if not found\n");
	fprintf(c_ac, "\t[],\n");
	fprintf(c_ac, "dnl to do if not found\n");
	fprintf(c_ac, "\t[],\n");
	fprintf(c_ac, "dnl default includes\n");
	fprintf(c_ac, "\t[\n");
	default_includes();
	fprintf(c_ac, "]\n");
	fprintf(c_ac, ")\n");
	newline();
}

void	ac_arg_enable(char *arg, char *help, bool lib)
{
	int	i,len;
	char	*default_help = "";
	char	variable[STRING_LEN];
	char	VARIABLE[STRING_LEN];
	char	*CONFIG = "CONFIG";
	char	c;
	char	*use;
//	printf("ac_arg_enable\n");
	if (lib) {
		use = "use_";
		CONFIG = "USE";
	} else {
		use = "";
	}
	fprintf(c_ac, "AC_ARG_ENABLE(%s,\n", arg);
	fprintf(c_ac, "\t[--enable-%s", arg);
	if (help != NULL) {
		fprintf(c_ac, "\t%s", help);
	}

	/* change '-' to '_' for a legal variable name */
	/* Create upper case "VARIABLE" */
	sanitize_names(arg, STRING_LEN-1 , variable, VARIABLE);
	fprintf(c_ac, "],\n");

	fprintf(c_ac, "\t[case \"${enableval}\" in\n");
	fprintf(c_ac, "\t\tyes)\t%s%s=true  ;;\n", use, variable);
	fprintf(c_ac,  "\t\tno)\t%s%s=false ;;\n", use, variable);
	fprintf(c_ac,   "\t\t*) AC_MSG_ERROR(bad value ${enableval} for --enable-%s) ;;\n", arg);
	fprintf(c_ac, "\t esac\n");
	fprintf(c_ac, "\t],\n");
	fprintf(c_ac, "\t[%s%s=false])\n", use, variable);
	fprintf(c_ac, "AS_IF([test	x$%s%s = xtrue], [AC_DEFINE([%s], [], [Description])])\n", use, variable, VARIABLE);
	fprintf(c_ac, "AM_CONDITIONAL(%s_%s, test x$%s%s = xtrue)\n", CONFIG, VARIABLE, use, variable);
	newline();
}

/*	Typical call
 *	ac_arg_with_default(
 *		.library	=	"openssl",
 *		.var		"	"OPENSSL"
 *		.libname	=	"ssl",
 *		.name		=	"OpenSSL",
 *		.prefix		=	"/usr",
 *		.flags		=	F_CC,
 *		.def		=	YES
 *	);
 */
void	ac_arg_with_default(char *library, char *var, char *libname, char *name, char *prefix, int flags, int def)
{
	int	i,len;
	char	library_sanitized[STRING_LEN];
	char	LIBRARY[STRING_LEN];
	char	c;
	char	*symbol;
//	printf("ac_arg_with_default");
	sanitize_names(library, STRING_LEN-1, library_sanitized, LIBRARY);
	fprintf(c_ac, "AC_ARG_WITH([%s],\n", library);
#if	0
	fprintf(c_ac, "\t"
		"[AS_HELP_STRING("
			"[--with-%s=DIR\tcompile to use %s, defaults to %s]"
		")],\n",
		library,
		name,
		0?"yes":"no");
#else
	fprintf(c_ac, "\t"	"[--with-%s=DIR\tcompile to use %s", library, name);
	if (def > 0) {
		fprintf(c_ac, ", defaults to %s", 0?"yes":"no");
	}
	fprintf(c_ac, "],\n");
#endif
	fprintf(c_ac, "\t"	"%sDIR=$withval", LIBRARY);
	if (def > 0) {
		fprintf(c_ac, "\t"	", with_%s=%s\n", library_sanitized, 0?"yes":"no");
	}
	fprintf(c_ac, ")\n");

	fprintf(c_ac,	"if test \"$with_%s\" != \"no\"\n", library_sanitized);
	fprintf(c_ac,	"then\n");
			fprintf(c_ac,	"\t");
			ac_define3(var,"[]","[]");
	fprintf(c_ac,	"\t"	"LIBS=\"-l%s ${LIBS}\"\n",libname);
	fprintf(c_ac,	"\t"	"SLIBS=\"-l%s ${SLIBS}\"\n",libname);
	fprintf(c_ac,	"\t"	"if test \"$%sDIR\" -a \"$%sDIR\" != \"yes\"; then\n", LIBRARY, LIBRARY);
	fprintf(c_ac,	"\t\t"		"LIBS=\"-L$%sDIR/.libs -L$%sDIR/lib -L$%sDIR $LIBS\"\n", LIBRARY, LIBRARY, LIBRARY);
	fprintf(c_ac,	"\t\t"		"CPPFLAGS=\"-I$%sDIR/include $CPPFLAGS\" \n", LIBRARY);
	fprintf(c_ac,	"\t"	"fi\n");
	fprintf(c_ac,	"fi\n");
	newline();
}

/*	Typical call
 *	ac_arg_with_library_default(
 *		.library	=	"openssl",
 *		.var		"	"OPENSSL"
 *		.libname	=	"ssl",
 *		.name		=	"OpenSSL",
 *		.prefix		=	"/usr",
 *		.flags		=	F_CC,
 *		.def		=	YES
 *	);
 */
void	ac_arg_with_library_default(char *library, char *var, char *libname, char *name, char *prefix, int flags, int def)
{
	int	i,len;
	char	library_sanitized[STRING_LEN];
	char	LIBRARY[STRING_LEN];
	char	c;
	char	*symbol;
//	printf("ac_arg_with_default");
	sanitize_names(library, STRING_LEN-1, library_sanitized, LIBRARY);
	fprintf(c_ac, "AC_ARG_WITH(\n");
	fprintf(c_ac, "\t[%s-library],\n", library);
	fprintf(c_ac, "\t"	"AC_HELP_STRING("					"\n");
	fprintf(c_ac, "\t\t"		"[--with-%s-library],"				"\n", library);
	fprintf(c_ac, "\t\t"		"[Build with specified (static) library.]"	"\n");
	fprintf(c_ac, "\t"	"),"							"\n");

	fprintf(c_ac, "\t"	"[%s_LIBRARY=$with_%s]"					"\n", LIBRARY, library_sanitized);
	fprintf(c_ac, "\t"	"[%s_LIBRARY=\"-l%s\"]"					"\n", LIBRARY, libname);
	fprintf(c_ac, ")"								"\n");
	newline();
	ac_subst2(LIBRARY, "_LIBRARY");
}

/*	Typical call
 *	ac_arg_with(
 *		.library	=	"openssl",
 *		.libname	=	"ssl",
 *		.name		=	"OpenSSL",
 *		.path		=	"/usr/lib",
 *		.flags		=	F_CC|F_CXX
 *	);
 */
void	ac_arg_with(char *library, char *var, char *libname, char *name, char *prefix, int flags)
{
	ac_arg_with_default(library, var, libname, name, prefix, flags, -1);
}

/*	Typical call
 *	ac_arg_with_include(
 *		.library	=	"openssl",
 *		.libname		=	"ssl",
 *		.name		=	"OpenSSL",
 *		.path		=	"/usr/lib",
 *		.flags		=	F_CC
 *	);
 */
void	ac_arg_with_include (char *library, char *libname, char *name, char *path, int flags)
{
	int	i,len;
	char	LIBRARY[STRING_LEN];
	char	library_sanitized[STRING_LEN];
	char	c;
	char	*symbol;
//	printf("ac_arg_with_include\n");
	fprintf(c_ac, "AC_ARG_WITH([%s-include-path],\n", library);
	fprintf(c_ac, "\t"
		"[AS_HELP_STRING("
			"[--with-%s-include-path]"			","
			"[location of the %s headers, defaults to %s]"
		")],\n",
		library,
		name,
		path);
	sanitize_names(library, STRING_LEN-1, library_sanitized, &LIBRARY[0]);
	if (flags & F_CC) {
		symbol = "CFLAGS";
	} else if (flags & F_CXX) {
		symbol = "CXXFLAGS";
	} else {
		symbol = "BADFLAGS";
	}
	fprintf(c_ac, "\t[%s_%s=\"-I$withval\"],\n",	LIBRARY, symbol);
	fprintf(c_ac, "\t[%s_%s=\"-I%s\"])\n",		LIBRARY, symbol,  path);

	fprintf(c_ac, "AC_SUBST([%s_%s])\n", LIBRARY, symbol);
	newline();
}

/*	Typical call
 *	ac_arg_with_lib_path(
 *		.library	=	"openssl",
 *		.libname	=	"ssl",
 *		.name		=	"OpenSSL",
 *		.path		=	"/usr/lib",
 *		.flags		=	F_CC
 *	);
 */

void	ac_arg_with_lib_path(char *library, char *libname,char *name, char *path, int flags)
{
	int	i,len;
	char	LIBRARY[STRING_LEN];
	char	library_sanitized[STRING_LEN];
	char	c;
//	printf("ac_arg_with_lib_path\n");

	fprintf(c_ac, "AC_ARG_WITH([%s-lib-path],\n", library);
	fprintf(c_ac, "\t"
		"[AS_HELP_STRING("
			"[--with-%s-lib-path]"			","
			"[location of the %s libraries, defaults to %s]"
		")],\n",
		library,
		name,
		path);
	sanitize_names(library, STRING_LEN-1, library_sanitized, LIBRARY);

	fprintf(c_ac, "\t[%s_LIBS=\"-L$withval -l%s\"],\n", LIBRARY , /* library_sanitized, */libname);
	fprintf(c_ac, "\t[%s_LIBS=\"-L%s -l%s\"])\n", LIBRARY, path, libname);

	fprintf(c_ac, "AC_SUBST([%s_LIBS])\n", LIBRARY);
	newline();
}


void	pkg_check_modules(char *name, char *lib, char *min_version)
{
	fprintf(c_ac, "PKG_CHECK_MODULES([%s], [%s >= %s],,\n", name, lib, min_version);
	fprintf(c_ac, "\tAC_MSG_ERROR([%s %s or newer not found.])\n", lib, min_version);
	fprintf(c_ac, ")\n");
}

void	ac_config_files()
{
	fprintf(c_ac, "AC_CONFIG_FILES([Makefile");
#if	defined(CONFIG_LIBRARY)
	fprintf(c_ac, " %s.pc", CONFIG_LIBRARY_NAME);
#endif
	fprintf(c_ac, "])\n");
}

#if	0
int MAX_PATH_LENGTH = 80;
char* path[MAX_PATH_LENGTH];
getcwd(path, MAX_PATH_LENGTH);
printf("Current Directory = %s", path);
#endif

void	ac_set_version()
{
}

void	add_to_CFLAGS(char *s)
{
	fprintf(c_ac, "CFLAGS='${CFLAGS} ${%s_CFLAGS}'\n", s);
}

void	add_to_LIBS(char *s)
{
	fprintf(c_ac, "LIBS='${LIBS} ${%s_LIBS}'\n", s);
}

void	configure_ac(void)
{
	c_ac	= fopen("configure.ac", "w");
	if (c_ac == NULL) {
		perror("ERROR");
		exit(1);
	}

	ac_init();
	ac_config("AC_PREREQ",		CONFIG_AC_PRERQ);

	ac_config("AC_CONFIG_HEADER",	CONFIG_AC_CONFIG_HEADER);
	ac_config("AC_CONFIG_SRCDIR",	CONFIG_SRCDIR);

	ac_config_macro_dir();

	ac_simple("AC_PROG_LN_S");
	ac_simple("AC_PROG_CPP");
	ac_simple("AC_PROG_CC");
	ac_simple("AC_ARG_PROGRAM");
	ac_config("AM_INIT_AUTOMAKE",	CONFIG_AM_INIT_AUTOMAKE);
	ac_simple("AC_PROG_MAKE_SET");
	ac_simple("AM_MAINTAINER_MODE");
#if	defined(CONFIG_LIBRARY)
	sanitize_names(CONFIG_LIBRARY_NAME, STRING_LEN-1, library, LIBRARY);
	ac_subst2_val(LIBRARY, "_VERSION", CONFIG_LIBRARY_VERSION);
#endif
	ac_simple("AC_HEADER_STDC");
#if	defined(CONFIG_SHARED_LIB)
	ac_simple("AC_ENABLE_SHARED");
	ac_simple("AC_DISABLE_STATIC");
#endif
#if	defined(CONFIG_STATIC_LIB)
	ac_simple("AC_DISABLE_SHARED");
	ac_simple("AC_ENABLE_STATIC");
#endif
	ac_simple("AC_PROG_LIBTOOL");
#if	0
	ac_simple("dnl make sure we keep ACLOCAL_FLAGS around for maintainer builds to work");
	ac_simple("AC_SUBST(ACLOCAL_AMFLAGS, \"$ACLOCAL_FLAGS\")");
#else
	ac_simple("AC_SUBST(ACLOCAL_AMFLAGS, \"\")");
#endif
	ac_simple("AC_HEADER_STDC");

	ac_simple("AC_C_CONST");
	ac_simple("AC_TYPE_SIZE_T");
	ac_simple("AC_HEADER_TIME");
	ac_simple("");

	newline();
	ac_check_headers(CHECK_HEADERS_FILE);

#if	defined(CONFIG_BOOST)
	ac_simple("# ==== Boost Libraries");
	ac_arg_with_include ("boost", "", "Boost", "/usr/include/boost",F_CXX);
	ac_arg_with_lib_path("boost",
		   "boost_system"
		" -lboost_filesystem"
		" -lboost_program_options"
		" -lboost_thread"
		" -lpthread",
		"Boost", "/usr/lib",F_CXX);
	ac_arg_enable("boost", "Include Boost Libraries", true);
#endif

#if	defined(CONFIG_CURL)
	ac_simple("# ==== cURL Libraries");
	ac_arg_with_include ("curl", "curl", "cURL", "/usr/include",F_CXX);
	ac_arg_with_lib_path("curl", "curl", "cURL", "/usr/lib",F_CXX);
	ac_arg_enable("curl", "Include cURL", true);
#endif

#if	defined(CONFIG_CURLPP)
	ac_simple("# ==== cURLPP Libraries");
	ac_arg_with_include ("curlpp", "curlpp", "cURLPP", "/usr/include",F_CXX);
	ac_arg_with_lib_path("curlpp", "curlpp -lutilspp", "cURLPP", "/usr/lib",F_CXX);
	ac_arg_enable("curlpp", "Include cURLPP", true);
#endif

#if	defined(CONFIG_FTD2XX)
	ac_simple("# ==== FTDI D2XX Libraries");
	ac_arg_with_include ("ftd2xx", "ftd2xx", "FTDI D2XX", "/usr/local/include",F_CXX);
	ac_arg_with_lib_path("ftd2xx", "ftd2xx", "FTDI D2XX", "/usr/local/lib",F_CXX);
	ac_arg_enable("ftd2xx", "Include FTD2XX", true);
#endif

#if	defined(CONFIG_OPENSSL)
	ac_simple("# ==== OpenSSL Libraries");
	ac_arg_with_include ("openssl", "ssl", "OpenSSL", "/usr/include",F_CC);
	ac_arg_with_lib_path("openssl", "ssl", "OpenSSL", "/usr/lib",F_CC);
	ac_arg_enable("openssl", "Include OpenSSL", true);
	ac_arg_with ("openssl", "OPENSSL", "crypto", "OpenSSL", "/usr",F_CC);
#endif

#if	defined(CONFIG_WESTON)
	pkg_check_modules("weston", "weston", "3");
	ac_subst("WESTON_CFLAGS");
	ac_subst("WESTON_LIBS");
//	add_to_CFLAGS("weston");

#endif

#if	defined(CONFIG_LIBEVDEV)
	pkg_check_modules("libevdev", "libevdev", "1.0");
	ac_subst("LIBEVDEV_CFLAGS");
	ac_subst("LIBEVDEV_LIBS");
//	add_to_CFLAGS("libevdev");
#endif

#if	defined(CONFIG_PIXMAN)
	pkg_check_modules("PIXMAN", "pixman-1", "0.29.1");
	ac_subst("PIXMAN_CFLAGS");
	ac_subst("PIXMAN_LIBS");
//	add_to_CFLAGS("pixman");
#endif

#if	defined(CONFIG_PTHREAD)
	ac_simple("# ==== Pthread Libraries");
	ac_arg_with_include ("pthread", "pthread", "PThread", "/usr/include",F_CC);
	ac_arg_with_lib_path("pthread", "pthread", "PThread", "/usr/lib",F_CC);
	ac_arg_enable("pthread", "Include PThreads", true);
#endif

	ac_simple("# ==== OS Support");
#if	defined(CONFIG_OS_ANDROID)
	ac_arg_enable("os-android", 	"Build for Android enabled", false);
#endif
#if	defined(CONFIG_OS_IOS)
	ac_arg_enable("ios",		"Build for iOS enabled", false);
#endif
#if	defined(CONFIG_OS_LINUX)
	ac_arg_enable("os-linux",	"Build for Linux enabled", false);
#endif
#if	defined(CONFIG_OS_MAC_X)
	ac_arg_enable("mac-os-x",	"Build for Mac OS X enabled", false);
#endif
#if	defined(CONFIG_OS_WINDOWS)
	ac_arg_enable("os-windows",	"Build for Windows enabled", false);
#endif
#if	defined(CONFIG_OS_OTHER)
	ac_arg_enable("os-other",	"Build for 'Other' OS is enabled", false);
#endif

#if	defined(CONFIG_DEBUG)
	ac_simple("# ==== Debug");
	ac_arg_enable("debug", "Build with DEBUG enabled", false);
#endif

#if	defined(CONFIG_MOD_LIBCONFIG)
	pkg_check_modules("LIBCONFIGXX","libconfig++","1.4");
#endif
#include "library/libraries.inc"
#include "user/user-code-ac.inc"

#ifdef	CONFIG_LIBRARY
	ac_subst2_val(LIBRARY, "_LIBS", "[$SLIBS]");
#endif

	ac_config("AC_SUBST",		"CFLAGS");
	ac_config("AC_SUBST",		"CPPFLAGS");
	ac_config("AC_SUBST",		"LIBS");
	ac_config("AC_SUBST",		"SLIBS");
	ac_config("AC_MSG_RESULT",	"$build_tests");
	ac_config_files();
	ac_simple("AC_OUTPUT");
	fclose(c_ac);
}

int	main(int argc, char **argv)
{
	configure_ac();
}
