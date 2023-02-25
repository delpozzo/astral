# Astral

## About

Astral is an open source 2D space game currently under developement. Astral is written in C and uses Simple DirectMedia Layer (SDL) libraries for low level access to graphics, input, and audio hardware. 

Astral has minimal hardware requirements. In its current state it can even run on a Raspberry Pi.

Starship sprites are created by taking bits from various creative commons photos (engine parts, aircraft, gears, industrial machines, etc.) and "scrap-booking" them together in GIMP.

Astral is in the early stages of development and is being developed for fun in my spare time.

![Screenshot](screenshots/astral_screenshot_20220224.png?raw=true)

### To-Do List

- [ ] Audio system
- [ ] Collision detection
- [ ] Inertial stabalization
- [ ] Load map from .map file
- [ ] Ship Outfitting
- [ ] Asteroids / Mining
- [ ] NPCs
- [ ] Windows build files and instructions
- [ ] MacOS build files and instructions

### Partially Complete

- [-] Input system
- [-] Map system
- [-] GUI subsystem

### Complete

- [x] Primary graphics system
- [x] Text subsystem
- [x] Sprite subsystem
- [x] Entity management system
- [x] Camera management system
- [x] Parallax scrolling

## Dependencies

### Linux

To compile Astral on Linux you will need a gcc compiler as well as the sdl2, sdl2_image, and sdl_ttf libraries. Your mileage may vary, but here are some examples of installing these dependencies:

**Arch Linux**

`sudo pacman -S gcc sdl2 sdl2_image sdl2_ttf`

**Debian / Ubuntu**

`sudo apt-get update`

`sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev`

## Building

### Linux

**Step 1:** Clone the Astral repository

`git clone https://github.com/delpozzo/astral.git`

**Step 2:** Enter into the resulting directory from step 1

`cd /path/to/astral`

**Step 3:** Compile Astral

`make`

**Step 4:** Run Astral

`./astral`

### Windows

TBD

### macOS

TBD

## Instructions

Astral launches by default in a 1280x800 window. This window can be resized and the graphics system will automatically adapt.

You can also change the default window size in "graphics.c" for now if desired (be sure to re-complie):

`#define DEFAULT_WINDOW_WIDTH 1280`
`#define DEFAULT_WINDOW_HEIGHT 800`

### Keyboard Controls

- **Up** - Engage engine.
- **Left** - Turn ship left.
- **Right** - Turn ship right.

## FAQ

**The application won't launch and I am getting [TEXT] and [SPRITE] errors / warnings**

This is due to the fact that Astral currently uses a relative path for loading resources in the `sprites/` and `fonts/` directories. For now, enter the astral directory first, then run the application:

`cd /path/to/astral`

`./astral`

You can create a shell script to automate this which can be called from menu/desktop shortcuts:

astral.sh example:
```
#!/bin/sh

cd /path/to/astral
./astral
```

Don't forget to set the execute bit on the shell script you created:

`chmod +x astral.sh`

**What about Windows or Mac support?**

The source code should compile fine on both platforms with little to no modification as long as the proper sdl2 libraries are installed. I plan to release build files and instructions for multiple platforms in the future.

## License

Astral Copyright (C) 2023 Mike Del Pozzo

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

See [LICENSE](LICENSE) for details.
