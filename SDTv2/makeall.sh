#!/bin/sh
#
# Copyright     Bobardier Transportation 2011
#
# Component     SDTv2 Library
#
# File          makeall.sh
#
# Requirements  NA
#
# Abstract      Buils all SW variants in one go
#

host="`/bin/hostname`"

if test "$host" == "labpro" ; then
make VXWORKS_68K_CSS1_config
make lint
make
make DEBUG=TRUE
make VXWORKS_PPC_CSS3_GW-C_config
make lint
make
make DEBUG=TRUE
make VXWORKS_PPC_CSS3_CCUO_config
make lint
make
make DEBUG=TRUE
make VXWORKS_PPC_CSS3_DCU2_config
make lint
make
make DEBUG=TRUE
else
make INTEGRITY_config
make
make lint
make VXWORKS_HMI411_config
make lint
make
make DEBUG=TRUE
make lint
make LINUX_HMI500wrl_config
make lint
make
make DEBUG=TRUE
fi
