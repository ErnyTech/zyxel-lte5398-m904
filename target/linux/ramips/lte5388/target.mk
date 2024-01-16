#
# Copyright (C) 2009 OpenWrt.org
#

SUBTARGET:=lte5388
BOARDNAME:=LTE5388/LTE5398 Generic Indoor LTE CPE
ARCH_PACKAGES:=ramips_24kec
FEATURES+=usb ubifs nand
CPU_TYPE:=24kec
CPU_SUBTYPE:=dsp

DEFAULT_PACKAGES +=

define Target/Description
	Build firmware images for LTE5388 /LTE5398 Generic Indoor LTE CPE.
endef

