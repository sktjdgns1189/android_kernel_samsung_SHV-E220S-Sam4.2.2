#!/system/bin/sh

mount -o remount,ro /system /system
logcat > /data/say.log
logcat -d > /data/sh.log
