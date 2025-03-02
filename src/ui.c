#include <raylib.h>
#include <stdio.h>
#include "include/ui.h"
#include "include/assets.h"
#include "include/event.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/sprite.h"
#include "include/timer.h"
#include "include/types.h"
#include "include/utils.h"


void DrawHPBar(i32 current, i32 max, Vector2 pos, Vector2 offset)
{
    const i32 width = 24;
    const i32 height = 4;
    DrawRectangle(pos.x - width / 2., pos.y, width, height, (Color) {116, 79, 70, 255});
}

void DrawScore(i32 score, Assets *a)
{
    char buffer[32] = {0};
    Vector2 center = {
        .x = GAME_WIDTH / 2.,
        .y = 8,
    };
    sprintf(buffer, "%d", score);
    Vector2 origin = MeasureTextEx(a->font, buffer, 8, 2);
    origin.y = 0;
    origin.x /= 2.;
    DrawTextPro(a->font, buffer, center, origin, 0, 8, 2, (Color) {178, 156, 151, 255});
}
void DrawHP(f32 current, f32 max, Assets *a)
{
    static float shake = 0;
    static i32 blink = 0;
    static bool should_blink = false;
    static bool should_heart_blink = false;
    static Timer heart = {
        .m_lifetime = 0.5,
        .m_repeating = true,
    };
    shake = MIN(0, shake - GetFrameTime());
    blink = MIN(0, blink - 1);
    shake = MAX(shake, 4);

    if (blink == 0) should_blink = false;
    if (blink % 4) should_blink = !should_blink;
    if (current <= 20) {
        TimerUpdate(&heart);
        if (TimerCompleted(&heart)) should_heart_blink = !should_heart_blink;
    }

    EventType event = GetEvent();
    if (event == EVENT_HP_DECREASE) {
        shake = 2;
        blink = 8;
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
    if (!should_heart_blink || !(current <= 20)) {
        DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);
    }

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
        if (should_blink && i == (hp - 1)) {
            break;
        }
        DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);
    }

    if (current >= max) {
        DrawTextPro(a->font, "MAX!", (Vector2) {328, 100}, VECTOR_ZERO, 0, 8, 2, (Color) {178, 156, 151, 255});
    } else if (current <= 20) {
        DrawTextPro(a->font, "LOW!", (Vector2) {328, 100}, VECTOR_ZERO, 0, 8, 2, (Color) {178, 156, 151, 255});
    }
}

void DrawEnergy(f32 current, f32 max, Assets *a)
{
    static float shake = 0;
    static Timer battery = {
        .m_lifetime = 0.5,
        .m_repeating = true,
    };
    static i32 blink = 0;
    static bool should_blink = false;
    static bool should_battery_blink = false;
    shake = MIN(0, shake - GetFrameTime());
    blink = MIN(0, blink - 1);
    shake = MAX(shake, 4);

    if (blink == 0) should_blink = false;
    if (blink % 4) should_blink = !should_blink;
    if (current <= 20) {
        TimerUpdate(&battery);
        if (TimerCompleted(&battery)) should_battery_blink = !should_battery_blink;
    }

    EventType event = GetEvent();
    if (event == EVENT_ENERGY_DECREASE) {
        blink = 8;
        shake = 2;
        PopEvent();
    }

    i32 hp = MIN(0, (current / max) * 5);
    // Draw Battery
    Rectangle src = {
        .x = 64,
        .y = 240,
        .width = 16,
        .height = 16,
    };
    Rectangle dst = {
        .x = 35 + Shake(shake),
        .y = 200 + Shake(shake),
        .width = 16,
        .height = 16,
    };

    if (!should_battery_blink || !(current <= 20)) {
        DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);
    }

    // Draw Slot
    src.x = 0;
    src.y = 152;
    src.width = 48;
    src.height = 88;
    dst.x = 20;
    dst.y = 113;
    dst.width = src.width;
    dst.height = src.height;

    DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);

    src.x = 0;
    src.y = 240;
    src.width = 40;
    src.height = 16;
    for (int i = 0; i < hp; i++) {
        dst.x = 23;
        dst.y = 175 - (i * src.height - 4);
        dst.width = src.width;
        dst.height = src.height;
        if (should_blink && i == (hp - 1)) {
            break;
        }
        DrawTexturePro(a->atlas, src, dst, VECTOR_ZERO, 0, WHITE);
    }

    if (current >= max) {
        DrawTextPro(a->font, "MAX!", (Vector2) {24, 100}, VECTOR_ZERO, 0, 8, 2, (Color) {178, 156, 151, 255});
    } else if (current <= 20) {
        DrawTextPro(a->font, "LOW!", (Vector2) {24, 100}, VECTOR_ZERO, 0, 8, 2, (Color) {178, 156, 151, 255});
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
        temp->blink = TimerInit(0.2, true);
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

void UIText(const char *text, Vector2 pos, i32 font_size, Assets *a)
{
    const i32 font_space = 2;
    Vector2 measure = MeasureTextEx(a->font, text, font_size, font_space);
    Rectangle collision = (Rectangle) {
        .x = pos.x,
        .y = pos.y,
        .width = measure.x,
        .height = measure.y,
    };

    collision.x -= 2;
    collision.y -= 2;
    collision.width += 4;
    collision.height += 4;

    DrawRectangleRec(collision, (Color) {62, 32, 24, 255});
    DrawTextPro(a->font, text, pos, VECTOR_ZERO, 0, font_size, font_space, (Color) {178, 156, 151, 255});
}


bool UITextButton(const char *text, Vector2 pos, Vector2 mouse, Assets *a)
{
    const i32 font_size = 8;
    const i32 font_space = 2;
    Vector2 measure = MeasureTextEx(a->font, text, font_size, font_space);
    Rectangle collision = (Rectangle) {
        .x = pos.x,
        .y = pos.y,
        .width = measure.x,
        .height = measure.y,
    };
    bool is_hovered = CheckCollisionPointRec(mouse, collision);

    collision.x -= 2;
    collision.y -= 2;
    collision.width += 4;
    collision.height += 4;

    DrawRectangleRec(collision, (Color) {62, 32, 24, 255});

    if (is_hovered) {
        DrawTextPro(a->font, text, pos, VECTOR_ZERO, 0, font_size, font_space, (Color) {178, 156, 151, 255});
        return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }

    DrawTextPro(a->font, text, pos, VECTOR_ZERO, 0, font_size, font_space, (Color) {116, 79, 70, 255});

    return false;
}
