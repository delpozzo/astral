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

#ifndef GUI_H
#define GUI_H

#include "entity.h"

void initGUI();
void closeGUI();
void displayEntityDebugInfo(Entity *ent, i32 x, i32 y);

#endif

