#pragma once

#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdbool.h>

#include "types.h"
#include "assets.h"
#include "player.h"

/*#define DEBUG           1*/
#define SCREEN_WIDTH    1366
#define SCREEN_HEIGHT   768
#define GAME_WIDTH      384
#define GAME_HEIGHT     216
#define WORLD_WIDTH     384
#define WORLD_HEIGHT    216
#define FULLSCREEN      0


typedef struct Game {
    Player player;
    Camera2D camera;

    bool debug_collision;
} Game;

extern Game g;
extern Assets a;

void GameLoop(void);
void GameInit(void);
void GameUnload(void);
bool ShouldGameQuit(void);

#endif
