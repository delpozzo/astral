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

#include "sprite.h"

#define MAX_SPRITES 128

extern SDL_Renderer *gRenderer;
extern bln gQuit;
extern i32 gWinWidth;
extern i32 gWinHeight;

Sprite SpriteList[MAX_SPRITES];

u16 spritesLoaded = 0;

void initSpriteList()
{
    for(u16 i = 0; i < MAX_SPRITES; i++)
    {
        SpriteList[i].image = NULL;
        strncpy(SpriteList[i].filename, "", MAX_FILE_LENGTH);
        SpriteList[i].imageWidth = 0;
        SpriteList[i].imageHeight = 0;
        SpriteList[i].frameWidth = 0;
        SpriteList[i].frameHeight = 0;
        SpriteList[i].framesPerLine = 0;
        SpriteList[i].used = blnFalse;
    }

    printf("[INFO] [SPRITE] Sprite list initialized (%i slots available)\n", MAX_SPRITES);
}

void clearSpriteList()
{
    for(u16 i = 0; i < MAX_SPRITES; i++)
    {
        closeSprite(&SpriteList[i]);
    }

    printf("[INFO] [SPRITE] Sprite list cleared\n");
}

Sprite* loadSprite(char *filename, u16 frameWidth, u16 frameHeight)
{
    if(frameWidth < 1 || frameHeight < 1)
    {
        printf("[ERROR] [SPRITE] Unable to load image %s! frameWidth and frameHeight must be > 0\n", filename);
        gQuit = blnTrue;
        return NULL;
    }

    for(u16 i = 0; i < MAX_SPRITES; i++)
    {
        if(strncmp(filename, SpriteList[i].filename, MAX_FILE_LENGTH) == 0)
        {
            return &SpriteList[i];
        }
    }

    SDL_Surface *loadedSurface = NULL;

    for(u16 i = 0; i < MAX_SPRITES; i++)
    {
        if(SpriteList[i].used == blnFalse)
        {
            loadedSurface = IMG_Load(filename);
            if(loadedSurface == NULL)
            {
                printf("[ERROR] [SPRITE] Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
                gQuit = blnTrue;
                return NULL;
            }

            SpriteList[i].image = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            SDL_FreeSurface(loadedSurface);
            loadedSurface = NULL;
            if(SpriteList[i].image == NULL)
            {
                printf("[ERROR] [SPRITE] Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
                gQuit = blnTrue;
                return NULL;
            }

            strncpy(SpriteList[i].filename, filename, MAX_FILE_LENGTH);
            SDL_QueryTexture(SpriteList[i].image, NULL, NULL, &SpriteList[i].imageWidth, &SpriteList[i].imageHeight);
            SpriteList[i].frameWidth = frameWidth;
            SpriteList[i].frameHeight = frameHeight;
            SpriteList[i].framesPerLine = SpriteList[i].imageWidth / frameWidth;
            SpriteList[i].used = blnTrue;

            spritesLoaded++;
            printf("[INFO] [SPRITE] Sprites loaded: %i/%i\n", spritesLoaded, MAX_SPRITES);

            return &SpriteList[i];
        }
    }

    printf("[ERROR] [SPRITE] Sprite limit reached");
    gQuit = blnTrue;
    return NULL;
}

void closeSprite(Sprite *sprite)
{
    if(sprite == NULL || sprite->image == NULL)
    {
        return;
    }

    SDL_DestroyTexture(sprite->image);
    sprite->image = NULL;
    strncpy(sprite->filename, "", MAX_FILE_LENGTH);
    sprite->imageWidth = 0;
    sprite->imageHeight = 0;
    sprite->frameWidth = 0;
    sprite->frameHeight = 0;
    sprite->framesPerLine = 0;
    sprite->used = blnFalse;

    spritesLoaded--;
    printf("[INFO] [SPRITE] Sprites loaded: %i/%i\n", spritesLoaded, MAX_SPRITES);
}

void drawSprite(Sprite *sprite, i32 x, i32 y, u16 frame, f32 rot, f32 scale, SDL_RendererFlip flip)
{
    if(sprite == NULL || sprite->image == NULL)
    {
        printf("[ERROR] [SPRITE] Tried to draw a sprite that was null\n");
        gQuit = blnTrue;
        return;
    }

    SDL_Rect clip;
    clip.x = (frame % sprite->framesPerLine) * sprite->frameWidth;
    clip.y = (frame / sprite->framesPerLine) * sprite->frameHeight;
    clip.w = sprite->frameWidth;
    clip.h = sprite->frameHeight;

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = sprite->frameWidth * scale;
    dest.h = sprite->frameHeight * scale;

    SDL_RenderCopyEx(gRenderer, sprite->image, &clip, &dest, rot, NULL, flip);
}

void drawBackgroundTiled(Sprite *sprite, u16 frame)
{
    if(sprite == NULL || sprite->image == NULL)
    {
        printf("[ERROR] [SPRITE] Tried to draw a bg with a sprite that was null\n");
        gQuit = blnTrue;
        return;
    }

    u32 xTiles = 1 + (gWinWidth / sprite->frameWidth);
    u32 yTiles = 1 + (gWinHeight / sprite->frameHeight);

    for(u32 i = 0; i < xTiles * yTiles; i++)
    {
        u32 x = i % xTiles;
        u32 y = i / xTiles;
        drawSprite(sprite, x * sprite->frameWidth, y * sprite->frameHeight, frame, 0, 1.0, SDL_FLIP_NONE);
    }
}

