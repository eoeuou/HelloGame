#!/bin/bash
echo "hello gbk2utf8 tool"
exit
for i in `find ../../Classes  -type f -name '*.cpp' -o -name '*.h'` ;
do
        #echo $i
        #echo ${i}.tmp
        file $i
        iconv -f gbk -t utf-8  $i>${i}.tmp
        mv ${i}.tmp $i;
done
