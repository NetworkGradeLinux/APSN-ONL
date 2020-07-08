###############################################################################
#
#
#
###############################################################################
THIS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
x86_64_stordis_bf6064x_t_INCLUDES := -I $(THIS_DIR)inc
x86_64_stordis_bf6064x_t_INTERNAL_INCLUDES := -I $(THIS_DIR)src 
x86_64_stordis_bf6064x_t_DEPENDMODULE_ENTRIES := init:x86_64_stordis_bf6064x_t ucli:x86_64_stordis_bf6064x_t
