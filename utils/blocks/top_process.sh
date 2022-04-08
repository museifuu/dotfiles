#!/bin/bash
top -b -1 -d2 -w149 >> /tmp/top &
$(dirname "${BASH_SOURCE[0]}")/top_parser &
while true; do
    grep -A1 '^COMA' /tmp/top | tail -n1 >> /tmp/top_grepped
    echo '' > /tmp/top
    sleep 2
done
