#!bin/bash
#example: sh deploy.sh Share

filename=$1
filenamebig=`tr '[a-z]' '[A-Z]' <<<"$1"`
filenamesmall=`tr '[A-Z]' '[a-z]' <<<"$1"`

rm -rf output
mkdir output

filename="CK"$1"Engine"
hfile="CK"$1"Engine.h"
cppfile="CK"$1"Engine.cpp"

echo $hfile
echo $cppfile
echo $filenamebig

cp -rf templates/CKPayEngine.h output/$hfile
cp -rf templates/CKPayEngine.cpp output/$cppfile

#DefaultEngine
hfile="CKDefault"$1"Engine.h"
cppfile="CKDefault"$1"Engine.cpp"

cp -rf templates/CKDefaultPayEngine.h output/$hfile
cp -rf templates/CKDefaultPayEngine.cpp output/$cppfile

#AndroidEngine
hfile="CKAndroid"$1"Engine.h"
cppfile="CKAndroid"$1"Engine.cpp"

cp -rf templates/CKAndroidPayEngine.h output/$hfile
cp -rf templates/CKAndroidPayEngine.cpp output/$cppfile

#IOSEngine
hfile="CKIOS"$1"Engine.h"
cppfile="CKIOS"$1"Engine.mm"

cp -rf templates/CKIOSPayEngine.h output/$hfile
cp -rf templates/CKIOSPayEngine.mm output/$cppfile

#sed something
sed -i -e "s/PAY/$filenamebig/g" output/*
sed -i -e "s/pay/$filenamesmall/g" output/*

sed -i -e "s/CKPayEngine/$filename/g" output/*

sed -i -e "s/Pay/$1/g" output/*


