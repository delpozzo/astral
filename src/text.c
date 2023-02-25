// ###########################################################################
//          Title: Astral Text Subsystem (Graphics)
//         Author: Mike Del Pozzo
//    Description: Handles ttf font loading and rendering for Astral.
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

#include "text.h"

#define MAX_FONTS 16

extern SDL_Renderer *gRenderer;
extern bln gQuit;

Font FontList[MAX_FONTS];

SDL_Color defaultFontColor = {255, 255, 255, 255};
u8 fontsLoaded = 0;

void initFontList()
{
    for(u8 i = 0; i < MAX_FONTS; i++)
    {
        FontList[i].ttf = NULL;
        strncpy(FontList[i].filename, "", MAX_FILE_LENGTH);
        FontList[i].color = defaultFontColor;
        FontList[i].used = blnFalse;
    }

    printf("[INFO] [TEXT] Font list initialized (%i slots available)\n", MAX_FONTS);
}

Font* loadFont(char *filename, u16 size, u8 style, u8 outline)
{    
    for(u8 i = 0; i < MAX_FONTS; i++)
    {
        if(strncmp(filename, FontList[i].filename, MAX_FILE_LENGTH) == 0)
        {
            return &FontList[i];
        }
    }

    TTF_Font *loadedFont = NULL;

    for(u8 i = 0; i < MAX_FONTS; i++)
    {
        if(FontList[i].used == blnFalse)
        {
            loadedFont = TTF_OpenFont(filename, size);
            if(loadedFont == NULL)
            {
                printf("[WARN] [TEXT] Unable to load font %s! SDL_ttf Error: %s\n", filename, TTF_GetError());
                return NULL;
            }

            FontList[i].ttf = loadedFont;
            TTF_SetFontStyle(loadedFont, style);
            TTF_SetFontOutline(loadedFont, outline);
            loadedFont = NULL;

            strncpy(FontList[i].filename, filename, MAX_FILE_LENGTH);
            FontList[i].color = defaultFontColor;
            FontList[i].used = blnTrue;

            fontsLoaded++;
            printf("[INFO] [TEXT] Fonts loaded: %i/%i\n", fontsLoaded, MAX_FONTS);

            return &FontList[i];
        }
    }

    printf("[WARN] [TEXT] Font limit reached\n");
    return NULL;
}

void clearFontList()
{
    for(u8 i = 0; i < MAX_FONTS; i++)
    {
        closeFont(&FontList[i]);
    }

    printf("[INFO] [TEXT] Font list cleared\n");
}

void setFontColor(Font *font, SDL_Color color)
{
    if(font == NULL)
    {
        printf("[WARN] [TEXT] Tried to set color of a font that was null\n");
        return;
    }

    font->color = color;
}

void closeFont(Font *font)
{
    if(font == NULL || font->ttf == NULL)
    {
        return;
    }

    TTF_CloseFont(font->ttf);
    font->ttf = NULL;
    strncpy(font->filename, "", MAX_FILE_LENGTH);
    font->color = defaultFontColor;
    font->used = blnFalse;

    fontsLoaded--;
    printf("[INFO] [TEXT] Fonts loaded: %i/%i\n", fontsLoaded, MAX_FONTS);
}

void drawText(Font *font, i32 x, i32 y, const char *text)
{
    if(font == NULL || font->ttf == NULL)
    {
        printf("[ERROR] [TEXT] Tried to use a font that was null\n");
        gQuit = blnTrue;
        return;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font->ttf, text, font->color);
    if(textSurface == NULL)
    {
        printf("[ERROR] [TEXT] Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        gQuit = blnTrue;
        return;
    }

    SDL_Texture *mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = textSurface->w;
    dest.h = textSurface->h;

    SDL_FreeSurface(textSurface);
    textSurface = NULL;

    if(mTexture == NULL)
    {
        printf("[ERROR] [TEXT] Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        gQuit = blnTrue;
        return;
    }

    SDL_RenderCopyEx(gRenderer, mTexture, NULL, &dest, 0, NULL, SDL_FLIP_NONE);

    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}

