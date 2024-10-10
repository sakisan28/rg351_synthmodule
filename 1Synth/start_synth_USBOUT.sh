#!/usr/bin/bash

USBDEV=$(aplay -l|grep '\[USB Audio\]' | awk '{print $3;exit}')

fluidsynth -s -i -a alsa -o audio.alsa.device=hw:${USBDEV},0 -m alsa_seq -g 1.0 /usr/share/sounds/sf2/FluidR3_GM.sf2 &
#fluidsynth -s -i -a alsa -o audio.alsa.device=hw:rockchiprk817co,0 -m alsa_seq -g 1.0 /usr/share/sounds/sf3/default-GM.sf3 &

sleep 7

fluid=$(aconnect -o -l | awk '/FLUID/{ print substr($2,1,length($2)-1);exit }')
k=$(aconnect -i -l | awk '/^client/ && !/(System|Midi\ Through)/{ print substr($2,1,length($2)-1) ($0~/Launchpad\ Mini/?":1":"");exit }')
aconnect ${k} ${fluid}
