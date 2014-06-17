#!/bin/bash
echo "hello javah tool"
rm -rf output
lines=`find ./../../proj.android/src -name '*.java'`
#echo "lines=$lines"
for line in $lines
do
	echo "$line"
done
#javah -d ./output -classpath ./../../proj.android/src -jni org.cocos2dx.ckbase.CKGameHelper