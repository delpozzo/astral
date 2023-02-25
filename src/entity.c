// ###########################################################################
//          Title: Astral Entity System
//         Author: Mike Del Pozzo
//    Description: Entity management system for Astral.
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

#include "entity.h"
#include "camera.h"

#define MAX_ENTITIES 1024 // max number of entities that can exist at a time

extern Camera gCamera;

Entity EntityList[MAX_ENTITIES];

void initEntityList()
{
    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        freeEntity(&EntityList[i]);
    }

    printf("[INFO] [ENTITY] Entity list initialized (%i slots available)\n", MAX_ENTITIES);
}

Entity *spawnEntity()
{
    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        if(EntityList[i].used == blnFalse)
        {
            EntityList[i].used = blnTrue;
            return &EntityList[i];
        }
    }

    printf("[WARN] [ENTITY] Entity limit reached\n");
    return NULL;
}

void freeEntity(Entity *ent)
{
    if(ent == NULL)
    {
        return;
    }

    strncpy(ent->name, "", MAX_NAME_LENGTH);
    ent->type = typeNone;
    ent->spriteSheet = NULL;
    ent->frame = 0;
    ent->position.x = 0;
    ent->position.y = 0;
    ent->velocity.x = 0;
    ent->velocity.y = 0;
    ent->rotation = 0;
    ent->scale = 1;
    ent->accelSpeed = 0;
    ent->turnSpeed = 0;
    ent->maxSpeed = 0;
    ent->used = blnFalse;
    ent->think = NULL;
}

void clearEntityList()
{
    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        freeEntity(&EntityList[i]);
    }

    printf("[INFO] [ENTITY] Entity list cleared\n");
}

void drawEntity(Entity *ent)
{
    if(ent == NULL)
    {
        printf("[WARN] [ENTITY] Tried to draw entity that was null\n");
        return; 
    }

    drawSprite(ent->spriteSheet, ent->position.x - gCamera.position.x, ent->position.y - gCamera.position.y, ent->frame, ent->rotation, ent->scale, SDL_FLIP_NONE);
}

void drawAll()
{
    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        if(EntityList[i].used == blnTrue)
        {
            drawEntity(&EntityList[i]);
        }
    }
}

void thinkAll()
{
    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        if(EntityList[i].used == blnTrue && EntityList[i].think != NULL)
        {
            EntityList[i].think(&EntityList[i]);
        }
    }
}

