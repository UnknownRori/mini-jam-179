#include <raylib.h>
#include <stdio.h>
#include "include/ui.h"
#include "include/assets.h"
#include "include/game.h"
#include "include/utils.h"


void DrawScore(i32 score, Assets *a)
{
    char buffer[1024] = {0};
    Vector2 center = {
        .x = GAME_WIDTH / 2.,
        .y = 0,
    };
    sprintf(buffer, "%d", score);
    Vector2 origin = MeasureTextEx(a->font, buffer, 8, 2);
    origin.y = 0;
    origin.x /= 2.;
    DrawTextPro(a->font, buffer, center, origin, 0, 8, 2, (Color) {116, 79, 70, 255});
}
void DrawHP(f32 current, f32 max, Assets *a)
{
    i32 hp = MIN(0, (current / max) * 5);
    // Draw Hearts
    Rectangle src = {
        .x = 48,
        .y = 240,
        .width = 16,
        .height = 16,
    };
    Rectangle dst = {
        .x = 336,
        .y = 200,
        .width = 16,
        .height = 16,
    };
    DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);

    // Draw Slot
    src.x = 0;
    src.y = 152;
    src.width = 48;
    src.height = 88;
    dst.x = 320;
    dst.y = 113;
    dst.width = src.width;
    dst.height = src.height;

    DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);

    // Draw HP slot
    src.x = 0;
    src.y = 240;
    src.width = 40;
    src.height = 16;
    for (int i = 0; i < hp; i++) {
        dst.x = 323;
        dst.y = 175 - (i * src.height - 4);
        dst.width = src.width;
        dst.height = src.height;
        DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);
    }
}
