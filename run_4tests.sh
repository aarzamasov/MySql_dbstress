#!/bin/bash

function killer()
{
    TESTSUID="`mysql -e 'show processlist;'| grep 'testsuite' | awk '{print $1}'`"

    for pid in $TESTSUID; do
            mysql -e "kill $pid">& /dev/null
    done
    sleep 20 
}

TESTS="READ_PK_POINT READ_KEY_POINT READ_KEY_POINT_NO_DATA READ_PK_POINT_INDEX"

for test in $TESTS;
do
        for threads in 1 4 16 64 128 256 384 512 600; 
        do
	       	php /root/testsuite/main.php  -d 360 -t $threads -o run -n df_bigvarchar -s 1000000 -e myisam -q $test
                killer
        done
done

killer
killer
killer

for test in $TESTS;
do
        for threads in 1 4 16 64 128 256 384 512 600; 
        do
	       	php /root/testsuite/main.php  -d 360 -t $threads -o run -n df_text -s 1000000 -e myisam -q $test
                killer
        done
done

killer
killer
killer

for test in $TESTS;
do
        for threads in 1 4 16 64 128 256 384 512 600; 
        do
	       	php /root/testsuite/main.php  -d 360 -t $threads -o run -n df_bigvarcharaux -s 1000000 -e myisam -q $test
                killer
        done
done

killer
killer
killer

for test in $TESTS;
do
        for threads in 1 4 16 64 128 256 384 512 600; 
        do
	       	php /root/testsuite/main.php  -d 360 -t $threads -o run -n df_textaux -s 1000000 -e myisam -q $test
                killer
        done
done

killer
killer
killer
