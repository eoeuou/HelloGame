#!/bin/bash
echo "hello androidmk tool"

rm -rf output
mkdir output

echo "LOCAL_C_INCLUDES := ">> output/dir_temp.txt
find ./../../Classes -type d>> output/dir_temp.txt
sed -i "s/\.\/\.\.\/\.\.\//\$\(LOCAL_PATH\)\/\.\.\/\.\.\//g" output/dir_temp.txt
sed -i "s/$/&\ \\\/g" output/dir_temp.txt

echo -e '\033[41;33;1m PATH_BEGIN \033[0m'
cat output/dir_temp.txt
echo -e '\033[41;33;1m PATH_END \033[0m'

rm output/temp.txt
rm output/temp_all.txt

#search *.cpp
find ./../../Classes -name '*.cpp'>> output/temp_all.txt
echo "LOCAL_SRC_FILES := hellocpp/main.cpp ">> output/temp.txt

temp_lines=`cat output/temp_all.txt`
for temp_line in $temp_lines
do
	if [ `echo $temp_line|grep Default` ];then
		echo "don't include $temp_line"
	else
		echo "$temp_line" >> output/temp.txt
	fi
done

rm output/temp_all.txt

sed -i "s/\.cpp/\.cpp\ \\\/g" output/temp.txt
sed -i "s/\.\/\.\.\/\.\.\//\.\.\/\.\.\//g" output/temp.txt

echo -e '\033[41;33;1m SRC_BEGIN \033[0m'
cat output/temp.txt
echo -e '\033[41;33;1m SRC_END \033[0m'
exit
