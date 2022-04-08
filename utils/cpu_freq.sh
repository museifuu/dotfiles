for i in {0..3}; do
    let "c = c + $(cat /sys/devices/system/cpu/cpufreq/policy$i/scaling_cur_freq)"
done
let "c = c / 4"
printf "${c:0:4}.${c:4:3} MHz"
