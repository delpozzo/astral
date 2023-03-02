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

#include "shapes.h"

extern SDL_Renderer *gRenderer;

SDL_Color rainbowColor;

void drawRect(SDL_Rect *rect, SDL_Color *color, bln fill)
{
    if(gRenderer == NULL || rect == NULL || color == NULL)
    {
        return;
    }

    SDL_SetRenderDrawColor(gRenderer, color->r, color->g, color->b, color->a);

    if(fill == blnTrue)
    {
        SDL_RenderFillRect(gRenderer, rect);
    }
    else
    {
        SDL_RenderDrawRect(gRenderer, rect);
    }
}

void drawRainbowRect(SDL_Rect *rect, u8 speed, bln fill)
{
    if(SDL_GetTicks() % speed == 0)
    {
        rainbowColor.r = rand() % 255;
        rainbowColor.b = rand() % 255;
        rainbowColor.g = rand() % 255;
    }

    drawRect(rect, &rainbowColor, fill);
}

void drawCircle(i32 x0, i32 y0, i32 radius, SDL_Color *color)
{
    if(gRenderer == NULL || color == NULL)
    {
        return;
    }

    SDL_SetRenderDrawColor(gRenderer, color->r, color->g, color->b, color->a);

    i32 x = 0;
    i32 y = radius;
    i32 dp = 1 - radius;

    do
    {
        if(dp < 0)
        {
            dp = dp + 2 * (++x) + 3;
        }
        else
        {
            dp = dp + 2 * (++x) - 2 * (--y) + 5;
        }

        SDL_RenderDrawPoint(gRenderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(gRenderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(gRenderer, x0 + x, y0 - y);
        SDL_RenderDrawPoint(gRenderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(gRenderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(gRenderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(gRenderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(gRenderer, x0 - y, y0 - x);
    } while (x < y);
}

void drawRainbowCircle(i32 x0, i32 y0, i32 radius, u8 speed)
{
    if(SDL_GetTicks() % speed == 0)
    {
        rainbowColor.r = rand() % 255;
        rainbowColor.b = rand() % 255;
        rainbowColor.g = rand() % 255;
    }

    drawCircle(x0, y0, radius, &rainbowColor);
}

void drawLine(i32 x1, i32 y1, i32 x2, i32 y2, SDL_Color *color)
{
    if(gRenderer == NULL || color == NULL)
    {
        return;
    }

    SDL_SetRenderDrawColor(gRenderer, color->r, color->g, color->b, color->a);

    SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);   
}

void drawRainbowLine(i32 x1, i32 y1, i32 x2, i32 y2, u8 speed)
{
    if(SDL_GetTicks() % speed == 0)
    {
        rainbowColor.r = rand() % 255;
        rainbowColor.b = rand() % 255;
        rainbowColor.g = rand() % 255;
    }

    drawLine(x1, y1, x2, y2, &rainbowColor);
}

