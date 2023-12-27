#!/bin/bash
command="uname"
read  LV << $(command) 
#
# -a |perl -ne' print $$1  if (/^.*? .*? (.*?) /)'
#echo "LV = $LV"
if [$? -eq ${LV}]; 
  then LINUX_VER = "ubuntu"
fi

echo "The value is ${LINUX_VER}"
echo $LV

