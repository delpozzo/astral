// ###########################################################################
//          Title: Astral GUI Subsystem (Graphics)
//         Author: Mike Del Pozzo
//    Description: Handles Graphical User Interface elements such as buttons,
//                 windows, and displaying debug information.
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

#include "gui.h"
#include "text.h"

#define MAX_DEBUG_LENGTH 128
#define DEBUG_SPACING 25

Font *debugFont = NULL;
char debugTextBuffer[MAX_DEBUG_LENGTH] = "";

void initGUI()
{
    debugFont = loadFont("fonts/DejaVuSansMono.ttf", 16, TTF_STYLE_NORMAL, 0);
    setFontColor(debugFont, (SDL_Color){255, 255, 0});

    printf("[INFO] [GUI] GUI initialized\n");
}

void closeGUI()
{
    debugFont = NULL;

    printf("[INFO] [GUI] GUI closed\n");
}

void displayEntityDebugInfo(Entity *ent, i32 x, i32 y)
{
    if(ent == NULL || ent->used == blnFalse)
    {
        return;
    }

    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Entity: %s", ent->name);
    drawText(debugFont, x, y, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Rotation: %f", ent->rotation);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Position: (%f, %f)", ent->position.x, ent->position.y);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Velocity: (%f, %f)", ent->velocity.x, ent->velocity.y);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Sprite Frame: %i", ent->frame);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Sprite Scale: %f", ent->scale);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Accel Speed: %f", ent->accelSpeed);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Turn Speed: %f", ent->turnSpeed);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
    snprintf(debugTextBuffer, MAX_DEBUG_LENGTH, "Max Speed: %f", ent->maxSpeed);
    drawText(debugFont, x, y+=DEBUG_SPACING, debugTextBuffer);
}

