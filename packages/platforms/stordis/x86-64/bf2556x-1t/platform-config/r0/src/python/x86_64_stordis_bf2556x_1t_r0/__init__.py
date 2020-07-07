from onl.platform.base import *
from onl.platform.stordis import *

class OnlPlatform_x86_64_stordis_bf2556x_1t_r0(OnlPlatformStordis,
                                         OnlPlatformPortConfig_48x25_8x100):
    PLATFORM='x86-64-stordis-bf2556x-1t-r0'
    MODEL="BF2556X-1T"
    SYS_OBJECT_ID=".25560.1"
    
    def baseconfig(self):
        
        return True

