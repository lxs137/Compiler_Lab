#/bin/sh
for i in "$@"
do
    lines=`wc -l mem_log_${i} | cut -f1 -d' '`
    if [ "$lines" = "67" ]
    then
        echo "y"
    else
        echo "n"
        exit 1
    fi
done
