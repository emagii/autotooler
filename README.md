# autotooler
Autotooler uses the Kconfig system to create a configuration, then generates configure.ac and Makefile.am

The proper installation of autotooler uses the mklib script in <INSTALL_DIR>/scripts/mklib

You have to clone autotooler once to get access to the script.

The script is called with one parameter, which is the library name.
Then it will create:

<library-name>
	/user
	/<library-name>	; autotooler git repo
		/.config

.config is created from a set of defaults inside 'mklib'
You want to modify 'mklib' to fit your needs, before you run it.
It is not 100% neccessary, but otherwise, you have to modify
the configuration in Kconfig.

The <autotooler>/user directory contains some examples,
showing how libraries and options can be added.

This directory is cloned to the 'user' directory parallel to the autotooler repo,
allowing modification without affecting the autotooler repo.

The process of getting something done is to:

1.	Clone autotooler
2.	Copy <autotooler>/scripts/mklib to a working directory WD
3.	cd WD
4.	Modify WD/mklib to suit your needs.
5.	./mklib	<LIBNAME>
6.	Modify any files in WD/<LIBNAME>/user to suit your requirements
7.	cd	WD/<LIBNAME>/<LIBNAME>/		== AT
8.	make menuconfig
9.		Update the configuration and save
		The result is stored in '.config'
		A header file is created in config/autotooler-config/autoconf.h

============================================================
Below this line, is "YET TO BE IMPLEMENTED", 'cd src; make' is used for now!
============================================================
10.	cd	AT/src
11.	make	ac		; This creates configure_ac and maybe Makefile_am
12.	run	configure_ac	; This will create configure.ac
13.	make	am		; This will create Makefile_am
14.	run	Makefile_am	; This will create Makefile.am (soon)
15.	make			; Will create both
16.	You may need to update both results manually
17.	make	install		; copy to WD/user directory
