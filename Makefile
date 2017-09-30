#
# Default config file is in $(TOPDIR)/user/defconfig
# First, run xxx_defconfig
# Then, `make menuconfig' if needed
#

TOPDIR=$(shell pwd)

CONFIG_CONFIG_IN=Config.in
CONFIG_DEFCONFIG=.defconfig
CONFIG=config

CONFIG_SHELL=$(shell which bash)
ifeq ($(CONFIG_SHELL),)
$(error GNU Bash is needed to build autotooler!)
endif

BINDIR:=$(TOPDIR)/binaries

DATE := $(shell date)
VERSION := 0.1
REVISION := 1

noconfig_targets:= menuconfig defconfig $(CONFIG) oldconfig

# Check first if we want to configure Autotooler
#
ifeq ($(filter $(noconfig_targets),$(MAKECMDGOALS)),)
-include .config
endif

ifeq ($(HAVE_DOT_CONFIG),)

all: menuconfig

# configuration
# ---------------------------------------------------------------------------

$(CONFIG)/conf:
	@mkdir -p $(CONFIG)/autotooler-config
	$(MAKE) CC="$(HOSTCC)" -C $(CONFIG) conf
	-@if [ ! -f .config ]; then \
		cp $(CONFIG_DEFCONFIG) .config; \
	fi

$(CONFIG)/mconf:
	@mkdir -p $(CONFIG)/autotooler-config
	$(MAKE) CC="$(HOSTCC)" -C $(CONFIG) conf mconf
	-@if [ ! -f .config ]; then \
		cp $(CONFIG_DEFCONFIG) .config; \
	fi

menuconfig: $(CONFIG)/mconf
	@mkdir -p $(CONFIG)/autotooler-config
	@if ! KCONFIG_AUTOCONFIG=$(CONFIG)/autotooler-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/autotooler-config/autoconf.h \
		$(CONFIG)/mconf $(CONFIG_CONFIG_IN); then \
		test -f .config.cmd || rm -f .config; \
	fi

$(CONFIG): $(CONFIG)/conf
	@mkdir -p $(CONFIG)/autotooler-config
	@KCONFIG_AUTOCONFIG=$(CONFIG)/autotooler-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/autotooler-config/autoconf.h \
		$(CONFIG)/conf $(CONFIG_CONFIG_IN)

oldconfig: $(CONFIG)/conf
	@mkdir -p $(CONFIG)/autotooler-config
	@KCONFIG_AUTOCONFIG=$(CONFIG)/autotooler-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/autotooler-config/autoconf.h \
		$(CONFIG)/conf -o $(CONFIG_CONFIG_IN)

defconfig: $(CONFIG)/conf
	@mkdir -p $(CONFIG)/autotooler-config
	@KCONFIG_AUTOCONFIG=$(CONFIG)/autotooler-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/autotooler-config/autoconf.h \
		$(CONFIG)/conf -d $(CONFIG_CONFIG_IN)


else #  Have DOT Config

CROSS_COMPILE=

AS=gcc
CC=gcc
LD=ld
NM=nm
SIZE=size
OBJCOPY=objcopy
OBJDUMP=objdump

CCVERSION := $(strip $(subst .,, $(shell expr `$(CC) -dumpversion`)))
CCVERSIONGE441 := $(shell test $(CCVERSION) -ge 441 && echo 1 || echo 0)

PROJECT 		:= $(strip $(subst ",,$(CONFIG_PROJECT)))
LIBRARY_NAME		:= $(strip $(subst ",,$(CONFIG_LIBRARY_NAME)))
HOMEPAGE		:= $(strip $(subst ",,$(CONFIG_HOMEPAGE)))
VERSION			:= $(strip $(subst ",,$(CONFIG_LIBRARY_VERSION)))
SRC_URI			:= $(strip $(subst ",,$(CONFIG_SRC_URI)))
ifeq ($(VERSION),)
VERSION:=1.0
endif

PHONY:=all
rebuild: clean all

endif  # HAVE_DOT_CONFIG

PHONY+= rebuild

%_defconfig:
	echo $(shell find ./lib/ -name $@)
	cp $(shell find ./lib/ -name $@) .config
	@$(MAKE) oldconfig

update:
	cp .config user/$(PROJECT)_defconfig

debug:
	cat	config/autotooler-config/autoconf.h
	
PHONY+=update debug

distrib: config-clean
	find . -type f \( -name .depend \
		-o -name '*.o' \
		-o -name '*~' \) \
		-print0 \
		| xargs -0 rm -f
	rm -fr build
	rm -fr log
	rm -fr .auto.deps
	rm -fr ..make.deps.tmp
	rm -fr .config.cmd .config.old
	make -C config clean
	rm -fr config/autotooler-config
	rm -fr config/conf
	rm -f  config/.depend
	rm -f .installed
	rm -f .configured

config-clean:
	make -C config distclean
	rm -fr config/autotooler-config
	rm -f  config/.depend

clean:
	find . -type f \( -name .depend \
		-o -name '*.o' \
		-o -name '*~' \) \
		-print0 \
		| xargs -0 rm -f
	rm -fr $(obj)

distclean: clean config-clean
	rm -fr .config .config.cmd .config.old
	rm -fr .auto.deps
	rm -f .installed
	rm -f ..*.tmp
	rm -f .configured

mrproper: distclean
	rm -fr $(BINDIR)
	rm -fr log

.PHONY: $(PHONY)
