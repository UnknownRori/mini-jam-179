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
void AnimatedSpriteDraw(Texture2D atlas, AnimatedSprite *spr, Vector2 pos)
{
    if (spr->frameDelay < 0) {
        spr->frameDelay = spr->defaultFrameDelay;
        spr->frame += 1;
    }
    spr->frameDelay -= GetFrameTime();

    if (spr->frame >= spr->maxFrame) spr->frame = 0;
    Rectangle src = {
        .x = spr->src.x + spr->src.width * spr->frame,
        .y = spr->src.y,
        .width = spr->flipX ? -spr->src.width : spr->src.width,
        .height = spr->src.height,
    };
    Rectangle dst = {
        .x = pos.x,
        .y = pos.y,
        .width = src.width * spr->scale,
        .height = src.height * spr->scale,
    };
    Vector2 origin = {0};
    float rotation = spr->rotation;
    DrawTexturePro(atlas, src, dst, origin, rotation, WHITE);
}
