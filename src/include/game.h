#pragma once

#include "enemy.h"
#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdbool.h>

#include "types.h"
#include "wall.h"
#include "assets.h"
#include "player.h"
#include "parallax.h"

/*#define DEBUG           1*/
#define SCREEN_WIDTH    1366
#define SCREEN_HEIGHT   768
#define GAME_WIDTH      384
#define GAME_HEIGHT     216
#define WORLD_WIDTH     384
#define WORLD_HEIGHT    216
#define FULLSCREEN      0

#define PLAYER_SPEED    300
#define GRAVITY         -200

#define MAX_ENEMY       10


typedef struct Game {
    Player player;
    EnemyBot enemy[MAX_ENEMY];

    Camera2D camera;

    ParallaxLayer layer;
    Wall wall_left;
    Wall wall_right;

    bool debug_collision;
} Game;

extern Game g;
extern Assets a;

void GameLoop(void);
void GameInit(void);
void GameUnload(void);
bool ShouldGameQuit(void);

#endif
