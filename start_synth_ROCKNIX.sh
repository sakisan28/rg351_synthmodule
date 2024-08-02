#!/usr/bin/bash

fluidsynth -s -i -a pulseaudio -m alsa_seq -g 1.0 /usr/share/soundfonts/GeneralUser.sf2 &

sleep 7

fluid=$(aconnect -o -l | awk '/FLUID/{ print substr($2,1,length($2)-1);exit }')
k=$(aconnect -i -l | awk '/^client/ && !/(System|Midi\ Through)/{ print substr($2,1,length($2)-1) ($0~/Launchpad\ Mini/?":1":"");exit }')
aconnect ${k} ${fluid}
