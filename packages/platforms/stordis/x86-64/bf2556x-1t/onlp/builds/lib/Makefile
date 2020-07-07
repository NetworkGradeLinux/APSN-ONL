############################################################
# <bsn.cl fy=2014 v=onl>
#
#           Copyright 2014 BigSwitch Networks, Inc.
#
# Licensed under the Eclipse Public License, Version 1.0 (the
# "License"); you may not use this file except in compliance
# with the License. You may obtain a copy of the License at
#
#        http://www.eclipse.org/legal/epl-v10.html
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
# either express or implied. See the License for the specific
# language governing permissions and limitations under the
# License.
#
# </bsn.cl>
############################################################
#
#
############################################################
# include $(ONL)/make/config.amd64.mk

# MODULE := libonlp-x86-64-stordis-bf2556x-1t
# include $(BUILDER)/standardinit.mk

# DEPENDMODULES := AIM IOF x86_64_stordis_bf2556x_1t onlplib
# DEPENDMODULE_HEADERS := sff

# include $(BUILDER)/dependmodules.mk

# SHAREDLIB := libonlp-x86-64-stordis-bf2556x-1t.so
# $(SHAREDLIB)_TARGETS := $(ALL_TARGETS)
# include $(BUILDER)/so.mk
# .DEFAULT_GOAL := $(SHAREDLIB)

# GLOBAL_CFLAGS += -I$(onlp_BASEDIR)/module/inc
# GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1 
# #GLOBAL_CFLAGS += -Wnoerror=unused-function -Wnoerror=unused-function
# GLOBAL_CFLAGS += -fPIC
# LIBDPAPI := $(ONL)/packages/platforms/stordis/x86-64/dpapi/libdpapi.a
# GLOBAL_LINK_LIBS += -lpthread -ldl -lz $(LIBDPAPI)

# include $(BUILDER)/targets.mk



PLATFORM := x86-64-stordis-bf2556x-1t
LIBDPAPI := $(ONL)/packages/platforms/stordis/x86-64/dpapi/libdpapi.a
GLOBAL_LINK_LIBS += $(LIBDPAPI) -ldl -lz
include $(ONL)/packages/base/any/onlp/builds/platform/libonlp-platform.mk