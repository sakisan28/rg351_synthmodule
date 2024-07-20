#!/usr/bin/bash

fluidsynth -s -i -a alsa -o audio.alsa.device=default -m alsa_seq -g 1.0 /usr/share/sounds/sf3/default-GM.sf3 &
#GeneralUser GS
#fluidsynth -s -i -a alsa -o audio.alsa.device=default -m alsa_seq -g 1.0 /roms2/1M8ARK/'GeneralUser GS v1.471.sf2' &

sleep 2

#m8=$(aconnect -i -l | awk '/M8/{ print substr($2,1,length($2)-1);exit }')
#fluid=$(aconnect -o -l | awk '/FLUID/{ print substr($2,1,length($2)-1);exit }')

#aconnect ${m8} ${fluid}
