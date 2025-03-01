#include <raylib.h>
#include <stdio.h>
#include "include/ui.h"
#include "include/assets.h"
#include "include/event.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/sprite.h"
#include "include/timer.h"
#include "include/utils.h"

float shake = 0;

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
    shake = MIN(0, shake - GetFrameTime());
    shake = MAX(shake, 4);

    EventType event = GetEvent();
    if (event == EVENT_HP_DECREASE) {
        shake += 1;
        PopEvent();
    }

    i32 hp = MIN(0, (current / max) * 5);
    // Draw Hearts
    Rectangle src = {
        .x = 48,
        .y = 240,
        .width = 16,
        .height = 16,
    };
    Rectangle dst = {
        .x = 336 + Shake(shake),
        .y = 200 + Shake(shake),
        .width = 16,
        .height = 16,
    };
    DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);

    // Draw Slot
    src.x = 0;
    src.y = 152;
    src.width = 48;
    src.height = 88;
    dst.x = 320 + Shake(shake);
    dst.y = 113 + Shake(shake);
    dst.width = src.width;
    dst.height = src.height;

    DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);

    // Draw HP slot
    src.x = 0;
    src.y = 240;
    src.width = 40;
    src.height = 16;
    for (int i = 0; i < hp; i++) {
        dst.x = 323 + Shake(shake);
        dst.y = 175 - (i * src.height - 4) + Shake(shake);
        dst.width = src.width;
        dst.height = src.height;
        DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);
    }
}

void InsertWarning(Vector2 pos)
{
    for (int i = 0; i < MAX_WARNING_INFO; i++) {
        WarningInfo *temp = &g.warning_info[i];
        if (temp->exist) continue;

        temp->position = pos;
        temp->many_blink = 4;
        temp->sprite.flipX = false;
        temp->sprite.rotation = 0;
        temp->sprite.scale = 1;
        temp->sprite.src.x = 48;
        temp->sprite.src.y = 224;
        temp->sprite.src.width = 16;
        temp->sprite.src.height = 16;
        temp->blink = TimerInit(0.8, true);
        temp->many_blink = 8;
        temp->exist = true;
        break;
    }
}

// WarningInfo should be an array
void UpdateWarning(WarningInfo *w)
{
    for (int i = 0; i < MAX_WARNING_INFO; i++) {
        WarningInfo *temp = &w[i];
        if (!temp->exist) continue;

        __LOG("%f, %d, %d", temp->blink.m_remaining, temp->many_blink, temp->blinking);
        TimerUpdate(&temp->blink);
        if (TimerCompleted(&temp->blink) && temp->blinking) {
            temp->many_blink -= 1;
            temp->blinking = false;
        } else if (TimerCompleted(&temp->blink) && !temp->blinking) {
            temp->blinking = true;
        }
        if (temp->many_blink < 0) temp->exist = false;
    }
}
// WarningInfo should be an array
void DrawWarning(WarningInfo *w, Assets *a)
{
    for (int i = 0; i < MAX_WARNING_INFO; i++) {
        WarningInfo *temp = &w[i];
        if (!temp->exist) continue;
        if (temp->blinking) {
            DrawSprite(a->atlas, temp->sprite, temp->position);
        }

    }
}
