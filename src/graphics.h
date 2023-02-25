// ###########################################################################
//          Title: Astral Graphics System
//         Author: Mike Del Pozzo
//    Description: Handles the SDL window, renderer, frame delay, and the
//                 initialization/shutdown of the following subsystems:
//                 Sprite Subsystem, Text Subsystem, GUI Subsystem
//        Version: 0.2.0
//           Date: 24 Feb 2023
//        License: GPLv3 (see LICENSE)
//
//    Astral Copyright (C) 2023 Mike Del Pozzo
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
// ###########################################################################

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "datatypes.h"

bln initGraphics(char *windowTitle);
void clearScreen();
void nextFrame();
bln checkWindowSize();
void closeGraphics();

#endif

