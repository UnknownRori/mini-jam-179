#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#include "main_menu.h"

#include "../include/game.h"
#include "../include/logger.h"
#include "../include/utils.h"
#include "../include/cursor.h"
#include "../include/ui.h"

void MainMenuInit()
{
    g.layer = (ParallaxLayer) {
        .speedY = 1,
        .speedX = 1,
        .offset = (Vector2) {0, 0},
        .texture = a.background,
    };
    g.camera = (Camera2D){0};
}

void MainMenuUpdate()
{

}

void MainMenuRender()
{
    char buffer[32] = {0};
    sprintf(buffer, "HI SCORE : %d", g.high_score);
    Vector2 mouse_position = GetMousePositionScaled();
    Vector2 pos_title = (Vector2) {
        .x = 110,
        .y = 40 + 4. * sin(4 * GetTime()),
    };

    g.camera.target.y += 0.5;
    BeginTextureMode(a.buffer);
        ClearBackground((Color){62, 32, 24, 255});

        DrawParallaxLayer(&g.layer, g.camera.target);
        DrawTextPro(a.font, buffer, (Vector2) {130, 180}, VECTOR_ZERO, 0, 8, 2, (Color) {176, 156, 151, 255});
        DrawTextPro(a.font, "Escape Velocity", pos_title, VECTOR_ZERO, 0, 10, 2, (Color) {176, 156, 151, 255});
        if (UITextButton("New Run", (Vector2) {155, 80}, mouse_position, &a)) SceneChange(0);
        if (UITextButton("Option", (Vector2) {155, 90}, mouse_position, &a)) SceneChange(3);
        if (UITextButton("Help", (Vector2) {155, 100}, mouse_position, &a)) SceneChange(2);
        if (UITextButton("Exit", (Vector2) {155, 110}, mouse_position, &a)) g.should_quit = true;;
        DrawCursor(&a, mouse_position);
    EndTextureMode();
}

void MainMenuDeinit()
{

}

Scene GetSceneMainMenu()
{
    return (Scene) {
        .init = MainMenuInit,
        .deinit = MainMenuDeinit,
        .update = MainMenuUpdate,
        .render = MainMenuRender,
    };
}
