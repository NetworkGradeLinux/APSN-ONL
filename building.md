ONL Stordis Opinionated Build
=============================

This repository is set up to be an opinionated ONL/ONLP(v1) build focused on
Stordis switches. By default, it will do the following:
- Build bf2556x-1t and bf6064x-t only
- Only build kernel 4.19
- Include kernel headers
- Use `systemd` for init system

While it is up to you to choose which Debian version, this has currently only
been tested on Debian Stretch (`onlbuilder -9`).

The rest of this document outlines the changes we have made to make it easier
for users to modify in the future.



Building
--------
The standard build steps apply:

    git clone git@github.com:APS-Networks/OpenNetworkLinux.git
    cd OpenNetworkLinux
    docker/tools/onlbuilder -9
    apt-cacher-ng
    source setup.env
    make amd64


Changing Init System
--------------------
In `setup.env` add either:
- `export INIT=systemd`
- `export INIT=sysvinit`

> Systemd may be used be default in anything after Jessie, although not entirely
> sure.


Installing Kernel Headers by Default
------------------------------------
Some applications built on ONL after installation (for example the Barefoot SDE
because of custom kernel modules) require the kernel headers to be installed. In
the original repository, this is not done by default. Firstly, identify which
kernel is being used (the "Changing Kernels" section below will help), and make 
sure that the relevant headers package is added to the $DIST/$ARCH base
packages.

For instance, using Debian Stretch with Kernel 4.19, you would modify the
following file: `builds/any/rootfs/stretch/common/amd64-base-packages.yml`.
Given that there should be an entry for `onl-kernel-4.19-lts-x86-64-all-modules`
add the following:

    - onl-kernel-4.19-lts-x86-64-all


Limiting Platform
-----------------

In `setup.env`:

    export PLATFORM_LIST="x86-64-stordis-bf6064x-t-r0"
    export PLATFORMS="x86-64-stordis-bf6064x-t-r0"
    export ONLPM_OPTION_PLATFORM_WHITELIST="x86-64-stordis-bf6064x-t-r0"

> TODO: When selecting multiple platforms for build, it isn't clear exactly what
> format these environment variables should be, e.g, space/comma delimited. It
> appears that `PLATFORM_LIST` is comma delimited, and the others space
> delimited.


Changing Distribution
---------------------

Run docker build, supplying major version of Debian distribution:
- Jessie: `docker/tools/onlbuilder -8`
- Stretch: `docker/tools/onlbuilder -9`
- Buster: `docker/tools/onlbuilder -10`

Make sure that the kernel to be used is supported by referring to
- `builds/any/rootfs/$DIST/common/amd64-base-packages.yml`

> If you have issues where the build has problems finding definitions for
> various ELF headers and definitions, make sure `CPATH` is unset. You may be 
> able to keep using it by having it point to `/usr/include` as well as what
> else it is set to.


Changing Kernels
----------------

Comment out unneeded kernels in:
- `builds/any/rootfs/$DIST/common/amd64-base-packages.yml`
- `packages/base/$ARCH/upgrade/PKG.yml`
- `packages/base/$ARCH/upgrade/builds/Makefile`

Change Kernel in:
- `packages/platforms/$VENDOR/$ARCH/$MODEL/platform-config/$REVISION/src/lib/$ARCH-$VENDOR-$MODEL-$REVISION.yml`

If have Kernel modules change in:
- `packages/platforms/$VENDOR/$ARCH/$MODEL/modules/builds/Makefile` 
- `packages/platforms/$VENDOR/$ARCH/$MODEL/modules/PKG.yml`



Recovering From Broken Build
----------------------------
If you've made changes to any files which has broken the build, you may find
this useful if you don't want to re-clone the repository. Assuming you haven't
committed any changes yourself (unless you are forking you shouldn't be doing
this anyway):

Make sure you are no longer running in the ONL docker shell (this is done by 
running onlbuilder), and you are at the repository root:

    git clean -xd # Cleans untracked directories, including files in .gitignore
    git clean -xf # Cleans untracked files, including files in .gitignore
    git reset --hard # Revert any changes to files back to last commit, forcibly

If you are breaking builds frequently, this might save you up to 30 seconds per
build.