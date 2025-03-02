#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include <stdbool.h>
#include "collision.h"
#include "sprite.h"
#include "types.h"
#include "assets.h"
#include "player.h"
#include "timer.h"

typedef struct EnemyBot {
    Sprite sprite;
    Vector2 position;
    Vector2 vel;
    CollisionBox collision;

    f32 hp;
    f32 max_hp;

    Timer shot_cooldown;

    bool exists;
    bool collided;
} EnemyBot;

void SpawnEnemy(Camera2D * cam, int threshold);
void InsertEnemy(Vector2 pos);
// Array of enemy it will check if it out of bound
void DrawEnemy(EnemyBot *, Assets *);
void UpdateEnemy(EnemyBot *arr, Player *p);
// Array of enemy it will check if it out of bound
void DespawnEnemy(EnemyBot *, Camera2D *);

#endif
