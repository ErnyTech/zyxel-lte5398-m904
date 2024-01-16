#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libjwt
PKG_VERSION:=1.8.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=https://github.com/benmcollins/libjwt/releases
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/libs

PKG_LICENSE:=LGPLv3
PKG_LICENSE_FILES:=COPYING

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

PKG_MAINTAINER:=Ben Collins <ben@cyphre.com>

include $(INCLUDE_DIR)/package.mk
TARGET_CFLAGS += $(FPIC)
#TARGET_CFLAGS += $(FPIC) -Wno-error=unused-but-set-variable

define Package/libjwt
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=javascript object notation
  DEPENDS:=+jansson +openssl-util
endef

define Package/libjwt/description
  Libjwt is a C library for JSON Web Token
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/{lib,include}
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libjwt* $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/* $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
endef

define Package/libjwt/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libjwt*so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libjwt))
