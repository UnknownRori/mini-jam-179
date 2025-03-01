#include "include/sprite.h"
#include <raylib.h>

void DrawSprite(Texture2D atlas, Sprite spr, Vector2 pos)
{
    Rectangle dst = {
        .x = pos.x,
        .y = pos.y,
        .width = spr.src.width * spr.scale,
        .height = spr.src.height * spr.scale,
    };
    Rectangle src = spr.src;
    if (spr.flipX) {
        src.width = -src.width;
    }
    Vector2 origin = {src.width / 2., src.height / 2.};
    float rotation = spr.rotation;
    DrawTexturePro(atlas, src, dst, origin, rotation, WHITE);
}
