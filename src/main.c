// ###########################################################################
//          Title: Astral
//         Author: Mike Del Pozzo
//    Description: An open source 2D space game.
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

#include "graphics.h"
#include "sprite.h"
#include "input.h"
#include "entity.h"
#include "player.h"
#include "camera.h"
#include "text.h"
#include "map.h"
#include "gui.h"

void loop(); // main game loop

extern bln gQuit;
extern Entity *gPlayer;

Map *testMap = NULL;

int main(int argc, char * argv[])
{
    seedRandom();

    if(initGraphics("Astral v0.2.0"))
    {
        initInput();
        initEntityList();
        initMapList();

        testMap = loadMap("Test Map");
        gPlayer = spawnPlayer(2300, 1800);

        while(!gQuit)
        {
            loop();
        }

        gPlayer = NULL;
        testMap = NULL;
    }

    closeInput();
    closeCamera();
    clearMapList();
    clearEntityList();
    closeGraphics();
    SDL_Quit();

    return 0;
}

void loop()
{
    clearScreen();
    drawMap(testMap);
    updateInput();
    thinkAll();
    updateCamera();
    drawAll();
    displayEntityDebugInfo(gPlayer, 50, 50);
    nextFrame();
}

