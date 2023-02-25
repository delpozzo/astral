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

#include "input.h"
#include "camera.h"
#include "graphics.h"

extern bln gQuit;

i32 gMouseX = 0;
i32 gMouseY = 0;
bln gInput[MAX_INPUT_KEYS];

void initInput()
{
    for(u8 i = 0; i < MAX_INPUT_KEYS; i++)
    {
        gInput[i] = blnFalse;
    }

    printf("[INFO] [INPUT] Input system initialized\n");
}

void updateInput()
{
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
            // check for quit (window closed)
            case(SDL_QUIT):
                gQuit = blnTrue;
                break;
            // update mouse coordinates
            case(SDL_MOUSEMOTION):
                gMouseX = e.motion.x;
                gMouseY = e.motion.y;
                break;
            // update keyboard input
            case(SDL_KEYDOWN):
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        gInput[inputUp] = blnTrue;
                        break;
                    case SDLK_DOWN:
                        gInput[inputDown] = blnTrue;
                        break;
                    case SDLK_LEFT:
                        gInput[inputLeft] = blnTrue;
                        break;
                    case SDLK_RIGHT:
                        gInput[inputRight] = blnTrue;
                        break;
                }
                break;
            case(SDL_KEYUP):
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        gInput[inputUp] = blnFalse;
                        break;
                    case SDLK_DOWN:
                        gInput[inputDown] = blnFalse;
                        break;
                    case SDLK_LEFT:
                        gInput[inputLeft] = blnFalse;
                        break;
                    case SDLK_RIGHT:
                        gInput[inputRight] = blnFalse;
                        break;
                }
                break;
            }
        }

    // check if window was resized
    if(checkWindowSize())
    {
        printf("[INFO] [INPUT] Window resized\n");
        resizeCamera();
    }
}

bln mouseCollide(SDL_Rect *box)
{
    if((gMouseX > box->x) && (gMouseX < box->x + box->w) && (gMouseY > box->y) && (gMouseY < box->y + box->h))
    {
        return blnTrue;
    }

    return blnFalse;
}

void closeInput()
{
    // placeholder
    printf("[INFO] [INPUT] Input system closed\n");
}

