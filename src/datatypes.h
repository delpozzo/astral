// ###########################################################################
//          Title: Astral Data Types
//         Author: Mike Del Pozzo
//    Description: Astral data type mappings and declarations
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

#ifndef DATATYPES_H
#define DATATYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846 // pi in case it's not defined
#endif
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0) // converts degrees to radians
#define QUARTER_TURN M_PI/2 // pi/2 = quarter turn (90 degrees)

#define MAX_FILE_LENGTH 128 // max string length for filepath/filename

// Integers (signed)
typedef Sint8 i8;
typedef Sint16 i16;
typedef Sint32 i32;
typedef Sint64 i64;

// Integers (unsigned)
typedef Uint8 u8;
typedef Uint16 u16;
typedef Uint32 u32;
typedef Uint64 u64;

// Floats (signed)
typedef float f32;
typedef double f64;

// Boolean
typedef u8 bln;

enum blnEnum
{
    blnTrue = 1,
    blnFalse = 0
};

// 2D Coordinate
typedef struct COORD_S
{
    f32 x; // x positon
    f32 y; // y position
} Coord;

// Random
void seedRandom();

#endif

