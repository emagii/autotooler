# autotooler
Autotooler is used to create the files needed for autotools to run.
* configure.ac
* Makefile.am

[CREATING A PROJECT]

You have to clone autotooler once to get access to the script.

$ git clone https://github.com/emagii/autotooler.git

[GETTING YOUR PROJECT TO AUTOTOOLIZE]
Inside the repo, you clone the repo you want to "autotoolize".

$ git clone <project>

I.E:

$ git clone git@github.com:emagii/weston-binder.git

You may want to enter the repo and create a new branch.

$ cd weston-binder
$ git checkout -b kirkstone
$ cd ..

[CHANGING CREDENTIALS]

The 'config.inc" file contains some defaults, which you might want to change.
They can be changed later, but it might be easier in an editor.

[CONFIGURATION]

Once ready, you can prepare your project

$ ./mklib <project>

"<project>" must be a git project inside the "autotooler" directory.
I.E:

$ ./mklib weston-binder

If this is the first time you run mklib on the project,
it will create the following files in your <project>.

*	 <project>/AUTHORS
*	 <project>/autogen.sh
*	 <project>/autotooler/Config.in
*	 <project>/autotooler/Config-libs.in
*	 <project>/autotooler/csource+headers-am.inc
*	 <project>/autotooler/emagii_defconfig
*	 <project>/autotooler/gitignore
*	 <project>/autotooler/user-code-ac.inc
*	 <project>/autotooler/user-code-am.inc
*	 <project>/autotooler/user-headers-ac.inc
*	 <project>/m4
*	 <project>/src
*	 <project>/src/include
*	 <project>/src/include/config.h.in
*	 <project>/<project>.pc.in		(a template)
*	 <project>/ChangeLog
*	 <project>/COPYING
*	 <project>/INSTALL
*	 <project>/LICENSE
*	 <project>/NEWS
*	 <project>/README.md
*	 <project>/.gitignore			(unless there is already a .gitignore)
*	 <project>/
*	 <project>/
*	 <project>/

Most new files will be added and committed to the git repo.

[KERNEL CONFIG]

Enter the autotooler and run

$ make menuconfig

and configure the system.

You can select to build
* An Application
* A Shared library
* A Static Library.

You then specify which libraries you depend on.
As long as they are in the list, you are OK.

[SAVING THE CONFIGURATION]
You can save your new .config file by making

$ make update

Your config file will be saved in <project>/autotooler/<project>_defconfig

[RETRIEVING YOUR CONFIGURATION]

If you have already run mklib, 
it will just find the <project>/autotooler/<project>_defconfig

If you come back to the project, you can run:

$ make <project>_defconfig

to start reconfiguring.

[ADDING NEW LIBRARIES]

If the library you need lacks a configuration,
you have to extend the system.

The kernel Kconfig reads in a "Config.in" file at the toplevel.
This can include other files.

├── config
├── Config.in						*
├── library
│   ├── Config.in					*
│   ├── dl
│   │   └── Config.in				*
│   ├── ftd2xx
│   │   └── Config.in				*
│   ├── nsl
│   │   └── Config.in				*
│   └── socket
│       └── Config.in				*
├── LICENSE
├── Makefile
├── Platform.in						*
├── README.md
├── REPO -> ../weston-binder
├── scripts
├── src
└── user
    ├── Config.in					*
    ├── Config-libs.in				*
    ├── csource+headers-am.inc
    ├── emagii_defconfig
    ├── gitignore
    ├── user-code-ac.inc
    ├── user-code-am.inc
    └── user-headers-ac.inc

Platform.in						*		MACHINE and OS
Config.in						*		Libraries to be linked with
user/Config-libs.in				*
library/Config.in				*		Checked for presence
	Config.in's in library				Checked for presence
user/Config.in					*

Adding a library is either done in the toplevel Config.in or
in the <project>/autotooler/Config-libs.in

Example:

To add the libweston library, we are going to add to the user/Config-libs.in

============================
config	CONFIG_WESTON
	bool	"Weston"

config  CONFIG_LIBEVDEV
	bool	"libevdev"
============================

When you run "make menuconfig", you can suddenly select the Weston 
and libevdev libraries

[ADDING SOURCE FILES]

The <project>/autotooler/csource+headers-am.inc file contains the
CSOURCES variable. All source files are to be added to that variable
 
[CHECKING THAT LIBRARIES ARE INSTALLED]
The <project>/autotooler/user-header-ac.inc contains a list of all
the headers that the source file will try to include.
You have to review the source files and extract the name of
all header files and add it to the list.

[CREATING THE AUTOTOOLS FILES]

from the <toplevel>/autotooler directory:

$ make install

This creates the Makefile.am and configure.ac in your project

[CONFIGURING AND BUILDING THE PROJECT]

cd <project>
./autogen.sh
./configure
make
make install

[IF IT FAILS]
You are probably missing adding a header or a path.
You need to look at the files in the autotooler directory.

They are compiled together with files in the autotooler/src directory
when you "make install" to create Makefile.am and configure.ac

[TODO]
Right now, "configure" is ignored by .gitignore, so you have
to run ./autogen.sh all the time. Might be better to save the
result of ./autogen.sh
========================

Example project:
    https://github.com/emagii/ielftool
