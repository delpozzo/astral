// ###########################################################################
//          Title: Astral Player Functions
//         Author: Mike Del Pozzo
//    Description: Functions related to the player.
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

#include "player.h"
#include "input.h"
#include "camera.h"

void thinkPlayer(Entity *self);  // player's think function

extern bln gInput[MAX_INPUT_KEYS];
extern bln gQuit;
extern Camera gCamera;

Entity *gPlayer = NULL;

Entity* spawnPlayer(i32 x, i32 y)
{
    Entity *self = spawnEntity();
    if(self == NULL)
    {
        printf("[ERROR] [PLAYER] Unable to spawn player\n");
        gQuit = blnTrue;
        return NULL;
    }

    strncpy(self->name, "Player", MAX_NAME_LENGTH);
    self->type = typePlayer;
    self->spriteSheet = loadSprite("sprites/ship1.png", 545, 675);
    self->frame = 0;
    self->position.x = x;
    self->position.y = y;
    self->rotation = 0.0;
    self->scale = 0.25;
    self->accelSpeed = 0.03;
    self->turnSpeed = 1.5;
    self->maxSpeed = 5.0;
    self->think = thinkPlayer;

    gCamera.focus = self;

    return self;
}

void thinkPlayer(Entity *self)
{
    // turn left
    if(gInput[inputLeft] == blnTrue)
    {
        self->rotation -= self->turnSpeed;
    }

    // turn right
    if(gInput[inputRight] == blnTrue)
    {
        self->rotation += self->turnSpeed;
    }

    // engage engine
    if(gInput[inputUp] == blnTrue)
    {
        f32 angle = degToRad(self->rotation) + QUARTER_TURN;
        self->frame = 1;
        self->velocity.x -= cos(angle) * self->accelSpeed;
        self->velocity.y -= sin(angle) * self->accelSpeed;
    }
    else
    {
        self->frame = 0;
    }

    // throttle x velocity
    if(self->velocity.x > self->maxSpeed)
    {
        self->velocity.x = self->maxSpeed;
    }
    else if(self->velocity.x < -self->maxSpeed)
    {
        self->velocity.x = -self->maxSpeed;
    }

    // throttle y velocity
    if(self->velocity.y > self->maxSpeed)
    {
        self->velocity.y = self->maxSpeed;
    }
    else if(self->velocity.y < -self->maxSpeed)
    {
        self->velocity.y = -self->maxSpeed;
    }

    // update position
    self->position.x += self->velocity.x;
    self->position.y += self->velocity.y;

    // constrain to map
    Coord limit;
    limit.x = gCamera.bufferW - self->spriteSheet->frameWidth * self->scale;
    limit.y = gCamera.bufferH - self->spriteSheet->frameHeight * self->scale;
    
    if(self->position.x < 0)
    {
        self->position.x = 0;
        self->velocity.x = 0;
    }
    else if(self->position.x > limit.x)
    {
        self->position.x = limit.x;
        self->velocity.x = 0;
    }

    if(self->position.y < 0)
    {
        self->position.y = 0;
        self->velocity.y = 0;
    }
    else if(self->position.y > limit.y)
    {
        self->position.y = limit.y;
        self->velocity.y = 0;
    }
}

