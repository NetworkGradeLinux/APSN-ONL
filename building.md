Building
========

Limiting Platform
-----------------

In `setup.env`:

    export PLATFORM_LIST="x86-64-stordis-bf6064x-t-r0"
    export PLATFORMS="x86-64-stordis-bf6064x-t-r0"
    export ONLPM_OPTION_PLATFORM_WHITELIST="x86-64-stordis-bf6064x-t-r0"


Changing Distribution
---------------------

Run docker build, supplying major version of Debian distribution:
- Jessie: `docker/tools/onlbuilder -8`
- Stretch: `docker/tools/onlbuilder -9`
- Buster: `docker/tools/onlbuilder -10`

Make sure that the kernel to be used is supported by referring to
- `builds/any/rootfs/$DIST/common/amd64-base-packages.yml`

Changing Kernels
----------------

Comment out unneeded kernels in:
- `builds/any/rootfs/$DIST/common/amd64-base-packages.yml`
- `packages/base/$ARCH/upgrade/PKG.yml`
- `packages/base/$ARCH/upgrade/builds/Makefile`

Change Kernel In
- `packages/platforms/$VENDOR/$ARCH/$MODEL/modules/builds/Makefile`
- `packages/platforms/$VENDOR/$ARCH/$MODEL/modules/PKG.yml`
- `packages/platforms/$VENDOR/$ARCH/$MODEL/platform-config/r0/src/lib/$ARCH-$VENDOR-$MODEL-$REVISION.yml`