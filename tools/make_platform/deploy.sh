#!bin/bash
#example: sh deploy.sh Share

filename=$1
filenamebig=`tr '[a-z]' '[A-Z]' <<<"$1"`
filenamesmall=`tr '[A-Z]' '[a-z]' <<<"$1"`

rm -rf output
mkdir output

begname="CK"
#endname="Engine"
filename=$begname$1$endname""
hfile=$begname$1$endname".h"
cppfile=$begname$1$endname".cpp"

echo $hfile
echo $cppfile
echo $filenamebig

cp -rf templates/CKPayEngine.h output/$hfile
cp -rf templates/CKPayEngine.cpp output/$cppfile

#DefaultEngine
hfile=$begname"Default"$1$endname".h"
cppfile=$begname"Default"$1$endname".cpp"

cp -rf templates/CKDefaultPayEngine.h output/$hfile
cp -rf templates/CKDefaultPayEngine.cpp output/$cppfile

#AndroidEngine
hfile=$begname"Android"$1$endname".h"
cppfile=$begname"Android"$1$endname".cpp"

cp -rf templates/CKAndroidPayEngine.h output/$hfile
cp -rf templates/CKAndroidPayEngine.cpp output/$cppfile

#IOSEngine
hfile=$begname"IOS"$1$endname".h"
cppfile=$begname"IOS"$1$endname".mm"

cp -rf templates/CKIOSPayEngine.h output/$hfile
cp -rf templates/CKIOSPayEngine.mm output/$cppfile

#sed something
sed -i -e "s/PAY/$filenamebig/g" output/*
sed -i -e "s/pay/$filenamesmall/g" output/*

sed -i -e "s/CKPayEngine/$filename/g" output/*

sed -i -e "s/Pay/$1/g" output/*

