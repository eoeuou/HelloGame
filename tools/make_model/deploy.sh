#!bin/bash

filename=$1
filenamebig=`tr '[a-z]' '[A-Z]' <<<"$1"`

rm -rf output
mkdir output

cp -rf templates/CKModel.h output/$1".h"
cp -rf templates/CKModel.cpp output/$1".cpp"

sed -i -e "s/CKMODEL/$filenamebig/g" output/$1".h"

sed -i -e "s/CKModel/$filename/g" output/$1".h"
sed -i -e "s/CKModel/$filename/g" output/$1".cpp"


