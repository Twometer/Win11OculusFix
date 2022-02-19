# Win11OculusFix
Fixes the obnoxious lag occurring with Windows 11 and Oculus once and for all.

### The Problem

Windows 11 introduced an _optimization_ that limits all programs running in the background to 30 fps. As it so happens, the Oculus Server that renders to your headset is such a background process. The nauseating lag you see is caused by the 30 fps limit.

### The Solution

The most widely known solution is to enable the debug console, which opens a window in the server, making it a foreground process and bypassing the optimization.

I found this annoying, since I always had to have the console open. I made this tool, which does a similar thing, but much simpler and without the annoying console window. It injects into the Oculus Server process, and shows a message box, preventing the FPS limit. 

### Usage

Run the `OculusInjector.exe`. A new window (message box) should appear in the taskbar with the Oculus logo. Unminimize it and start playing - the lag should be gone. When you're done playing, you can close the box with the _Ok_ button.
