#/bin/sh
for i in "$@"
do
    if cmp -s $i.output $i.expect
    then
        continue
    else
        exit 1
    fi
done
