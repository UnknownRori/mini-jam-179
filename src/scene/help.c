#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/logger.h"
#include "../include/global_sprites.h"
#include "../include/utils.h"
#include "../include/cursor.h"
#include "../include/ui.h"


#include "help.h"

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
        if (UITextButton("Back", (Vector2) {330, 10}, mouse_position, &a)) SceneChange(1);
        DrawSprite(a.atlas, CURSOR_SPRITE, (Vector2) {30, 50});
        UIText("Your cursor", (Vector2) {50, 40}, 8, &a);
        UIText("Left click to shoot", (Vector2) {50, 40}, 8, &a);
        UIText("There is recoil mechanic", (Vector2) {50, 50}, 8, &a);
        UIText("Your job is to go up", (Vector2) {50, 60}, 8, &a);

        DrawSprite(a.atlas, PLAYER_SPRITE, (Vector2) {30, 90});
        UIText("This is you", (Vector2) {50, 80}, 8, &a);
        UIText("Avoid bullet & Laser", (Vector2) {50, 90}, 8, &a);

        DrawSprite(a.atlas, HP_ITEM_SPRITE, (Vector2) {30, 120});
        UIText("HP item", (Vector2) {50, 110}, 8, &a);
        UIText("Fill up your HP", (Vector2) {50, 120}, 8, &a);

        DrawSprite(a.atlas, ENERGY_ITEM_SPRITE, (Vector2) {30, 150});
        UIText("Energy item", (Vector2) {50, 140}, 8, &a);
        UIText("Fill up your Energy", (Vector2) {50, 150}, 8, &a);
        UIText("Shot uses energy", (Vector2) {50, 160}, 8, &a);

        DrawSprite(a.atlas, ROBOT_SPRITE, (Vector2) {30, 190});
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
