
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
#include	"autoconf.h"

#define		CHECK_HEADERS_FILE	"user-headers.inc"
#define		min(a, b)	(a<b?a:b)
FILE	*c_ac;


#define	F_CC	(1 << 0)
#define	F_CXX	(1 << 1)

void	ac_simple(char	*s)
{
	fprintf(c_ac, "%s\n", s);
}

void	newline(void)
{
	ac_simple("");
}

void	ac_init(void)
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

void	ac_config(char	*var, char *value)
{
	fprintf(c_ac, "%s([%s])\n", var, value);
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
	strcpy(header_name, "Cannot open header.inc");

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
	char	variable[128];
	char	VARIABLE[128];
	char	c;
	char	*use;
	if (lib) {
		use = "use_";
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
	strncpy(variable, arg, 120);
	len = strlen(variable);
	for (i = 0; i < len ; i++) {
		c = variable[i];
		if (c == '-') {
			c = '_';
			variable[i] = c;
		}
		VARIABLE[i] = toupper(c);
	}
	VARIABLE[i] = '\0';

	fprintf(c_ac, "],\n");

	fprintf(c_ac, "\t[case \"${enableval}\" in\n");
	fprintf(c_ac, "\t\tyes)\t%s%s=true  ;;\n", use, variable);
	fprintf(c_ac,  "\t\tno)\t%s%s=false ;;\n", use, variable);
	fprintf(c_ac,   "\t\t*) AC_MSG_ERROR(bad value ${enableval} for --enable-%s) ;;\n", arg);
	fprintf(c_ac, "\t esac\n");
	fprintf(c_ac, "\t],\n");
	fprintf(c_ac, "\t[%s%s=false])\n", use, variable);
	fprintf(c_ac, "AM_CONDITIONAL(CONFIG_%s, test x$%s = xtrue)\n", VARIABLE, variable);
	newline();
}


void	ac_arg_with_include (char *library, char *libname, char *name, char *path, int flags)
{
	int	i,len;
	char	LIBRARY[128];
	char	c;
	char	*symbol;
	fprintf(c_ac, "AC_ARG_WITH([%s-include-path],\n", library);
	fprintf(c_ac, "\t"
		"[AS_HELP_STRING("
			"[--with-%s-include-path]"			","
			"[location of the %s headers, defaults to %s]"
		")],\n",
		library,
		name,
		path);
	len=min(strlen(library), 120);
	for (i = 0; i < len ; i++) {
		c = library[i];
		if (c == '-')
			c = '_';
		LIBRARY[i]=toupper(c);
	}
	LIBRARY[i] = '\0';
	if (flags & F_CC) {
		symbol = "CFLAGS";
	} else if (flags & F_CXX) {
		symbol = "CXXFLAGS";
	} else {
		symbol = "BADFLAGS";
	}
	fprintf(c_ac, "\t[%s_%s=\"-I$withval\"],\n",	symbol, LIBRARY);
	fprintf(c_ac, "\t[%s_%s=\"-I%s\"])\n",		symbol, LIBRARY, path);

	fprintf(c_ac, "AC_SUBST([%s_CFLAGS])\n", LIBRARY);
	newline();
}

void	ac_arg_with_lib_path(char *library, char *libname,char *name, char *path, int flags)
{
	int	i,len;
	char	LIBRARY[128];
	char	c;
	fprintf(c_ac, "AC_ARG_WITH([%s-lib-path],\n", library);
	fprintf(c_ac, "\t"
		"[AS_HELP_STRING("
			"[--with-%s-lib-path]"			","
			"[location of the %s libraries, defaults to %s]"
		")],\n",
		library,
		name,
		path);
	len=min(strlen(library), 120);
	for (i = 0; i < len ; i++) {
		c = library[i];
		if (c == '-')
			c = '_';
		LIBRARY[i]=toupper(c);
	}
	LIBRARY[i] = '\0';

	fprintf(c_ac, "\t[%s_LIBS=\"-L$withval\" -l%s],\n", LIBRARY, libname);
	fprintf(c_ac, "\t[%s_LIBS=\"-L%s -l%s\"])\n", LIBRARY, path, libname);

	fprintf(c_ac, "AC_SUBST([%s_LIBS])\n", LIBRARY);
	newline();
}

void	ac_config_files()
{
	fprintf(c_ac, "AC_CONFIG_FILES([Makefile ");
	fprintf(c_ac, " %s.pc", CONFIG_LIBRARY_NAME);
	fprintf(c_ac, "])\n");
}

#if	0
int MAX_PATH_LENGTH = 80;
char* path[MAX_PATH_LENGTH];
getcwd(path, MAX_PATH_LENGTH);
printf("Current Directory = %s", path);
#endif

void	configure_ac(void)
{
	c_ac	= fopen("configure.ac", "w");
	if (c_ac == NULL) {
		perror("ERROR");
		exit(1);
	}

	ac_init();
	ac_config("AC_PRERQ",		CONFIG_AC_PRERQ);
	ac_config("AC_CONFIG_HEADER",	CONFIG_AC_CONFIG_HEADER);
	ac_config("AC_CONFIG_SRCDIR",	CONFIG_SRCDIR);
	ac_simple("AC_PROG_CPP");
	ac_simple("AC_PROG_CC");
	ac_config("AC_INIT_AUTOMAKE",	CONFIG_AM_INIT_AUTOMAKE);
	ac_simple("AC_PROG_MAKE_SET");
	ac_simple("AM_MAINTAINER_MODE");
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

#if	defined(CONFIG_OPENSSL)
	ac_simple("# ==== OpenSSL Libraries");
	ac_arg_with_include ("openssl", "ssl", "OpenSSL", "/usr/include",F_CC);
	ac_arg_with_lib_path("openssl", "ssl", "OpenSSL", "/usr/lib",F_CC);
	ac_arg_enable("openssl", "Include OpenSSL", true);
#endif

#if	defined(CONFIG_PTHREAD)
	ac_simple("# ==== Pthread Libraries");
	ac_arg_with_include ("pthread", "pthread", "PThread", "/usr/include",F_CC);
	ac_arg_with_lib_path("pthread", "pthread", "PThread", "/usr/include",F_CC);
	ac_arg_enable("pthread", "Include PThreads", true);
#endif

#if	defined(CONFIG_DEBUG)
	ac_simple("# ==== Debug");
	ac_arg_enable("debug", "Build with DEBUG enabled", false);
#endif

#include "user-code.inc"

	ac_config("AC_SUBST",		"CFLAGS");
	ac_config("AC_MSG_RESULT",	"$build_tests");
	ac_config_files();
	ac_simple("AC_OUTPUT");
	fclose(c_ac);
}

int	main(int argc, char **argv)
{
	configure_ac();
}
