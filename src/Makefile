# We depend on 'user/<file>', but 'user' does not exist in the repo.
# The intention is that a 'user' directory is created in parallel to
# this git repo, the git repo is rsynced to the external 'user' directory.
# A symbolic link here links to the external 'user' directory.
# This way, we can have local files, which does not affect the main repo.


CFLAGS	+=	-I.

all:	ac	am

.PHONY:	ac am

ac:	configure.ac

configure.ac:	configure_ac
	./configure_ac

configure_ac:	configure_ac.c	autoconf.h user-code.inc user-headers.inc
	${CC}	${CFLAGS} -o $@	configure_ac.c

autoconf.h:	../config/autotooler-config/autoconf.h
	cp	$<	$@

user-code.inc:		user/user-code.inc
	cp	$<	$@

user-headers.inc:	user/user-headers.inc
	cp	$<	$@

am:	Makefile.am

Makefile.am:	Makefile_am
	./Makefile_am

Makefile_am:	Makefile_am.c	autoconf.h fileinfo
	${CC}	${CFLAGS} -o $@	Makefile_am.c

.PHONY:	fileinfo
fileinfo:	api_headers.dat	headers.dat	sources.dat
api_headers.dat:	API	purge
	@(cd	$<	; find . -name  '*.h*' | sed -e 's%^\./%%g'	> ../$@)

headers.dat:		HEADERS	purge
	@(cd	$<	; find . -name  '*.h*' | sed -e 's%^\./%%g'	> ../$@)

sources.dat:		SOURCES	purge
	@(cd	$<	; find . -name  '*.c*' | sed -e 's%^\./%%g'	> ../$@)

purge:
	@touch	tag~
	@find	. -name '*~'	| xargs /bin/rm

clean:
	rm	-f	api_headers.dat headers.dat sources.dat
	rm	-f	Makefile_am	Makefile.am
	rm	-f	configure_ac	configure.ac
	rm	-f	user-*
	rm	-f	autoconf.h
