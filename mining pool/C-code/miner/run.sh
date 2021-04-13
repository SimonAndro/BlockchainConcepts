#!/bin/bash

cd build

make 
tmp=$?
 echo "make return:" ${tmp}
if [ ${tmp} -ne 0 ]
then
echo "make <>return:" ${tmp}
 exit -1
fi
 

cd ../bin
./BTCmining  127.0.0.1 8081
