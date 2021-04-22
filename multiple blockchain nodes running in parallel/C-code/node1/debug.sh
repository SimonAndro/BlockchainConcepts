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
gdb ./BTCmining Node1 8081

