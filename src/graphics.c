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

#include "graphics.h"
#include "text.h"
#include "sprite.h"
#include "gui.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 800

void frameDelay(u32 delay); // private function called by nextFrame()

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
bln gQuit = blnFalse;
i32 gWinWidth = 0;
i32 gWinHeight = 0;

bln initGraphics(char *windowTitle)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("[ERROR] [GRAPHICS] SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return blnFalse;
    }

    gWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(gWindow == NULL)
    {
        printf("[ERROR] [GRAPHICS] Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return blnFalse;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL)
    {
        printf( "[ERROR] [GRAPHICS] Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return blnFalse;
    }

    // uncomment line below to keep fixed logical resolution for rendering
    //SDL_RenderSetLogicalSize(gRenderer, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf( "[ERROR] [GRAPHICS] SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return blnFalse;
    }

    if(TTF_Init() == -1)
    {
        printf("[ERROR] [GRAPHICS] SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return blnFalse;
    }

    SDL_GetWindowSize(gWindow, &gWinWidth, &gWinHeight);

    initSpriteList();
    initFontList();
    initGUI();

    printf("[INFO] [GRAPHICS] Graphics system initialized\n");

    return blnTrue;
}

void clearScreen()
{
    SDL_RenderClear(gRenderer);
}

void frameDelay(u32 delay)
{
    static u32 pass = 100;
    u32 diff = SDL_GetTicks() - pass;
    if(diff < delay) SDL_Delay(delay - diff);
    pass = SDL_GetTicks();
}

void nextFrame()
{
    SDL_RenderPresent(gRenderer);
    frameDelay(16); // 33 for 30 fps, 16 for 60 fps
}

bln checkWindowSize()
{
    i32 width;
    i32 height;

    SDL_GetWindowSize(gWindow, &width, &height);

    if(gWinWidth != width || gWinHeight != height)
    {
        // set globals and return 1 if window has been resized
        gWinWidth = width;
        gWinHeight = height;
        return blnTrue;
    }

    return blnFalse;
}

void closeGraphics()
{
    clearSpriteList();
    clearFontList();
    closeGUI();

    if(gRenderer != NULL)
    {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }

    if(gWindow != NULL)
    {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }

    IMG_Quit();
    TTF_Quit();

    printf("[INFO] [GRAPHICS] Graphics system closed\n");
}

