#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/logger.h"
#include "../include/audio.h"
#include "../include/utils.h"
#include "../include/cursor.h"
#include "../include/ui.h"
#include "option.h"

void OptionInit()
{

}

void OptionUpdate()
{

}

void OptionRender()
{
    char buffer[32] = {0};
    Vector2 mouse_position = GetMousePositionScaled();
    Vector2 pos_title = (Vector2) {
        .x = 160,
        .y = 10,
    };
    BeginTextureMode(a.buffer);
        ClearBackground((Color){62, 32, 24, 255});

        DrawTextPro(a.font, "Option", pos_title, VECTOR_ZERO, 0, 12, 2, (Color) {176, 156, 151, 255});
        if (UITextButton("Back", (Vector2) {5, 10}, mouse_position, &a)) SceneChange(1);
        // Resolution
        UIText("Resolution", (Vector2) {70, 30}, 8, &a);
        UITextButton(">", (Vector2) {300, 50}, mouse_position, &a);
        UITextButton("<", (Vector2) {50, 50}, mouse_position, &a);
        // Master
        sprintf(buffer, "Master (%d)", (i32)(AudioManagerGetMasterVolume() * 10));
        UIText(buffer, (Vector2) {70, 70}, 8, &a);
        if (UITextButton(">", (Vector2) {300, 90}, mouse_position, &a)) {
            AudioManagerSetMasterVolume(Clamp(AudioManagerGetMasterVolume() + 0.1, 0, 1));
            AudioManagerPlaySFX(0);
        }
        if (UITextButton("<", (Vector2) {50, 90}, mouse_position, &a)) {
            AudioManagerSetMasterVolume(Clamp(AudioManagerGetMasterVolume() - 0.1, 0, 1));
            AudioManagerPlaySFX(0);
        }
        UIProgressBar(
            (Rectangle) {
                .x = 58,
                .y = 90,
                .width = 230,
                .height = 8,
            },
            AudioManagerGetMasterVolume(),
            1
        );
        // BGM
        sprintf(buffer, "BGM (%d)", (i32)(AudioManagerGetBGMVolume() * 10));
        UIText(buffer, (Vector2) {70, 110}, 8, &a);
        if (UITextButton(">", (Vector2) {300, 130}, mouse_position, &a)) {
            AudioManagerSetBGMVolume(Clamp(AudioManagerGetBGMVolume() + 0.1, 0, 1));
        }
        if (UITextButton("<", (Vector2) {50, 130}, mouse_position, &a)) {
            AudioManagerSetBGMVolume(Clamp(AudioManagerGetBGMVolume() - 0.1, 0, 1));
        }
        UIProgressBar(
            (Rectangle) {
                .x = 58,
                .y = 130,
                .width = 230,
                .height = 8,
            },
            AudioManagerGetBGMVolume(),
            1
        );
        // SFX
        sprintf(buffer, "SFX (%d)", (i32)(AudioManagerGetSFXVolume() * 10));
        UIText(buffer, (Vector2) {70, 150}, 8, &a);
        if (UITextButton(">", (Vector2) {300, 170}, mouse_position, &a)) {
            AudioManagerSetSFXVolume(Clamp(AudioManagerGetSFXVolume() + 0.1, 0, 1));
            AudioManagerPlaySFX(0);
        }
        if (UITextButton("<", (Vector2) {50, 170}, mouse_position, &a)) {
            AudioManagerSetSFXVolume(Clamp(AudioManagerGetSFXVolume() - 0.1, 0, 1));
            AudioManagerPlaySFX(0);
        }
        UIProgressBar(
            (Rectangle) {
                .x = 58,
                .y = 170,
                .width = 230,
                .height = 8,
            },
            AudioManagerGetSFXVolume(),
            1
        );
        DrawCursor(&a, mouse_position);
    EndTextureMode();
}

void OptionDeinit()
{

}

Scene GetSceneOption()
{
    return (Scene) {
        .init = OptionInit,
        .deinit = OptionDeinit,
        .update = OptionUpdate,
        .render = OptionRender,
    };
}
