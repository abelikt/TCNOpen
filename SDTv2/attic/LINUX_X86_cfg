#
# Copyright     Bobardier Transportation 2011
#
# Component     SDTv2 Library
#
# File          LINUX_X86_cfg
#
# Requirements  NA
#
# Abstract      Build definitions for x86 Linux
#

ARCH      = linux-x86
CPU       = i568
TARGET_OS = LINUX
TOOLCHAIN =

SDTLIBFEATURES = -DSDT_ENABLE_IPT \
                 -DSDT_ENABLE_MVB \
                 -DSDT_ENABLE_WTB \
                 -DSDT_SECURE \
                 -DUNITTEST 
LINT_SYSINCLUDE_DIRECTIVES = -i /usr/include +libh stdint.h +libh pthread.h                  
LDFLAGS += -m32
PLATFORM_CPPFLAGS = -DO_LE $(SDTLIBFEATURES)
PLATFORM_CFLAGS+=-m32
PLATFORM_CPPFLAGS+=-m32
PLATFORM_LDFLAGS+=$(LDFLAGS)