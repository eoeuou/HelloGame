#!bin/bash

filename=$1
filenamebig=`tr '[a-z]' '[A-Z]' <<<"$1"`

rm -rf output
mkdir output

cp -rf templates/CKManager.h output/$1".h"
cp -rf templates/CKManager.cpp output/$1".cpp"

sed -i -e "s/CKMANAGER/$filenamebig/g" output/$1".h"

sed -i -e "s/CKManager/$filename/g" output/$1".h"
sed -i -e "s/CKManager/$filename/g" output/$1".cpp"


