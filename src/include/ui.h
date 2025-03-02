#pragma once

#ifndef UI_H
#define UI_H

#include <raylib.h>
#include <stdbool.h>
#include "timer.h"
#include "types.h"
#include "sprite.h"
#include "assets.h"

typedef struct WarningInfo {
    Vector2 position;
    Sprite sprite;

    Timer blink;
    bool blinking;
    i32 many_blink;

    bool exist;
} WarningInfo;

void DrawHPBar(i32, i32, Vector2, Vector2);

void DrawScore(i32, Assets *);
void DrawHP(f32, f32, Assets *);
void DrawEnergy(f32, f32, Assets *);

void InsertWarning(Vector2);

// WarningInfo should be an array
void UpdateWarning(WarningInfo*);
// WarningInfo should be an array
void DrawWarning(WarningInfo*, Assets *);

void UIText(const char *text, Vector2 pos, i32 font_size, Assets *a);
bool UITextButton(const char *text, Vector2 pos, Vector2 mouse, Assets *a);

#endif
