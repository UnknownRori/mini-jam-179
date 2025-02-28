#include "include/cursor.h"
#include "include/utils.h"
#include "include/logger.h"
#include "include/sprite.h"
#include <raylib.h>

void DrawCursor(Assets *a, Vector2 pos)
{
    DrawSprite(a->atlas, (Sprite) {
        .rotation = 0,
        .scale = 1,
        .flipX = 0,
        .src = (Rectangle) {
            .x = 64,
            .y = 224,
            .width = 8,
            .height = 8,
        }
    }, pos);
}
