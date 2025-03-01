#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdbool.h>
#include "sprite.h"
#include "assets.h"
#include "collision.h"

typedef struct Player {
    Vector2 position;
    Sprite core;
    Sprite turret;

    CollisionBox collision;

    Vector2 vel;
    f32 speed;
    f32 hp;
    f32 max_hp;
    f32 power;
    bool collided;
} Player;

void PlayerInit(Player*);
void DrawPlayer(Player*, Assets *a, Vector2);
//
// @params  Player* - Player data
// @params  Vector2 - mouse position
void UpdatePlayer(Player*, Vector2);

#endif

