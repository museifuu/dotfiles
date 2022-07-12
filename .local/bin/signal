interface=$(ls -d /sys/class/net/wl* | cut -c 16-21)
[ $(cat /sys/class/net/$interface/operstate) = up ] &&
    iwlist $interface scan | grep dBm | cut -c 49-55 | tr '\n' '\0' ||
    printf "down"
