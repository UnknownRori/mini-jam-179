#pragma once

#ifndef PARALLAX_H
#define PARALLAX_H

#include <raylib.h>
#include "types.h"

typedef struct ParallaxLayer {
    Texture2D texture;
    f32 speedX;
    f32 speedY;
    Vector2 position;
    Vector2 offset;
} ParallaxLayer;

void DrawParallaxLayer(ParallaxLayer *layer, Vector2 cameraPos);

#endif
