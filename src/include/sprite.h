#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include "types.h"

typedef struct Sprite {
    Rectangle src;
    f32 scale;
    f32 rotation;

    bool flipX;
} Sprite;

// @params  Texture2D - atlas
// @params  Sprite - sprite data
// @params  Vector2 - position
void DrawSprite(Texture2D, Sprite, Vector2);

#endif
