# We depend on 'user/<file>', but 'user' does not exist in the repo.
# The intention is that a 'user' directory is created in parallel to
# this git repo, the git repo is rsynced to the external 'user' directory.
# A symbolic link here links to the external 'user' directory.
# This way, we can have local files, which does not affect the main repo.


CFLAGS	+=	-I.
CFLAGS	+=	$(pkg-config --cflags libconfig)
LIBFLAGS+=	$(pkg-config --libs libconfig)

all:	ac	am

.PHONY:	ac am

ac:	configure.ac

configure.ac:	configure_ac
	./configure_ac

configure_ac:	configure_ac.c	autoconf.h user/user-code-ac.inc user/user-headers.inc
	${CC}	${CFLAGS} -o $@	configure_ac.c

am:	Makefile.am

Makefile.am:	Makefile_am
	./Makefile_am

Makefile_am:	Makefile_am.c	autoconf.h user/Sources.inc user/user-code-am.inc
	${CC}	${CFLAGS} -o $@	Makefile_am.c	${LIBFLAGS}

autoconf.h:	../config/autotooler-config/autoconf.h
	cp	$<	$@

install:	am	ac
	install	-m 644	configure.ac	REPO/configure.ac
	install	-m 644	Makefile.am	REPO/Makefile.am
	
.PHONY:	fileinfo

purge:
	@touch	tag~
	@find	. -name '*~'	| xargs /bin/rm

clean:
	rm	-f	Makefile_am	Makefile.am
	rm	-f	configure_ac	configure.ac
	rm	-f	user-*
	rm	-f	autoconf.h
