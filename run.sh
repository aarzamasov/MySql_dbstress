#!/bin/bash

function killer()
{
    TESTSUID="`mysql -e 'show processlist;'| grep 'testsuite' | awk '{print $1}'`"

    for pid in $TESTSUID; do
            mysql -e "kill $pid">& /dev/null
    done
    sleep 20 
}

#TESTS="READ_PK_POINT READ_KEY_POINT READ_KEY_POINT_NO_DATA READ_PK_POINT_INDEX"
TESTS="READ_KEY_POINT READ_KEY_POINT_NO_DATA READ_KEY_POINT_LIMIT READ_KEY_POINT_NO_DATA_LIMIT UPDATE_POINT_PK UPDATE_RANGE_PK"
for test in $TESTS;
do
        for threads in 1 4 16 64 128 256 384 512 600; 
        do
	       	php main.php  -d 360 -t $threads -o run -n df_enum -s 1000000 -e myisam -q $test
                killer
        done
done

