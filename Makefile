# ###########################################################################
#          Title: Astral Makefile
#         Author: Mike Del Pozzo
#    Description: The gcc Makefile for Astral.
#                 Note: Requires sdl2, sdl2_image, and sdl2_ttf.
#        Version: 0.2.0
#           Date: 24 Feb 2023
#        License: GPLv3 (see LICENSE)
#
#    Astral Copyright (C) 2023 Mike Del Pozzo
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    any later version.
# ###########################################################################

CC = gcc
VPATH=./src
OBJ = main.o datatypes.o graphics.o sprite.o text.o gui.o input.o map.o entity.o camera.o player.o planet.o
SDL_CFLAGS = `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
LFLAGS = -g -lm -o astral
CFLAGS = -std=c11 -pedantic -g -Wall

all: $(OBJ)
	gcc $(OBJ) $(LFLAGS) $(SDL_LDFLAGS)

clean:
	rm *.o astral

main.o: main.c
datatypes.o: datatypes.h datatypes.c
graphics.o: graphics.h graphics.c
sprite.o: sprite.h sprite.c
text.o: text.h text.c
gui.o: gui.h gui.c
input.o: input.h input.c
map.o: map.h map.c
entity.o: entity.h entity.c
camera.o: camera.h camera.c
player.o: player.h player.c
planet.o: planet.h planet.c

.c.o:
	gcc $(CFLAGS) $(SDL_CFLAGS) -c $<

