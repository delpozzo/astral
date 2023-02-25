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

#include "map.h"
#include "camera.h"
#include "planet.h"

#define MAX_MAPS 16 // maximum number of maps that can be pre-loaded at a time

void drawMapLayer(Map *map, u16 layer); // private function called by drawMap()

extern bln gQuit;
extern Camera gCamera;

Map MapList[MAX_MAPS];

u16 mapsLoaded = 0;

void initMapList()
{
    for(u16 i = 0; i < MAX_MAPS; i++)
    {
        closeMap(&MapList[i]);
    }

    printf("[INFO] [MAP] Map list initialized (%i slots available)\n", MAX_MAPS);
}

void clearMapList()
{
    for(u16 i = 0; i < MAX_MAPS; i++)
    {
        closeMap(&MapList[i]);
    }

    printf("[INFO] [MAP] Map list cleared\n");
}

Map* loadMap(char *filename) // WORK IN PROGRESS
{
    for(u16 i = 0; i < MAX_MAPS; i++)
    {
        if(strncmp(filename, MapList[i].filename, MAX_FILE_LENGTH) == 0)
        {
            return &MapList[i];
        }
    }

    for(u16 i = 0; i < MAX_MAPS; i++) // WORK IN PROGRESS
    {
        if(MapList[i].used == blnFalse)
        {
            // loads demo map only for now (not from .map file)
            MapList[i].bg[0].sprite = loadSprite("sprites/bg3.png", 512, 512);
            MapList[i].bg[0].frame = 0;
            MapList[i].bg[0].scrollSpeed = 0.8;

            MapList[i].bg[1].sprite = loadSprite("sprites/stars2.png", 512, 512);
            MapList[i].bg[1].frame = 0;
            MapList[i].bg[1].scrollSpeed = 0.9;

            MapList[i].width = 5000;
            MapList[i].height = 5000;

            strncpy(MapList[i].filename, filename, MAX_FILE_LENGTH);
            MapList[i].used = blnTrue;

            spawnPlanet("Earth", 2000, 2000);
            spawnPlanet("Moon", 2400, 1600);

            mapsLoaded++;
            printf("[INFO] [MAP] Loaded map: %s\n", MapList[i].filename);
            printf("[INFO] [MAP] Maps loaded: %i/%i\n", mapsLoaded, MAX_MAPS);

            initCamera(MapList[i].width, MapList[i].height);

            return &MapList[i];
        }
    }

    printf("[ERROR] [MAP] Map limit reached, failed to load map\n");
    gQuit = blnTrue;
    return NULL;
}

void closeMap(Map *map)
{
    if(map == NULL)
    {
        return;
    }

    if(map->used == blnTrue)
    {
        mapsLoaded--;
        printf("[INFO] [MAP] Closing map: %s\n", map->filename);
            printf("[INFO] [MAP] Maps loaded: %i/%i\n", mapsLoaded, MAX_MAPS);
    }

    for(u16 i = 0; i < MAX_MAP_LAYERS; i++)
    {
        map->bg[i].sprite = NULL;
        map->bg[i].frame = 0;
        map->bg[i].scrollSpeed = 0;
    }

    strncpy(map->filename, "", MAX_FILE_LENGTH);
    map->width = 0;
    map->height = 0;
    map->used = blnFalse;
}

void drawMap(Map *map)
{
    if(map == NULL)
    {
        printf("[ERROR] [MAP] Tried to draw a map that was null\n");
        gQuit = blnTrue;
        return;
    }
    else if(map->used == blnFalse)
    {
        printf("[ERROR] [MAP] Tried to draw a map that wasn't initialized\n");
        gQuit = blnTrue;
        return;
    }

    for(u16 i = 0; i < MAX_MAP_LAYERS; i++)
    {
        if(map->bg[i].sprite == NULL)
        {
            continue;
        }

        drawMapLayer(map, i);
    }
}

void drawMapLayer(Map *map, u16 layer)
{
    u16 frameWidth = map->bg[layer].sprite->frameWidth;
    u16 frameHeight = map->bg[layer].sprite->frameHeight;

    u32 xTiles = 1 + map->width / frameWidth;
    u32 yTiles = 1 + map->height / frameHeight;

    Coord offset;
    offset.x = gCamera.position.x * map->bg[layer].scrollSpeed;
    offset.y = gCamera.position.y * map->bg[layer].scrollSpeed;

    // TODO: Optimize these loops (trim start and end for x & y)
    for(u32 y = 0; y < yTiles; y++)
    {
        for(u32 x = 0; x < xTiles; x++)
        {
            drawSprite(map->bg[layer].sprite, x * frameWidth - offset.x, 
            y * frameHeight - offset.y, map->bg[layer].frame, 0, 1.0, SDL_FLIP_NONE);
        }
    }
}

