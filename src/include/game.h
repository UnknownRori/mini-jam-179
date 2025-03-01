#pragma once

#include "bullet.h"
#include "enemy.h"
#include "obstacle.h"
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
#define SCREEN_WIDTH            1366
#define SCREEN_HEIGHT           768
#define GAME_WIDTH              384
#define GAME_HEIGHT             216
#define WORLD_WIDTH             384
#define WORLD_HEIGHT            216
#define FULLSCREEN              0

#define PLAYER_SPEED            300
#define PLAYER_BULLET_SPEED     150
#define ENEMY_SPEED             15
#define ENEMY_BULLET_SPEED      100
#define GRAVITY                 -200

#define MAX_ENEMY               10
#define MAX_OBSTACLE            4
#define MAX_BULLET              200


typedef struct Game {
    Player          player;
    EnemyBot        enemy[MAX_ENEMY];
    Bullet          bullet[MAX_BULLET];
    Obstacle        obstacle[MAX_OBSTACLE];

    Camera2D        camera;
    f32 shakeness;

    ParallaxLayer   layer;
    Wall            wall_left;
    Wall            wall_right;

    bool            debug_collision;
} Game;

extern Game g;
extern Assets a;

void GameLoop(void);
void GameInit(void);
void GameUnload(void);
bool ShouldGameQuit(void);

#endif
