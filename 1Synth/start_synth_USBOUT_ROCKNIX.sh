#!/usr/bin/bash

USBDEV=$(pactl list sinks short|grep 'alsa_output\.usb'|awk '{print $1;exit}')

fluidsynth -s -i -a pulseaudio -o audio.pulseaudio.device=hw:${USBDEV} -m alsa_seq -f $(dirname $0)/fluidsettings_ROCKNIX.txt &
sleep 5

fluid=$(aconnect -o -l | awk '/FLUID/{ print substr($2,1,length($2)-1);exit }')
k=$(aconnect -i -l | awk '/^client/ && !/(System|Midi\ Through)/{ print substr($2,1,length($2)-1) ($0~/Launchpad\ Mini/?":1":"");exit }')
aconnect ${k} ${fluid}
