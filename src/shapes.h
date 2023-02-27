// ###########################################################################
//          Title: Astral Shape Functions
//         Author: Mike Del Pozzo
//    Description: Functions to draw shapes such as rectangles and circles.
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

#ifndef SHAPES_H
#define SHAPES_H

#include "datatypes.h"

// Draw a rectangle (filled or unfilled)
void drawRect(SDL_Rect *rect, SDL_Color *color, bln fill);

// Draw a circle at center (x0, y0) with specified radius
void drawCircle(i32 x0, i32 y0, i32 radius, SDL_Color *color);

#endif

