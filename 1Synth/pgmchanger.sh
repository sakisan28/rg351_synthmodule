#!/usr/bin/bash

cd $(dirname $0)

fluid=$(aconnect -o -l | awk '/FLUID/{ print substr($2,1,length($2)-1);exit }')

./pgmchanger ${fluid}
