#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=iptables
PKG_VERSION:=1.4
ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
ifeq ("$(strip ${BRCM_SDK_VERSION})","502L04")
PKG_VERSION:=1.4.21
else
PKG_VERSION:=1.4.16.3
endif
else ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
PKG_VERSION:=1.4.10
else ifeq ("$(strip ${ZCFG_PLATFORM})","MTKSOC")
PKG_VERSION:=1.4.16.3
endif
#PKG_RELEASE:=3

#PKG_MD5SUM:=f382fe693f0b59d87bd47bea65eca198
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
#PKG_SOURCE_URL:=http://www.netfilter.org/projects/iptables/files \
	ftp://ftp.be.netfilter.org/pub/netfilter/iptables/ \
	ftp://ftp.de.netfilter.org/pub/netfilter/iptables/ \
	ftp://ftp.no.netfilter.org/pub/netfilter/iptables/
PKG_SOURCE_URL:=@ZyXEL_SITE/opensource/network/utils

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

# Support ip6tables NAT table
export CONFIG_MTKSOC_IP6TABLES_NAT_SUPPORT

#ifneq ($(CONFIG_EXTERNAL_KERNEL_TREE),"")
PATCH_DIR:=patches-$(PKG_VERSION)/$(ZCFG_PLATFORM)
#endif

include $(INCLUDE_DIR)/package.mk
ifeq ($(DUMP),)
  -include $(LINUX_DIR)/.config
  include $(INCLUDE_DIR)/netfilter.mk
  STAMP_CONFIGURED:=$(strip $(STAMP_CONFIGURED))_$(shell $(SH_FUNC) grep 'NETFILTER' $(LINUX_DIR)/.config | md5s)
endif


define Package/iptables/Default
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Firewall
  URL:=http://netfilter.org/
endef

define Package/iptables/Module
$(call Package/iptables/Default)
  DEPENDS:=iptables $(1)
endef

define Package/iptables
$(call Package/iptables/Default)
  TITLE:=IPv4 firewall administration tool
  MENU:=1
  DEPENDS+= +kmod-ipt-core +libip4tc +libxtables
endef

define Package/iptables/description
IPv4 firewall administration tool.

 Matches:
  - icmp
  - tcp
  - udp
  - comment
  - limit
  - mac
  - multiport

 Targets:
  - ACCEPT
  - DROP
  - REJECT
  - LOG
  - TCPMSS

 Tables:
  - filter
  - mangle

endef

define Package/iptables-mod-conntrack-extra
$(call Package/iptables/Module, +kmod-ipt-conntrack-extra)
  TITLE:=Extra connection tracking extensions
endef

define Package/iptables-mod-conntrack-extra/description
Extra iptables extensions for connection tracking.

 Matches:
  - connbytes
  - connmark
  - recent
  - helper

 Targets:
  - CONNMARK

endef

define Package/iptables-mod-filter
$(call Package/iptables/Module, +kmod-ipt-filter)
  TITLE:=Content inspection extensions
endef

define Package/iptables-mod-filter/description
iptables extensions for packet content inspection.
Includes support for:

 Matches:
  - layer7
  - string

endef

define Package/iptables-mod-ipopt
$(call Package/iptables/Module, +kmod-ipt-ipopt)
  TITLE:=IP/Packet option extensions
endef

define Package/iptables-mod-ipopt/description
iptables extensions for matching/changing IP packet options.

 Matches:
  - dscp
  - ecn
  - length
  - mark
  - statistic
  - tcpmss
  - time
  - unclean
  - hl

 Targets:
  - DSCP
  - CLASSIFY
  - ECN
  - MARK
  - HL

endef

define Package/iptables-mod-ipsec
$(call Package/iptables/Module, +kmod-ipt-ipsec)
  TITLE:=IPsec extensions
endef

define Package/iptables-mod-ipsec/description
iptables extensions for matching ipsec traffic.

 Matches:
  - ah
  - esp
  - policy

endef

define Package/iptables-mod-ipset
$(call Package/iptables/Module,)
  TITLE:=IPset iptables extensions
endef

define Package/iptables-mod-ipset/description
IPset iptables extensions.

 Matches:
  - set

 Targets:
  - SET

endef

define Package/iptables-mod-nat-extra
$(call Package/iptables/Module, +kmod-ipt-nat-extra)
  TITLE:=Extra NAT extensions
endef

define Package/iptables-mod-nat-extra/description
iptables extensions for extra NAT targets.

 Targets:
  - MIRROR
  - NETMAP
  - REDIRECT
endef

define Package/iptables-mod-ulog
$(call Package/iptables/Module, +kmod-ipt-ulog)
  TITLE:=user-space packet logging
endef

define Package/iptables-mod-ulog/description
iptables extensions for user-space packet logging.

 Targets:
  - ULOG

endef

define Package/iptables-mod-hashlimit
$(call Package/iptables/Module, +kmod-ipt-hashlimit)
  TITLE:=hashlimit matching
endef

define Package/iptables-mod-hashlimit/description
iptables extensions for hashlimit matching

 Matches:
  - hashlimit

endef

define Package/iptables-mod-iprange
$(call Package/iptables/Module, +kmod-ipt-iprange)
  TITLE:=IP range extension
endef

define Package/iptables-mod-iprange/description
iptables extensions for matching ip ranges.

 Matches:
  - iprange

endef

define Package/iptables-mod-extra
$(call Package/iptables/Module, +kmod-ipt-extra)
  TITLE:=Other extra iptables extensions
endef

define Package/iptables-mod-extra/description
Other extra iptables extensions.

 Matches:
  - addrtype
  - condition
  - owner
  - physdev (if ebtables is enabled)
  - pkttype
  - quota

endef

define Package/iptables-mod-led
$(call Package/iptables/Module, +kmod-ipt-led)
  TITLE:=LED trigger iptables extension
endef

define Package/iptables-mod-led/description
iptables extension for triggering a LED.

 Targets:
  - LED

endef

define Package/iptables-mod-tproxy
$(call Package/iptables/Module, +kmod-ipt-tproxy)
  TITLE:=Transparent proxy iptables extensions
endef

define Package/iptables-mod-tproxy/description
Transparent proxy iptables extensions.

 Matches:
  - socket

 Targets:
  - TPROXY

endef

define Package/iptables-mod-tee
$(call Package/iptables/Module, +kmod-ipt-tee)
  TITLE:=TEE iptables extensions
endef

define Package/iptables-mod-tee/description
TEE iptables extensions.

 Targets:
  - TEE

endef

define Package/iptables-mod-u32
$(call Package/iptables/Module, +kmod-ipt-u32)
  TITLE:=U32 iptables extensions
endef

define Package/iptables-mod-u32/description
U32 iptables extensions.

 Matches:
  - u32

endef

define Package/ip6tables
$(call Package/iptables/Default)
  DEPENDS:=+kmod-ip6tables +libip6tc +libxtables
  CATEGORY:=IPv6
  TITLE:=IPv6 firewall administration tool
  MENU:=1
endef

define Package/libiptc
$(call Package/iptables/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libip4tc +libip6tc
  TITLE:=IPv4/IPv6 firewall - shared libiptc library (compatibility stub)
endef

define Package/libip4tc
$(call Package/iptables/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=IPv4 firewall - shared libiptc library
endef

define Package/libip6tc
$(call Package/iptables/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=IPv6 firewall - shared libiptc library
endef

define Package/libxtables
 $(call Package/iptables/Default)
 SECTION:=libs
 CATEGORY:=Libraries
 TITLE:=IPv4/IPv6 firewall - shared xtables library
endef
PFX_EXT:=TCPMSS SKIPLOG
PF4_EXT:=icmp
PF6_EXT:=

PFX_EXT+=length limit standard conntrack tcp udp NFQUEUE dscp DSCP mac physdev mark MARK AUTOMAP policer time multiport pkttype connlimit recent iprange helper layer7 string
PF4_EXT+=LOG DNAT MASQUERADE REDIRECT REJECT SNAT TRIGGER

ifneq ($(strip $(CONFIG_IPV6)),)
PF6_EXT+=ah dst eui64 frag hbh hl icmp6 ipv6header mh rt HL LOG REJECT
ifeq ($(CONFIG_MTKSOC_IP6TABLES_NAT_SUPPORT),y)
PF6_EXT+=MASQUERADE REDIRECT
endif
endif

TARGET_CPPFLAGS := \
	-I$(PKG_BUILD_DIR)/include \
	-I$(LINUX_DIR)/user_headers/include \
	$(TARGET_CPPFLAGS)

TARGET_CFLAGS += \
	-I$(PKG_BUILD_DIR)/include \
	-I$(LINUX_DIR)/user_headers/include

ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
CONFIGURE_ARGS += \
	--disable-shared \
	--disable-devel \
	$(if $(CONFIG_IPV6),--enable-ipv6,--disable-ipv6) \
	--with-kernel="$(LINUX_DIR)/user_headers" \
	--with-xtlibdir=/usr/lib/iptables \
	--enable-static \
	--with-pfxmods="$(PFX_EXT)" \
	--with-pf4mods="$(PF4_EXT)" \
	--with-pf6mods="$(PF6_EXT)" 
else ifeq ("$(strip ${ZCFG_PLATFORM})","ECONET")
CONFIGURE_ARGS += \
	--disable-shared \
	--disable-devel \
	$(if $(CONFIG_IPV6),--enable-ipv6,--disable-ipv6) \
	--with-kernel="$(LINUX_DIR)/user_headers" \
	--enable-static
else ifeq ("$(strip ${ZCFG_PLATFORM})","MTKSOC")
#TARGET_CFLAGS += \
#	-ffunction-sections -fdata-sections -fPIC
#TARGET_LDFLAGS += \
#	-Wl,--gc-sections
CONFIGURE_ARGS += \
	--disable-shared \
	--disable-devel \
	$(if $(CONFIG_IPV6),--enable-ipv6,--disable-ipv6) \
	--with-kernel="$(LINUX_DIR)/user_headers" \
	--with-xtlibdir=/usr/lib/iptables \
	--enable-static \
	--with-pfxmods="$(PFX_EXT)" \
	--with-pf4mods="$(PF4_EXT)" \
	--with-pf6mods="$(PF6_EXT)"
endif

ifeq ($(CONFIG_MTKSOC_IP6TABLES_NAT_SUPPORT),y)
TARGET_CFLAGS += -DMTKSOC_IP6TABLES_NAT_SUPPORT
endif

MAKE_FLAGS := \
	$(TARGET_CONFIGURE_OPTS) \
	COPT_FLAGS="$(TARGET_CFLAGS)" \
	KERNEL_DIR="$(LINUX_DIR)/user_headers/" PREFIX=/usr \
	KBUILD_OUTPUT="$(LINUX_DIR)" \
	BUILTIN_MODULES="$(patsubst ipt_%,%,$(patsubst xt_%,%,$(IPT_BUILTIN) $(IPT_CONNTRACK-m) $(IPT_NAT-m)))" 

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/include/iptables
	$(INSTALL_DIR) $(1)/usr/include/net/netfilter

	# XXX: iptables header fixup, some headers are not installed by iptables anymore
ifeq ("$(strip ${BRCM_SDK_VERSION})","502L04")
	$(CP) $(PKG_BUILD_DIR)/include/linux/netfilter/*.h $(1)/usr/include/net/netfilter/
else
	-$(CP) $(PKG_BUILD_DIR)/include/net/netfilter/*.h $(1)/usr/include/net/netfilter/
endif
	$(CP) $(PKG_BUILD_DIR)/include/iptables/*.h $(1)/usr/include/iptables/
	$(CP) $(PKG_BUILD_DIR)/include/iptables.h $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/include/libipulog $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/include/libiptc $(1)/usr/include/

#	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib

#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libxtables.so $(1)/usr/lib/
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libip*tc.so* $(1)/usr/lib/

	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libxtables.a $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libip*tc.a* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/xtables.pc $(1)/usr/lib/pkgconfig/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libiptc.pc $(1)/usr/lib/pkgconfig/
endef

define Package/iptables/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/iptables $(1)/usr/sbin/
	$(LN) iptables $(1)/usr/sbin/iptables-save
	$(LN) iptables $(1)/usr/sbin/iptables-restore
	$(INSTALL_DIR) $(1)/usr/lib/iptables
	
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/rc3.d
#In ECONET platform, kernel modules are built-in
ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
	$(CP) ./files/nf_basic_modules_install.sh $(1)/etc/init.d
	ln -s ../init.d/nf_basic_modules_install.sh $(1)/etc/rc3.d/S45nf-basic-module
endif
endef

define Package/ip6tables/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/ip6tables $(1)/usr/sbin/
	$(LN) ip6tables $(1)/usr/sbin/ip6tables-save
	$(LN) ip6tables $(1)/usr/sbin/ip6tables-restore
	$(INSTALL_DIR) $(1)/usr/lib/iptables
	#(cd $(PKG_INSTALL_DIR)/usr/lib/iptables ; \
		$(CP) libip6t_*.so $(1)/usr/lib/iptables/ \
	)
endef

define Package/libiptc/install
	$(INSTALL_DIR) $(1)/usr/lib

#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libiptc.a $(1)/usr/lib/
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libiptc.so $(1)/usr/lib/
endef

define Package/libip4tc/install
	$(INSTALL_DIR) $(1)/usr/lib

#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libip4tc.a $(1)/usr/lib/
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libip4tc.so $(1)/usr/lib/
endef

define Package/libip6tc/install
	$(INSTALL_DIR) $(1)/usr/lib

#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libip6tc.a $(1)/usr/lib/
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libip6tc.so $(1)/usr/lib/
endef

define Package/libxtables/install
	$(INSTALL_DIR) $(1)/usr/lib
	
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libxtables.a $(1)/usr/lib/
#	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libxtables.so $(1)/usr/lib/
endef

define BuildPlugin
  define Package/$(1)/install
	$(INSTALL_DIR) $$(1)/usr/lib/iptables
	for m in $(patsubst xt_%,ipt_%,$(2)) $(patsubst ipt_%,xt_%,$(2)); do \
		if [ -f $(PKG_INSTALL_DIR)/usr/lib/iptables/lib$$$$$$$${m}.so ]; then \
			$(CP) $(PKG_INSTALL_DIR)/usr/lib/iptables/lib$$$$$$$${m}.so $$(1)/usr/lib/iptables/ ; \
		fi; \
	done
	$(3)
  endef

  $$(eval $$(call BuildPackage,$(1)))
endef

L7_INSTALL:=\
	$(INSTALL_DIR) $$(1)/etc/l7-protocols; \
	$(CP) files/l7/*.pat $$(1)/etc/l7-protocols/


$(eval $(call BuildPackage,iptables))
$(eval $(call BuildPlugin,iptables-mod-conntrack-extra,$(IPT_CONNTRACK_EXTRA-m)))
$(eval $(call BuildPlugin,iptables-mod-extra,$(IPT_EXTRA-m)))
$(eval $(call BuildPlugin,iptables-mod-filter,$(IPT_FILTER-m),$(L7_INSTALL)))
$(eval $(call BuildPlugin,iptables-mod-ipopt,$(IPT_IPOPT-m)))
$(eval $(call BuildPlugin,iptables-mod-ipsec,$(IPT_IPSEC-m)))
$(eval $(call BuildPlugin,iptables-mod-ipset,ipt_set ipt_SET))
$(eval $(call BuildPlugin,iptables-mod-nat-extra,$(IPT_NAT_EXTRA-m)))
$(eval $(call BuildPlugin,iptables-mod-iprange,$(IPT_IPRANGE-m)))
$(eval $(call BuildPlugin,iptables-mod-ulog,$(IPT_ULOG-m)))
$(eval $(call BuildPlugin,iptables-mod-hashlimit,$(IPT_HASHLIMIT-m)))
$(eval $(call BuildPlugin,iptables-mod-led,$(IPT_LED-m)))
$(eval $(call BuildPlugin,iptables-mod-tproxy,$(IPT_TPROXY-m)))
$(eval $(call BuildPlugin,iptables-mod-tee,$(IPT_TEE-m)))
$(eval $(call BuildPlugin,iptables-mod-u32,$(IPT_U32-m)))
$(eval $(call BuildPackage,ip6tables))
$(eval $(call BuildPackage,libiptc))
$(eval $(call BuildPackage,libip4tc))
$(eval $(call BuildPackage,libip6tc))
$(eval $(call BuildPackage,libxtables))
