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

#ifndef TEXT_H
#define TEXT_H

#include "datatypes.h"

typedef struct FONT_S
{
    TTF_Font *ttf; // font pointer
    char filename[MAX_FILE_LENGTH]; // path to .ttf file
    SDL_Color color; // font color
    bln used; // in-use flag for position in array
} Font;

void initFontList();
void clearFontList();
Font* loadFont(char *filename, u16 size, u8 style, u8 outline);
void setFontColor(Font *font, SDL_Color color);
void closeFont(Font *font);
void drawText(Font *font, i32 x, i32 y, const char *text);

#endif

