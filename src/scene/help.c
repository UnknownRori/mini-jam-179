#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/logger.h"
#include "../include/utils.h"
#include "../include/cursor.h"
#include "../include/ui.h"


#include "help.h"

static const Sprite HP_SPRITE = (Sprite) {
    .flipX = false,
    .rotation = 0,
    .scale = 1,
    .src = (Rectangle) {
        .x = 72,
        .y = 224,
        .width = 8,
        .height = 8,
    },
};

static const Sprite ENERGY_SPRITE = (Sprite) {
    .flipX = false,
    .rotation = 0,
    .scale = 1.,
    .src = (Rectangle) {
        .x = 72,
        .y = 232,
        .width = 8,
        .height = 8,
    },
};

const Sprite CURSOR_SPRITE = (Sprite) {
    .rotation = 0,
    .scale = 1,
    .flipX = 0,
    .src = (Rectangle) {
        .x = 64,
        .y = 224,
        .width = 8,
        .height = 8,
    }
};

const Sprite ENEMY_ROBOT_SPRITE = (Sprite){
    .flipX = 0,
    .rotation = 0,
    .scale = 1.,
    .src = (Rectangle) {
        .x = 0,
        .y = 16,
        .width = 16,
        .height = 16,
    }
};

const Sprite PLAYER_SPRITE = (Sprite){
        .flipX = false,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 16,
            .y = 0,
            .width = 16,
            .height = 16,
        },
    };

void HelpInit()
{

}

void HelpUpdate()
{

}

void HelpRender()
{
    Vector2 mouse_position = GetMousePositionScaled();
    Vector2 pos_title = (Vector2) {
        .x = 160,
        .y = 10,
    };
    BeginTextureMode(a.buffer);
        ClearBackground((Color){62, 32, 24, 255});

        DrawTextPro(a.font, "Help", pos_title, VECTOR_ZERO, 0, 12, 2, (Color) {176, 156, 151, 255});
        if (UITextButton("Back", (Vector2) {5, 10}, mouse_position, &a)) SceneChange(1);
        DrawSprite(a.atlas, CURSOR_SPRITE, (Vector2) {30, 40});
        UIText("Your cursor", (Vector2) {50, 30}, 8, &a);
        UIText("Left click to shoot", (Vector2) {50, 40}, 8, &a);
        UIText("Shoot cause go opposite direction", (Vector2) {50, 50}, 8, &a);
        UIText("Your job is to go up", (Vector2) {50, 60}, 8, &a);

        DrawSprite(a.atlas, PLAYER_SPRITE, (Vector2) {30, 90});
        UIText("This is you", (Vector2) {50, 80}, 8, &a);
        UIText("Avoid bullet & Laser", (Vector2) {50, 90}, 8, &a);

        DrawSprite(a.atlas, HP_SPRITE, (Vector2) {30, 120});
        UIText("HP item", (Vector2) {50, 110}, 8, &a);
        UIText("Fill up your HP", (Vector2) {50, 120}, 8, &a);

        DrawSprite(a.atlas, ENERGY_SPRITE, (Vector2) {30, 150});
        UIText("Energy item", (Vector2) {50, 140}, 8, &a);
        UIText("Fill up your Energy", (Vector2) {50, 150}, 8, &a);
        UIText("Shot uses energy", (Vector2) {50, 160}, 8, &a);

        DrawSprite(a.atlas, ENEMY_ROBOT_SPRITE, (Vector2) {30, 190});
        UIText("Enemy", (Vector2) {50, 180}, 8, &a);
        UIText("Avoid getting shot", (Vector2) {50, 190}, 8, &a);
        DrawCursor(&a, mouse_position);
    EndTextureMode();
}

void HelpDeinit()
{

}

Scene GetSceneHelp()
{
    return (Scene) {
        .init = HelpInit,
        .deinit = HelpDeinit,
        .update = HelpUpdate,
        .render = HelpRender,
    };
}
