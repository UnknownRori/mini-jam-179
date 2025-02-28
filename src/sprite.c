#include "include/sprite.h"

void DrawSprite(Texture2D atlas, Sprite spr, Vector2 pos)
{
    Rectangle dst = {
        .x = pos.x,
        .y = pos.y,
        .width = spr.src.width * spr.scale,
        .height = spr.src.height * spr.scale,
    };
    Rectangle src = spr.src;
    Vector2 origin = {src.width / 2., src.height / 2.};
    float rotation = spr.rotation;
    DrawTexturePro(atlas, src, dst, origin, rotation, WHITE);
}
