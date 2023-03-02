// ###########################################################################
//          Title: Astral Shape Functions
//         Author: Mike Del Pozzo
//    Description: Functions to draw basic shapes such as rectangles,
//                 circles, and lines.
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

// Same as above, but with random generated colors
void drawRainbowRect(SDL_Rect *rect, u8 speed, bln fill);

// Draw a circle at center (x0, y0) with specified radius
void drawCircle(i32 x0, i32 y0, i32 radius, SDL_Color *color);

// Same as above, but with random generated colors
void drawRainbowCircle(i32 x0, i32 y0, i32 radius, u8 speed);

// Draw a line from (x1, y1) to (x2, y2)
void drawLine(i32 x1, i32 y1, i32 x2, i32 y2, SDL_Color *color);

// Same as above, but with random generated colors
void drawRainbowLine(i32 x1, i32 y1, i32 x2, i32 y2, u8 speed);

#endif

