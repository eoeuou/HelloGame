#!/bin/bash
echo "hello javah tool"

rm -rf output
mkdir output

#search *.java
find ./../../proj.android/src -name '*.java'>>output/temp_all.txt

temp_lines=`cat output/temp_all.txt`
for temp_line in $temp_lines
do
	if grep 'native' $temp_line ;then
		echo "$temp_line" >> output/temp.txt		
	else
		echo "don't include native"
	fi
done

rm output/temp_all.txt

sed -i "s/\.\/\.\.\/\.\.\/proj\.android\/src\///g" output/temp.txt
sed -i "s/\//./g" output/temp.txt
sed -i "s/\.java//g" output/temp.txt

echo -e '\033[41;33;1m BEGIN \033[0m'
lines=`cat output/temp.txt`
for line in $lines
do
	echo "$line"	
	javah -d ./output -classpath ./../../proj.android/src -jni $line
done
echo -e '\033[41;33;1m END \033[0m'

#javah -d ./output -classpath ./../../proj.android/src -jni org.cocos2dx.ckbase.CKGameHelper

#rm output/temp.txt