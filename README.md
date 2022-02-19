# Win11OculusFix
Fixes the obnoxious lag occurring with Windows 11 and Oculus once and for all.

### The Problem

Windows 11 introduced an _optimization_ that limits all programs running in the background to 30 fps. As it so happens, the Oculus Server that renders to your headset is such a background process. The nauseating lag you see is caused by the 30 fps limit.

### The Solution

The most widely known solution is to enable the debug console, which opens a window in the server, making it a foreground process and bypassing the optimization.

I found this annoying, since I always had to have the console open. I made this tool, which does a similar thing, but much simpler and without the annoying console window. It injects into the Oculus Server process, and shows a message box, preventing the FPS limit. 

### Usage

Download and unpack the zip file from the Releases section, then run the `OculusInjector.exe`. A new window (message box) should appear in the taskbar with the Oculus logo. Bring it to foreground (unminimize it) and start playing - the lag should be gone. When you're done playing, you can close the box with the _Ok_ button.

Unlike the Oculus debug console, it will not leave any window open on your system after you close the message box.

### Disclaimer

This program uses the Windows API to inject a custom DLL into the Oculus server process. Your antivirus **may** detect this as a malicious action - if so, this is a false positive. The release download is a straight build from the source code you can see in this repository, and it only does what I described above.

