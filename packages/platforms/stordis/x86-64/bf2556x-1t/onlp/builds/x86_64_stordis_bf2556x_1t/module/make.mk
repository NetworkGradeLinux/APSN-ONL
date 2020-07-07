###############################################################################
#
#
#
###############################################################################
THIS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
LIBDPAPI := $(ONL)/packages/platforms/stordis/x86-64/dpapi/libdpapi.a
x86_64_stordis_bf2556x_1t_INCLUDES := -I $(THIS_DIR)inc
x86_64_stordis_bf2556x_1t_INTERNAL_INCLUDES := -I $(THIS_DIR)src
x86_64_stordis_bf2556x_1t_CFLAGS := $(LIBDPAPI)
x86_64_stordis_bf2556x_1t_DEPENDMODULE_ENTRIES := init:x86_64_stordis_bf2556x_1t ucli:x86_64_stordis_bf2556x_1t

