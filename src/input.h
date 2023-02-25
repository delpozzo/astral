// ###########################################################################
//          Title: Astral Input System
//         Author: Mike Del Pozzo
//    Description: Handles mouse, keyboard, and gamepad input for Astral.
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

#ifndef INPUT_H
#define INPUT_H

#include "datatypes.h"

#define MAX_INPUT_KEYS 4

enum inputEnum
{
    inputUp = 0,
    inputDown = 1,
    inputLeft = 2,
    inputRight = 3
};

void initInput();
void updateInput();
bln mouseCollide(SDL_Rect *box);
void closeInput();

#endif

