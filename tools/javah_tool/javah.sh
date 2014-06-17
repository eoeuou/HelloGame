#!/bin/bash
echo "hello javah tool"

rm -rf output
rm temp.txt
rm temp_all.txt

#search *.java
find ./../../proj.android/src -name '*.java'>>temp_all.txt

temp_lines=`cat temp_all.txt`
for temp_line in $temp_lines
do
	if grep 'native' $temp_line ;then
		echo "$temp_line" >> temp.txt		
	else
		echo "don't include native"
	fi
done

rm temp_all.txt

sed -i "s/\.\/\.\.\/\.\.\/proj\.android\/src\///g" temp.txt
sed -i "s/\//./g" temp.txt
sed -i "s/\.java//g" temp.txt

lines=`cat temp.txt`
for line in $lines
do
	echo "$line"	
	javah -d ./output -classpath ./../../proj.android/src -jni $line
done

#javah -d ./output -classpath ./../../proj.android/src -jni org.cocos2dx.ckbase.CKGameHelper

#rm temp.txt