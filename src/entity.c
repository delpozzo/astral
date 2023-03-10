// ###########################################################################
//          Title: Astral Entity System
//         Author: Mike Del Pozzo
//    Description: Entity management system for Astral. Handles entity
//                 drawing, thinking, spawning, freeing, and collisions.
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
#include "shapes.h"

#define MAX_ENTITIES 1024 // max number of entities that can exist at a time

extern Camera gCamera;

Entity EntityList[MAX_ENTITIES];

SDL_Color bboxColor = {255, 255, 0};

void initEntityList()
{
    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        freeEntity(&EntityList[i]);
    }

    printf("[INFO] [ENTITY] Entity list initialized (%i slots available)\n", MAX_ENTITIES);
}

Entity* spawnEntity()
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
    ent->bbox.rect[0].x = 0;
    ent->bbox.rect[0].y = 0;
    ent->bbox.rect[0].w = 0;
    ent->bbox.rect[0].h = 0;
    ent->bbox.rect[1] = ent->bbox.rect[0];
    ent->bbox.offsetX[0] = 0;
    ent->bbox.offsetY[0] = 0;
    ent->bbox.offsetX[1] = 0;
    ent->bbox.offsetY[1] = 0;
    ent->bbox.activeBox = 0;
    ent->collidable = blnFalse;
    ent->rotation = 0;
    ent->scale = 1;
    ent->accelSpeed = 0;
    ent->turnSpeed = 0;
    ent->maxSpeed = 0;
    ent->used = blnFalse;
    ent->owner = NULL;
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

void createBoundingBox(Entity *ent, f32 scale)
{
    if(ent == NULL || ent-> used == blnFalse || ent->spriteSheet == NULL)
    {
        return;
    }

    // original width and height (factoring in sprite scaling)
    i32 w = ent->spriteSheet->frameWidth * ent->scale;
    i32 h = ent->spriteSheet->frameHeight * ent->scale;

    // further scale bbox width and height
    ent->bbox.rect[0].w = w * scale;
    ent->bbox.rect[0].h = h * scale;

    // calculate x and y offset for centering
    ent->bbox.offsetX[0] = (w - ent->bbox.rect[0].w) / 2;
    ent->bbox.offsetY[0] = (h - ent->bbox.rect[0].h) / 2;

    // the second box is rotated 90 degrees (dimensions are flipped)
    ent->bbox.rect[1].w = ent->bbox.rect[0].h;
    ent->bbox.rect[1].h = ent->bbox.rect[0].w;
    ent->bbox.offsetX[1] = (w - ent->bbox.rect[1].w) / 2;
    ent->bbox.offsetY[1] = (h - ent->bbox.rect[1].h) / 2;
}

void updateBoundingBox(Entity *ent)
{
    if(ent == NULL || ent-> used == blnFalse)
    {
        return;
    }

    if(ent->rotation >= 0 && ent->rotation < 45)
    {
        ent->bbox.activeBox = 0;
    }
    else if(ent->rotation >= 135 && ent->rotation < 225)
    {
        ent->bbox.activeBox = 0;
    }
    else if(ent->rotation >= 315 && ent->rotation < 360)
    {
        ent->bbox.activeBox = 0;
    }
    else
    {
        ent->bbox.activeBox = 1;
    }

    ent->bbox.rect[ent->bbox.activeBox].x = ent->position.x + ent->bbox.offsetX[ent->bbox.activeBox];
    ent->bbox.rect[ent->bbox.activeBox].y = ent->position.y + ent->bbox.offsetY[ent->bbox.activeBox];
}

void drawBoundingBox(Entity *ent)
{
    if(ent == NULL || ent-> used == blnFalse)
    {
        return;
    }

    u8 activeBox = ent->bbox.activeBox;

    SDL_Rect rect;
    rect.x = ent->bbox.rect[activeBox].x - gCamera.position.x;
    rect.y = ent->bbox.rect[activeBox].y - gCamera.position.y;
    rect.w = ent->bbox.rect[activeBox].w;
    rect.h = ent->bbox.rect[activeBox].h;

    drawRect(&rect, &bboxColor, blnFalse);
}

void drawAllBoundingBoxes()
{
    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        if(EntityList[i].used == blnTrue && EntityList[i].collidable == blnTrue)
        {
            drawBoundingBox(&EntityList[i]);
        }
    }
}

bln collide(Entity *ent1, Entity *ent2)
{
    if(ent1 == NULL || ent1-> used == blnFalse || ent2 == NULL || ent2-> used == blnFalse)
    {
        return blnFalse;
    }

    SDL_Rect box1 = ent1->bbox.rect[ent1->bbox.activeBox];
    SDL_Rect box2 = ent2->bbox.rect[ent2->bbox.activeBox];

    if((box1.x+box1.w >= box2.x) && (box1.x <= box2.x+box2.w) && (box1.y+box1.h >= box2.y) && (box1.y <= box2.y+box2.h))
    {
        return blnTrue;
    }

    return blnFalse;
}

Entity* checkAllCollisions(Entity *src)
{
    if(src == NULL || src-> used == blnFalse)
    {
        return NULL;
    }

    for(u16 i = 0; i < MAX_ENTITIES; i++)
    {
        // don't check collisions with self or owner
        if(&EntityList[i] == src || &EntityList[i] == src->owner)
        {
            continue;
        }
        // check collisions if entity is in use and collidable
        if(EntityList[i].used == blnTrue && EntityList[i].collidable == blnTrue && collide(src, &EntityList[i]))
        {
            return &EntityList[i];
        }
    }

    return NULL;
}

