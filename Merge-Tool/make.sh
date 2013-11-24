# SH
cp -rf ../arch/arm/boot/zImage ./
rm ramdisk-new.gz
rm boot.img
./mkbootfs ./ramdisk | gzip > ramdisk-new.gz
./mkbootimg --kernel zImage --ramdisk ramdisk-new.gz --base 0x10000000 --pagesize 2048 --ramdiskaddr 0x11000000 -o boot.img
