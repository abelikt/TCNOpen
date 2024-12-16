#!/bin/sh
#
# Copyright     Bobardier Transportation 2011
#
# Component     SDTv2 Library
#
# File          makelint.sh
#
# Requirements  NA
#
# Abstract      Lint all SW variants in one go
#

make INTEGRITY_config
make lint

make LINUX_HMI500wrl_config
make lint

make VXWORKS_68K_CSS1_config
make lint

make VXWORKS_HMI411_config
make lint

make VXWORKS_PPC_CSS3_GW-C_config
make lint

make VXWORKS_PPC_CSS3_CCUO_config
make lint

make VXWORKS_PPC_CSS3_DCU2_config
make lint

