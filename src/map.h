// ###########################################################################
//          Title: Astral Map System
//         Author: Mike Del Pozzo
//    Description: Handles loading and drawing of maps.
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

#ifndef MAP_H
#define MAP_H

#include "sprite.h"

#define MAX_MAP_LAYERS 3 // max number of bg layers a map can have

typedef struct MAPLAYER_S
{
    Sprite *sprite; // pointer to sprite
    u16 frame; // current frame of sprite sheet to render
    f32 scrollSpeed; // scroll speed of layer (parallax)
} MapLayer;

typedef struct MAP_S
{
    MapLayer bg[MAX_MAP_LAYERS]; // array of background images
    char filename[MAX_FILE_LENGTH]; // path to .map file
    i32 width; // width of map
    i32 height; // height of map
    bln used; // in-use flag for position in array
} Map;

void initMapList();
void clearMapList();
Map* loadMap(char *filename);
void closeMap(Map *map);
void drawMap(Map *map);

#endif

