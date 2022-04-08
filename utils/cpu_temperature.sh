#!/bin/bash
let "temps = $(wc -l <<< $(ls /sys/devices/platform/coretemp.0/hwmon/hwmon?/temp*_input))"
let "total = 0"
for files in $(ls /sys/devices/platform/coretemp.0/hwmon/hwmon?/temp*_input); do
    let "temp = $(cat $files)"
    let "total = $total + $temp"
done
let "temp = $total / ($temps) / 1000"
echo "$temp°C"
