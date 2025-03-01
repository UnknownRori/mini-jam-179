#pragma once

#include "sprite.h"
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <raylib.h>
#include <stdbool.h>
#include "types.h"
#include "assets.h"
#include "collision.h"

#define OBSTACLE_WIDTH      8
#define OBSTACLE_HEIGHT     8

#define OBSTACLE_FLAG_LEFT  0x1
#define OBSTACLE_FLAG_RIGHT 0x0

typedef struct Obstacle {
    // This just how many block it has
    // At the end it will insert end block
    i32 length;
    Vector2 position;
    CollisionBox collision;

    Sprite body;
    Sprite end;

    // currently storing left or right
    i32 flags;
    bool exist;
} Obstacle;

// @params  Vector2 - pos
// @params  i32     - length
// @params  i32     - flags
void InsertObstacle(Vector2, i32, i32);
// Require obstacle to be an array and it will despawn if it outside the camera
void SpawnObstacle(Camera2D *, i32 threshold);
void DespawnObstacle(Obstacle*, Camera2D *);
// Require obstacle to be an array and it will despawn if it outside the camera
void DrawObstacle(Obstacle*, Assets *);

void CheckCollisionObstacle(Obstacle*, CollisionBox*);

#endif
