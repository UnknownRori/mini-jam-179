#include <math.h>
#include "include/parallax.h"

void DrawParallaxLayer(ParallaxLayer *layer, Vector2 cameraPos)
{
    Vector2 target_pos = {
        cameraPos.x * layer->speedX,
        cameraPos.y * layer->speedY,
    };

    f32 offsetX = fmodf(layer->position.x + layer->offset.x, layer->texture.width);
    f32 offsetY = fmodf(layer->position.y + layer->offset.y, layer->texture.height);

    i32 width = layer->texture.width;
    i32 height = layer->texture.height;

    for (int x = -width; x < GetScreenWidth() + width; x += width) {
        for (int y = -height; y < GetScreenHeight() + height; y += height) {
            DrawTexture(layer->texture, x - (int)offsetX, y - (int)offsetY, WHITE);
        }
    }
}
