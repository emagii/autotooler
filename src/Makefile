CFLAGS	+=	-I.

configure_ac:	configure_ac.c	autoconf.h
	${CC}	${CFLAGS} -o $@	$<

autoconf.h:	../config/autotooler-config/autoconf.h
	cp	$<	$@
