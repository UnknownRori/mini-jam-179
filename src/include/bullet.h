#pragma once

#include "assets.h"
#include <stdbool.h>
#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include "sprite.h"
#include "types.h"
#include "collision.h"

#define PLAYER_BULLET_GROUP 0
#define ENEMY_BULLET_GROUP 1

typedef struct Bullet {
    Sprite sprite;

    Vector2 position;
    Vector2 velocity;
    CollisionBox collision;

    i32 group;
    bool exist;
} Bullet;

void SpawnPlayerBullet(Vector2 vel, Vector2 position);
void SpawnEnemyBullet(Vector2 vel, Vector2 position);

void InsertBullet(Bullet);
// Array of enemy it will check if it out of bound
void DrawBullet(Bullet *, Assets *);
void UpdateBullet(Bullet *arr);
// Array of enemy it will check if it out of bound
void DespawnBullet(Bullet *b, Camera2D *cam);

#endif
