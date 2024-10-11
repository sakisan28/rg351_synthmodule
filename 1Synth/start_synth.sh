#!/usr/bin/bash

fluidsynth -s -i -a alsa -o audio.alsa.device=hw:rockchiprk817co,0 -m alsa_seq -f $(dirname $0)/fluidsettings.txt &
sleep 5

fluid=$(aconnect -o -l | awk '/FLUID/{ print substr($2,1,length($2)-1);exit }')
k=$(aconnect -i -l | awk '/^client/ && !/(System|Midi\ Through)/{ print substr($2,1,length($2)-1) ($0~/Launchpad\ Mini/?":1":"");exit }')
aconnect ${k} ${fluid}
