(Modifications by Wyatt Ward)
This is just a fork of Dolphin 3.5 which aims to be more easily built under
newer Linux systems. It may also be useful for users of other OSes, but I
only really target Linux.

My computer has an Ironlake GPU, which no one has yet made OpenGL 3.0 drivers
for (despite it being capable of all but one feature of OGL 3). As a result,
I am stuck on old versions of Dolphin, but SDL2 support was broken in 3.5's
source code (which was written before it was finalized, back when it was called
SDL 1.3). 3.5 would crash upon starting a game or attempting to configure
gamecube controllers, but SDL 2 was required for controller rumble support, so
I couldn't just built it for SDL 1.2.

This version takes some code from a later version of Dolphin for input devices,
and modifies it where it was still incompatible (for instance,
'SDL_HAPTIC_SQUARE' (square wave rumble) was replaced with SDL_HAPTIC_LEFTRIGHT
(which gives the illusion of an unevenly weighted controller when a controller
has multiple motors, like the XBox 360 pad).

Unfortunately, because FFMpeg API breakage gives me a headache, and for other
reasons like not wanting to spend even more time than I already have fixing
five years of code rot, this is easiest to build in a chroot. I built it
in Debian Wheezy with SDL 2.0, WxWidgets 2.9.5, and FFmpeg 1.0.1 compiled
from source code by myself, and then set LD_LIBRARY_PATH when running the
emulator outside of the chroot to tell it where its necessary older libraries
were. Libav (which is in the Debian Wheezy repositories) may or may not work as
a drop-in for FFmpeg (My guess is that it won't... but I'm not fond of Libav).

to 'install' it, I've been making a folder called 'instdir', and then running
`make install /path/to/instdir` to get it to install in an isolated
environment.

(--Wyatt Ward, 21 March 2018)


Dolphin-emu - The Gamecube / Wii Emulator
==========================================
Homesite: http://dolphin-emu.org/
Project Site: http://code.google.com/p/dolphin-emu

Dolphin-emu is a emulator for Gamecube, Wii, Triforce that lets
you run Wii/GCN/Tri games on your Windows/Linux/Mac PC system.

Open Source Release under GPL 2

Project Leaders: F|RES, ector

Team members: http://code.google.com/p/dolphin-emu/people/

Please read the FAQ before use:

http://dolphin-emu.org/docs/faq/

System Requirements:
* OS: Microsoft Windows (XP/Vista or higher) or Linux or Apple Mac OS X (10.6 or higher).
  Windows XP x64 is NOT supported.
* Processor: Fast CPU with SSE2 supported (recommended at least 2Ghz).
  Dual Core for speed boost.
* Graphics: Any reasonably modern graphics card (Direct3D9/OpenGL 2.1, shader model 3.0).

[Command line usage]
Usage: Dolphin [-h] [-d] [-l] [-e <str>] [-b] [-V <str>] [-A <str>]
  -h, --help                	Show this help message
  -d, --debugger            	Opens the debugger
  -l, --logger              	Opens the logger
  -e, --exec=<str>          	Loads the specified file (DOL,ELF,WAD,GCM,ISO)
  -b, --batch             	Exit Dolphin with emulator
  -V, --video_backend=<str>  	Specify a video plugin
  -A, --audio_emulation=<str>	Low level (LLE) or high level (HLE) audio

[Libraries]
Cg: Cg Shading API (http://developer.nvidia.com/object/cg_toolkit.html)
*.pdb = Program Debug Database (use these symbols with a program debugger)

[DSP Emulator Engines]
HLE: High Level DSP Emulation
LLE: Low Level DSP Emulation (requires DSP dumps)
     Recompiler is faster than interpreter but may be buggy.

[Video Backends]
Direct3D9: Render with Direct3D 9
Direct3D11: Render with Direct3D 11
OpenGL: Render with OpenGL + Cg Shader Language
Software Renderer: Render using the CPU only (for devs only)

[Sys Files]
totaldb.dsy: Database of symbols (for devs only)
font_ansi.bin/font_sjis.bin: font dumps
setting-usa/jpn/usa.txt: config files for Wii

[Support Folders]
Cache: used to cache the ISO list
Config: emulator configuration files
Dump: anything dumped from dolphin will go here
GameConfig: holds the INI game config files
GC: Gamecube memory cards
Load: custom textures
Logs: logs go here
Maps: symbol tables go here (dev only)
OpenCL: OpenCL code
ScreenShots: screenshots are saved here
Shaders: post-processing shaders
StateSaves: save states are stored here
Wii: Wii saves and config is stored here
