from onl.platform.base import *
from onl.platform.stordis import *


class OnlPlatform_x86_64_stordis_bf6064x_t_r0(OnlPlatformStordis,
                                              OnlPlatformPortConfig_64x100):
    PLATFORM = 'x86-64-stordis-bf6064x-t-r0'
    MODEL = "BF6064X-T"
    SYS_OBJECT_ID = ".6064"

    def baseconfig(self):
        return True
