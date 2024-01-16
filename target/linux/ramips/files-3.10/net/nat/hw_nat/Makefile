obj-$(CONFIG_RA_HW_NAT) += hw_nat.o
hw_nat-objs := hw_nat.o.g

ccflags-y += -Werror

# ifeq ($(CONFIG_FIRST_IF_MT7615E),y)
	EXTRA_CFLAGS += -DCONFIG_MBSS_SUPPORT -DCONFIG_RTDEV
# endif

# ifeq ($(CONFIG_SECOND_IF_MT7615E),y)
	EXTRA_CFLAGS += -DCONFIG_MBSS_SUPPORT -DCONFIG_RTDEV
# endif


