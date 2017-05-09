#!/bin/bash

if test -z "$1"
then
    echo "First argument must be function coverage file"
else
    notExecuted=`cat $1 | grep "^0.00%" | wc -l`
    executed=`cat $1 | grep -v "^0.00%" | wc -l`

    percentage=$(echo "scale=2; $notExecuted / ($notExecuted + $executed) * 100" |bc!)

    echo $percentage
fi
