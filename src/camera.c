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

#include "camera.h"

extern i32 gWinWidth;
extern i32 gWinHeight;

Camera gCamera;

void initCamera(i32 bufferW, i32 bufferH)
{
    gCamera.focus = NULL;
    gCamera.position.x = 0;
    gCamera.position.y = 0;
    gCamera.width = gWinWidth;
    gCamera.height = gWinHeight;
    gCamera.bufferW = bufferW;
    gCamera.bufferH = bufferH;

    printf("[INFO] [CAMERA] Camera initialized\n");
}

void resizeCamera()
{
    gCamera.width = gWinWidth;
    gCamera.height = gWinHeight;
    printf("[INFO] [CAMERA] Camera resized\n");
}

void updateCamera()
{
    if(gCamera.focus == NULL || gCamera.focus->used == blnFalse || gCamera.focus->spriteSheet == NULL)
    {
        return;
    }

    Coord adjustedPos;
    adjustedPos.x = gCamera.focus->position.x + ((gCamera.focus->spriteSheet->frameWidth * gCamera.focus->scale) / 2) - (gCamera.width >> 1);
    adjustedPos.y = gCamera.focus->position.y + ((gCamera.focus->spriteSheet->frameHeight * gCamera.focus->scale) / 2) - (gCamera.height >> 1);

    gCamera.position.x = adjustedPos.x;

    if(gCamera.position.x < 0)
    {
        gCamera.position.x = 0;
    }
    else if(gCamera.position.x > gCamera.bufferW - gCamera.width)
    {
        gCamera.position.x = gCamera.bufferW - gCamera.width;
    }

    gCamera.position.y = adjustedPos.y;

    if(gCamera.position.y < 0)
    {
        gCamera.position.y = 0;
    }
    else if(gCamera.position.y > gCamera.bufferH - gCamera.height)
    {
        gCamera.position.y = gCamera.bufferH - gCamera.height;
    }
}

void closeCamera()
{
    gCamera.focus = NULL;
    printf("[INFO] [CAMERA] Camera closed\n");
}

