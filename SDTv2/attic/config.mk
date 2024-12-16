#
# Copyright     Bobardier Transportation 2011
#
# Component     SDTv2 Library
#
# File          LINUX_HMI500wrl_cfg
#
# Requirements  SDT_LIB-REQ-017
#
# Abstract      Build definitions for HMI500 Linux
#

ARCH        = linux-x86-hmi500wrl
CPU         = i686
TARGET_OS   = LINUX
TOOLCHAIN   = i586-wrs-linux-gnu-
OSDEP_NAME  = linux

SDTLIBFEATURES = -DSDT_ENABLE_IPT 

PLATFORM_CPPFLAGS = $(SDTLIBFEATURES) -DO_LE --sysroot=$(GB_SYSROOT)/hmi500-glibc_std/sysroot
PLATFORM_LDFLAGS  = --sysroot=$(GB_SYSROOT)/hmi500-glibc_std/sysroot
