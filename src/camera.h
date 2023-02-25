// ###########################################################################
//          Title: Astral Camera System
//         Author: Mike Del Pozzo
//    Description: Camera management system for Astral.
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

#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

typedef struct CAMERA_S
{
    Entity *focus; // entity the camera will focus on
    Coord position; // x and y coordinates for camera
    i32 width; // camera viewport width
    i32 height; // camera viewport height
    i32 bufferW; // camera buffer width
    i32 bufferH; // camera buffer height
} Camera;

void initCamera(i32 bufferW, i32 bufferH);
void resizeCamera();
void updateCamera();
void closeCamera();

#endif

