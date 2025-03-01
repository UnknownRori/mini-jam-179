#pragma once

#include "collision.h"
#ifndef WALL_H
#define WALL_H

#include <raylib.h>
#include <stdbool.h>
#include "types.h"

typedef struct Wall
{
    f32 positionX;
    f32 depth;
} Wall;

bool WallIntersectCollisionBox(Wall*, CollisionBox*);

#endif
