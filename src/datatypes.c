// ###########################################################################
//          Title: Astral Data Types
//         Author: Mike Del Pozzo
//    Description: Astral data type mappings and declarations
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

#include "datatypes.h"
#include <time.h>

void seedRandom()
{
    time_t t;
    srand((unsigned) time(&t));
}

