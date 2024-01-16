# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$
	
include $(TOPDIR)/rules.mk

#These lines concatanate the package name and list the URL location from which the package source code is to be downloaded
PKG_NAME:=libzcfg_fe_dal
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=@ZyXEL_SITE/public/ZyXEL
DL_DIR:=$(TOPDIR)/dl/public/zyxel
PKG_CAT:=zcat

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

#Follwoing for MTKSOC platform initial development only, delete before release.
ifeq ($(ZCFG_PLATFORM),MTKSOC)
include $(INCLUDE_DIR)/package-mtksoc.mk
else
include $(INCLUDE_DIR)/package.mk
endif

#These lines describe what your package does and its place in the menu config

define Package/libzcfg_fe_dal
SECTION:=net
CATEGORY:=Zyxel Packages
TITLE:= ZyXEL Configuration Management Data Access Library
DESCRIPTION:=
DEPENDS:=+libzcfg_fe_rdm_string +libzcfg_fe_rdm_struct +libzcfg_fe_schema +libzyutil
endef

#For the compile rules you need to specify the cross compiler which needs to be used :


#These lines describe where your binary images are to be installed ¡V its the equivalent to make install

# This particular package is a library and the installation rules reflect it

define CheckDependencies
endef

ifeq ("$(strip ${ZCFG_PLATFORM})","BROADCOM")
# support DSL bonding
ifeq ($(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_BRCM_PHY_BONDING),y)
export SUPPORT_DSL_BONDING=y
endif
ifneq ("$(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_BRCM_CHIP)",)
BRCM_CHIP = $(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_BRCM_CHIP)
EXTRA_CFLAGS += -DCONFIG_BCM9$(BRCM_CHIP)
endif
#EthWanAsLan
ifeq ($(CONFIG_BRCMSDK$(shell echo $(CONFIG_BRCM_SDK_VERSION))_ZYXEL_SUPPORT_ETHWAN_AS_LAN),y)
EXTRA_CFLAGS += -DZYXEL_SUPPORT_ETHWAN_AS_LAN
endif

endif

ifeq ($(CONFIG_HAWAIIAN_TELCOM),y)
export HAWAIIAN_TELCOM=y
endif

ifeq ($(CONFIG_ZYXEL_HIDE_OTHER_ACCOUNT_INFO_FOR_INDIVIDUAL_USER_ACCOUNT),y)
export HIDE_OTHER_ACCOUNT_INFO_FOR_INDIVIDUAL_USER_ACCOUNT=y
endif

ifeq ($(CONFIG_ZYXEL_COULD_CHANGE_ITS_OWN_PASSWORD),y)
export COULD_CHANGE_ITS_OWN_PASSWORD=y
endif

ifeq ($(CONFIG_TELIA_CUSTOMIZATION),y)
export TELIA_CUSTOMIZATION=y
endif

#DNA
export CONFIG_DNA_CUSTOMIZATION
ifeq ($(CONFIG_MTKSOC_SCHEDULE_REBOOT_SUPPORT),y)
export CONFIG_MTKSOC_SCHEDULE_REBOOT_SUPPORT
endif

# DHCPv6 Relay support
ifeq ($(CONFIG_PACKAGE_wide-dhcpv6-relay),y)
export CONFIG_PACKAGE_wide-dhcpv6-relay
endif

# DHCPv6 Server IAPD support
ifeq ($(CONFIG_MTKSOC_DHCP6S_IAPD_SUPPORT),y)
export CONFIG_MTKSOC_DHCP6S_IAPD_SUPPORT
endif

# Enable the VLAN/Interface Group with CELLWAN type
ifeq ($(CONFIG_ZYXEL_CELLWAN_WITH_VLAN_INTF_GROUP),y)
export CONFIG_ZYXEL_CELLWAN_WITH_VLAN_INTF_GROUP
endif

ifeq ($(CONFIG_ZYXEL_LTE_FIRMWARE_UPGRADE_BY_DFOTA),y)
EXTRA_CFLAGS += -DZYXEL_LTE_FIRMWARE_UPGRADE_BY_DFOTA
endif

export CONFIG_ZYXEL_TR69_SUPPLEMENTAL_ACS

#XMPP
export CONFIG_ZYXEL_TR69_XMPP_CONNECTION_REQUEST

# WAN MAC for Ethernet WAN
export CONFIG_ZYXEL_WAN_MAC
export CONFIG_ZyXEL_WEB_GUI_SINGLE_IGMP_MLD
export CONFIG_ZYXEL_VDSL_Support_30A
export CONFIG_ZYXEL_VDSL_Support_35B
export CONFIG_CBT_CUSTOMIZATION
export CONFIG_ZYXEL_WEB_WIRELESS_NEW_VERSION_ONE
export CONFIG_ZYXEL_WEB_NETWORK_MAP_NEW_STYLE
export CONFIG_ZyXEL_WEB_GUI_SHOW_PON
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_SERVICE_DOMAIN
export CONFIG_ZYXEL_WEB_GUI_SHOW_CELLWAN
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_MULTI_APN
export CONFIG_ZYXEL_SMSNOTIFICATION
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_SMS
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_SMS_DECODE_PDU_USER_DATA
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_PCI_LOCK
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_NR_NSA
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_NBR_CELLS
export CONFIG_ZYXEL_WEB_GUI_CELLWAN_SUPPORT_GNSS_LOCATION
export CONFIG_ZYXEL_WEB_GUI_SUPPORT_SAS_CBSD
export CONFIG_ISKON_CUSTOMIZATION
export CONFIG_ABOG_CUSTOMIZATION
export CONFIG_ZYXEL_AP_STEERING
export CONFIG_WIND_ITALY_CUSTOMIZATION
export CONFIG_ZCFG_VMG8825_B50B_WIND
export CONFIG_PACKAGE_ZyIMS
export CONFIG_TARGET_en75xx
export CONFIG_ZYXEL_WEB_GUI_ECONET_QoS_STYLE
export CONFIG_ZYXEL_WEB_GUI_SHOW_QOS_CLS_TARGET_INTF
export CONFIG_PACKAGE_webgui_vue
export CONFIG_ZYXEL_GUIVUE_USB_INFO_SHOW_SYSINFO
export CONFIG_BUILD_ZYXEL_PCI_LOCK_NUM

#NAT log recorded feature
export CONFIG_ZYXEL_PPP_AUTH_MENU_CHAP_PAP_CTL
export CONFIG_ZYXEL_NAT_LOG
# Support Econet platform portmirror use
export ECONET_PLATFORM

export CONFIG_ZYXEL_ONESSID

#SONiQ Steering
export CONFIG_ZYXEL_SONIQ

#Auto Detect Wan
export CONFIG_ELISA_NAT_PORTFORWARD_CUSTOMIZATION

#DMZ Management
export CONFIG_ZYXEL_SUPPORT_DMZ_MANAGEMENT

export CONFIG_ZY_WIFI_ONESSID_SECURITY_SYNC

export CONFIG_ZYXEL_REMOTE_ACCESS_PRIVILEGE
export CONFIG_ZYXEL_WLAN_SCHEDULER_AUTO_SWITCH_RADIO_ON
#Support PPTP VPN
export CONFIG_KERNEL_ZYXEL_PPTP_SUPPORT

#Support WiFi Security Mode WPA/WPA2-PSK
export CONFIG_ZYXEL_WIFI_SUPPORT_WPA_MIX_MODE

#retype login password before apply change
export CONFIG_ZYXEL_RETYPE_LOGIN_PASSWORD_BEFORE_APPLY

#MQTT publisher
export CONFIG_ZYXEL_MQTT_PUBLISHER

#Customization
export CONFIG_INTERNET_LED_DEPEND_ON_DEFAULT_GW CONFIG_ELISA_NETWORKMAP_CUSTOMIZATION CONFIG_ZYXEL_SYNC_CCWAN_TO_ALL_DEFGW
export CONFIG_SAME_FW_FOR_TWO_BOARD
export CONFIG_ZYXEL_USA_PRODUCT
export CONFIG_CODETEL_CUSTOMIZATION
export CONFIG_ZyXEL_DHCP_OPTION82

#Support Feature Bits
export CONFIG_ZYXEL_FEATURE_BITS

#Support Online Firmware Upgrade for MTKSOC
export CONFIG_ZyXEL_Online_Firmware_Upgrade

#Support Online Module Upgrade for MTKSOC
export CONFIG_ZyXEL_Online_Module_Upgrade

# LTE Indoor: Support changing country code for Russia
export CONFIG_ZYXEL_CHANGE_WIFI_COUNTRY_FOR_RUSSIA

#LTE
export CONFIG_BUILD_ZYXEL_PHONE_VOLTE_SUPPORT

# LTE Outdoor CPE WIFI alwayws boot up and apply auto switch off timer
export CONFIG_ZY_WIFI_LTE_WLAN_AUTO_SWITCH_OFF

export CONFIG_ZY_WIFI_ECONET_5G

#support network monitor
export CONFIG_PACKAGE_lte_srv_diag
export CONFIG_PACKAGE_zyNWmonitor

#Support SpeedTest
export CONFIG_PACKAGE_SpeedTest

#Supprt FQ_Codel
ifeq ($(CONFIG_ZYXEL_FQ_CODEL),y)
export CONFIG_ZYXEL_FQ_CODEL
endif

#Support Nuttcp
ifeq ($(CONFIG_ZYXEL_NUTTCP),y)
export CONFIG_ZYXEL_NUTTCP
endif

define Package/libzcfg_fe_dal/compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libzcfg_fe_dal.so $(1)/usr/lib/
endef

define Package/libzcfg_fe_dal/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME).so $(1)/lib
#	$(INSTALL_DIR) $(1)/lib/public
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libzcfg_fe_dal.so $(1)/lib/public
#	ln -s /lib/public/libzcfg_fe_dal.so $(1)/lib/libzcfg_fe_dal.so
endef

$(eval $(call BuildPackage,libzcfg_fe_dal))

