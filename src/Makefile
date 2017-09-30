CFLAGS	+=	-I.

configure_ac:	configure_ac.c	autoconf.h user-code.inc user-headers.inc
	${CC}	${CFLAGS} -o $@	$<

autoconf.h:	../config/autotooler-config/autoconf.h
	cp	$<	$@

user-code.inc:	../user/user-code.inc
	cp	$<	$@

user-headers.inc:	../user/user-headers.inc
	cp	$<	$@


