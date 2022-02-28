#
# Copyright     This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
#               If a copy of the MPL was not distributed with this file, 
#               You can obtain one at http://mozilla.org/MPL/2.0/.
#               Copyright Alstom Transport SA or its subsidiaries and others, 2010-2022. All rights reserved.
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
