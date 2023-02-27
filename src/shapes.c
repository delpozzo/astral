// ###########################################################################
//          Title: Astral Shape Functions
//         Author: Mike Del Pozzo
//    Description: Functions to draw shapes such as rectangles and circles.
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

void drawCircle(i32 x0, i32 y0, i32 radius, SDL_Color *color)
{
    if(gRenderer == NULL || color == NULL)
    {
        return;
    }

    SDL_SetRenderDrawColor(gRenderer, color->r, color->g, color->b, color->a);

    i32 x = 0, y = radius;
    i32 dp = 1 - radius;

    do
    {
        if (dp < 0)
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

