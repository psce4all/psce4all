# psce4all
PlayStation Console Emulators For All

## Disclaimer
The goal of this project is to experiment, research, and educate on the topic of emulation of modern devices and operating systems.

## Quickstart
Windows 7 or later with Python 2.7 and Visual Studio 2013 installed.

## Contributors Wanted!
Have some spare time, know advanced C++, and want to write an emulator? Contribute! There's a ton of work that needs to be done, a lot of which is wide open greenfield fun.

## Remark
Everything may undergo change.

## ps1e4all
I like the idea to write one from scratch with some tricks used in __pspe4all__, especially the interpreter-like dynarec. It would be a low-level emulator, no HLE unlike __pspe4all__, but with a lot of shared code with __pspe4all__. 

## ps2e4all
Dunno. Having both __ps1e4all__ and __pspe4all__ is quite a big task.

## pspe4all
While there were two previous versions (__PCSP__ and old __PSPE4ALL__ with Qt 4.8), they suffered some drawbacks which made me to reconsider a new version of pspe4all without Qt. But helas without HLE and GE for the moment too as they need a major rewriting. It is also the first time I added an X86-64 dynarec to emulate Allegrex in __pspe4all__.  

### Limitations
* __Memory__: pspe4all emulates the PSP user-mode environment, which uses 32-bit addresses. This reflects on the CPU / Memory related code, and could cause issues if you use it for other platforms, or for designing a low-level PSP emulator.
* __Portability__: pspe4all assumes that the host system (Windows 7 or later) runs on a little endian CPU, with 64-bit addresses.

## ps3e4all

Huh... let me breathe!

## ps4e4all

Seriously!?

