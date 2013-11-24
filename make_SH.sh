#!/bin/bash
#########################################
# Sayanogenmod Sam 4.2.2  Kernel Source #
# Android 4.2.2                         #
# by Sunghun.Ra [Say]                   #
#########################################

make say_defconfig
make -j8
echo :
echo :
echo :
echo If you want make a boot image, use Merge-Tool folder.
echo Modules : modules.sh
echo by Sunghun.Ra
