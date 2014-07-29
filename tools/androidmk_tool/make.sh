#!/bin/bash
echo "hello androidmk tool"

rm -rf output
mkdir output

cp ../../proj.android/jni/Android.mk output/Android.mk

#make LOCAL_C_INCLUDES
echo "LOCAL_C_INCLUDES := ">> output/dir_temp.txt
find ./../../Classes -type d>> output/dir_temp.txt
find ./../../thirdpartylibs -type d>> output/dir_temp.txt
sed -i "s/\.\/\.\.\/\.\.\//\$\(LOCAL_PATH\)\/\.\.\/\.\.\//g" output/dir_temp.txt
sed -i "s/$/&\ \\\/g" output/dir_temp.txt

line=`cat output/dir_temp.txt | wc -l`
sed -i ''$line's/\\//' output/dir_temp.txt

echo -e '\033[41;33;1m PATH_BEGIN \033[0m'
#cat output/dir_temp.txt
echo "you can cat output/dir_temp.txt"
echo -e '\033[41;33;1m PATH_END \033[0m'

#make LOCAL_SRC_FILES
find ./../../Classes -name '*.cpp'>> output/temp_all.txt
echo "LOCAL_SRC_FILES := hellocpp/main.cpp">> output/path_temp.txt

temp_lines=`cat output/temp_all.txt`
for temp_line in $temp_lines
do
	if [ `echo $temp_line|grep Default` ];then
		echo "don't include $temp_line"
	else
		echo "$temp_line" >> output/path_temp.txt
	fi
done

sed -i "s/\.cpp/\.cpp\ \\\/g" output/path_temp.txt
sed -i "s/\.\/\.\.\/\.\.\//\.\.\/\.\.\//g" output/path_temp.txt

line=`cat output/path_temp.txt | wc -l`
sed -i ''$line's/\\//' output/path_temp.txt

echo -e '\033[41;33;1m SRC_BEGIN \033[0m'
#cat output/path_temp.txt
echo "you can cat output/path_temp.txt"
echo -e '\033[41;33;1m SRC_END \033[0m'

#==============================

#delete src_begin~src_end
src_begin=`grep "#src_begin" -n output/Android.mk | cut -d ":" -f1`
src_begin=$(($src_begin+1))
#echo $src_begin
src_end=`grep "#src_end" -n output/Android.mk | cut -d ":" -f1`
src_end=$(($src_end-1))
#echo $src_end
src_sum=$(($src_end-$src_begin))
#echo $src_sum
if [ $src_sum -ge 0 ]
then
	echo 'delete from '$src_begin' to '$src_end''
	sed -i ''$src_begin','$src_end'd' output/Android.mk
else
	cat 'warning delete nothing'
fi
#add src_begin~src_end
sed -i '/#src_begin/r output/path_temp.txt' output/Android.mk

#==============================

#delete c_begin~c_end
c_begin=`grep "#c_begin" -n output/Android.mk | cut -d ":" -f1`
c_begin=$(($c_begin+1))
#echo $c_begin
c_end=`grep "#c_end" -n output/Android.mk | cut -d ":" -f1`
c_end=$(($c_end-1))
#echo $c_end
src_sum=$(($c_end-$c_begin))
#echo $src_sum
if [ $src_sum -ge 0 ]
then
	echo 'delete from '$c_begin' to '$c_end''
	sed -i ''$c_begin','$c_end'd' output/Android.mk
else
	cat 'warning delete nothing'
fi
#add c_begin~c_end
sed -i '/#c_begin/r output/dir_temp.txt' output/Android.mk

#==============================

cp output/Android.mk ../../proj.android/jni/Android.mk 
