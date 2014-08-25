#!/bin/bash
echo "hello gbk2utf8 tool"

for i in `find ../../Classes -type f -name '*.cpp' -o -name '*.h'` ;
do
		echo -n ${i}
        isUTF=`file $i|grep 'UTF'|wc -l`
		min=0
		if [ $isUTF -eq $min ] 
		then 
			echo "	need convert"
			echo -ne '\xEF\xBB\xBF' > ${i}.tmp
			iconv -f gbk -t utf-8  $i>>${i}.tmp
			mv ${i}.tmp $i;
		else
		   echo "	not need convert"
		fi
done
