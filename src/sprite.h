// ###########################################################################
//          Title: Astral Sprite Subsystem (Graphics)
//         Author: Mike Del Pozzo
//    Description: Handles loading/drawing sprites and background tiling.
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

#ifndef SPRITE_H
#define SPRITE_H

#include "datatypes.h"

typedef struct SPRITE_S
{
    SDL_Texture *image; // texture pointer
    char filename[MAX_FILE_LENGTH]; // path to .png file
    i32 imageWidth; // width of sprite sheet in pixels
    i32 imageHeight; // height of sprite sheet in pixels
    u16 frameWidth; // width of each frame in sprite sheet in pixels
    u16 frameHeight; // height of each frame in sprite sheet in pixels
    u16 framesPerLine; // number of frames per line in sprite sheet, automatically calculated
    bln used; // in-use flag for position in array
} Sprite;

void initSpriteList();
void clearSpriteList();
Sprite* loadSprite(char *filename, u16 frameWidth, u16 frameHeight);
void closeSprite(Sprite *sprite);
void drawSprite(Sprite *sprite, i32 x, i32 y, u16 frame, f32 rot, f32 scale, SDL_RendererFlip flip);
void drawBackgroundTiled(Sprite *sprite, u16 frame);

#endif

