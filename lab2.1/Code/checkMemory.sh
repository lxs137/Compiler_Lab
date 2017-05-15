#/bin/sh
for i in "$@"
do
    lines=`wc -l mem_log_${i} | cut -f1 -d' '`
    if [ "$lines" = "15" ]
    then
        continue
    else
        exit 1
    fi
done
