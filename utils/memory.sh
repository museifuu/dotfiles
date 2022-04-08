free --mebi | awk '(NR==2){ printf("%.2f GB / %.2f GB\n", $3/1024, $2/1024) }'
