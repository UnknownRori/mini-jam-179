#pragma once

#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
#include <stdbool.h>

typedef struct CollisionBox {
    Vector2 pos;
    Rectangle box;
    bool collided;
} CollisionBox;

void DrawCollisionBox(CollisionBox);
bool CheckCollisionBox(CollisionBox, CollisionBox);

#endif
