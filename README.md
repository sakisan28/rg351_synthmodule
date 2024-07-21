# rg351_synthmodule
Portable game console become synthesizer module
for ArkOS.

Put 1Synth folder to /roms or /roms2.

**install**  
If your Game colsole have 'KODI menu' (RK3566 devices), no need to install.  
  
No 'KODI', try following:  
Option - Filemanager - execute 'setup_synth.sh' to setup, you have to enable wifi before setup.  
  
**use**  
Connect MIDI Keyboard or Pad to Game OTG port.  
Option - Filemanager - execute 'start_synth.sh' to start.  
You'll see application suddenly quit, but synth is resident on system.
  
Option - Filenamgaer - execute 'stop_synth.sh' to stop.  

Defaut soundfont file is /usr/share/sounds/sf3/default-GM.sf3  
If you have another file, you can rewrite path in start_synth.sh .
