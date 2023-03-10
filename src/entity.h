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

#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"

#define MAX_NAME_LENGTH 32

enum entityTypes
{
    typeNone = 0,
    typePlayer = 1,
    typeNPC = 2,
    typePlanet = 3,
    typeProjectile = 4
};

typedef struct BBOX_S
{
    SDL_Rect rect[2]; // bounding box rects
    i32 offsetX[2]; // x offset from entity position
    i32 offsetY[2]; // y offset from entity position
    u8 activeBox; // 0 for normal, 1 for rotated
} Bbox;

typedef struct ENTITY_S
{
    char name[MAX_NAME_LENGTH]; // name of entity
    u8 type; // entity type (see entityTypes enum)
    Sprite *spriteSheet; // pointer to entity's sprite sheet
    u16 frame; // current frame of sprite sheet to render
    Coord position; // 2D position of entity (x,y)
    Coord velocity; // 2D speed in direction
    Bbox bbox; // bounding box for collision detection
    bln collidable; // determines if collision checking is performed for entity
    f32 rotation; // rotation of entity
    f32 scale; // scale sprite (default 1.0)
    f32 accelSpeed; // acceleration speed
    f32 turnSpeed; // turn speed
    f32 maxSpeed; // maximum speed
    bln used; // in-use flag for position in array
    struct ENTITY_S *owner; // owner of entity
    void(*think)(struct ENTITY_S *self); // think function that will be called in the next thinkAll() iteration
} Entity;

void initEntityList(); // initialize list of entities
Entity* spawnEntity(); // finds first vacant spot in the entity list and returns a pointer
void freeEntity(Entity *ent); // delete specified entitiy
void clearEntityList(); // delete all entities
void drawEntity(Entity *ent); // draw sprite for given entity
void drawAll(); // calls drawEntity() for all active entities in the EntityList[]
void thinkAll(); // calls think function for all active entities with a think function
void createBoundingBox(Entity *ent, f32 scale); // calculates bounding box for entity using sprite frame size and scale
void updateBoundingBox(Entity *ent); // updates bounding box position for specified entity
void drawBoundingBox(Entity *ent); // draw bounding box for specified entity (mostly for debugging)
void drawAllBoundingBoxes(); // draw bounding boxes for all entities (mostly for debugging)
bln collide(Entity *ent1, Entity *ent2); // returns true if the two entities are colliding
Entity* checkAllCollisions(Entity *src); // returns first entity to collide with the src entity

#endif

