# rg351_synthmodule
Portable game console become a synthesizer module
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

**link**  
FluidSynth [https://www.fluidsynth.org/](https://www.fluidsynth.org/)  

----
RG351 やそれに類するゲーム機 (aka 中華ゲーム機)をMIDI音源モジュールにする  
  
ArkOSが必要です。  

fluidsynth を起動して、MIDI デバイスと接続するスクリプトです。  
  
1Synth フォルダを /roms か /roms2 にコピーしてください。  
  
**インストール**  
もしArkOSのメニューに KODI があったら (RK3566 CPUを搭載した機種) fluidsynth はシステムにインストールされているので
インストールは不要です。  

KODI が無く、インストールする場合は：  
事前に WIFI を有効にしておいてください。  
Option - Filemanager から'setup_synth.sh' を Execute するとインストールされます。  

**使用**  
MIDI キーボード / パッドをゲーム機のOTGポートに接続します。  
Option - Filemanager から 'start_synth.sh' を Execute すると起動します。  
一見、すぐに終了してしまうように見えますが、音源はシステムに常駐しています。  
  
Option - Filenamgaer から 'stop_synth.sh' を Execute すると終了します。  
特に保存しなければならないデータはないので、ゲーム機自体を終了させてもかまいません。  
  
このスクリプトのデフォルトの soundfont は /usr/share/sounds/sf3/default-GM.sf3 です。fluidsynth パッケージのインストール時に自動的にインストールされます。  
別のものを持っている場合は、1Synth と同じ場所にでもファイルをコピーして、start_synth.sh の中で指定すると
使うことができます。スペースの入ったファイル名を使う場合は /roms/1Synth/'this is file.sf2' のように「'」でくくるか、/roms/1Synth/this\ is\ file.sft のように「\」でエスケープしてください。  

fluidsynth はマルチティンバーで動作しているので、MIDI CHを変えれば、別CHを鳴らすことができます。プログラムチェンジなどで音色を変えられますが、GMやXGなどの soundfont ファイルの内部の作りによって変え方は変わります。 CC91でリバーブ、CC93でコーラスが掛けられます。  


..まあ、ものすごくやる気のない、簡単なスクリプトですが、使ってみると結構楽しいです :-)
