// ###########################################################################
//          Title: Astral Planet Functions
//         Author: Mike Del Pozzo
//    Description: Functions related to planets.
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

#include "planet.h"

Entity* spawnPlanet(char *name, i32 x, i32 y)
{
    Entity *self = spawnEntity();
    if(self == NULL)
    {
        printf("[WARN] [PLANET] Unable to spawn planet: %s\n", name);
        return NULL;
    }

    if(strncmp(name, "Earth", MAX_NAME_LENGTH) == 0)
    {
        self->spriteSheet = loadSprite("sprites/earth.png", 512, 512);
    }
    else if(strncmp(name, "Moon", MAX_NAME_LENGTH) == 0)
    {
        self->spriteSheet = loadSprite("sprites/moon.png", 256, 256);
    }
    else
    {
        printf("[WARN] [PLANET] Unable to find planet: %s\n", name);
        freeEntity(self);
        return NULL;
    }

    strncpy(self->name, name, MAX_NAME_LENGTH);
    self->type = typePlanet;
    self->frame = 0;
    self->scale = 0.5;
    self->position.x = x;
    self->position.y = y;

    return self;
}

