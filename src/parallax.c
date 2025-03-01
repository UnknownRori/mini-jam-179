#include "include/parallax.h"

#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include <assert.h>

#include "include/game.h"
#include "include/logger.h"

void DrawParallaxLayer(ParallaxLayer *layer, Vector2 cameraPos)
{
    assert(layer != NULL);
    Vector2 offset = { cameraPos.x * layer->speedX + layer->offset.x, cameraPos.y * layer->speedY  + layer->offset.y };

    f32 width = layer->texture.width;
    f32 height = layer->texture.height;

    for (int x = -2; x < 2; x++) {
        for (int y = -2 ; y < 2; y++) {
            f32 offsetX = (x * width) - fmodf(offset.x, width);
            f32 offsetY = (y * height) - fmodf(offset.y, height);
            DrawTexture(layer->texture, offsetX, offsetY, WHITE);
        }
    }
}
