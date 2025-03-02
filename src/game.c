#include <raylib.h>
#include <string.h>
#include "include/game.h"
#include "include/assets.h"
#include "include/audio.h"
#include "include/scene.h"
#include "include/timer.h"

#include "scene/gameplay.h"
#include "scene/help.h"
#include "scene/main_menu.h"

Game g = {0};
Assets a = {0};

void GameLoop(void)
{
    SceneUpdate();

    BeginDrawing();

        SceneDraw();

        ClearBackground(WHITE);
        DrawTexturePro(
            a.buffer.texture,
            (Rectangle) {.x = 0, .y = 0, .width = a.buffer.texture.width, .height = -a.buffer.texture.height},
            (Rectangle) {.x = 0, .y = 0, .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT},
            (Vector2) {0, 0},
            0,
            WHITE
        );
        DrawFPS(0, 0);

    EndDrawing();
}


void GameInit(void)
{
    // Raylib stuff
    SetExitKey(KEY_F1);
    HideCursor();

    // Setup config
    AudioManagerSetMasterVolume(1.);
    AudioManagerSetSFXVolume(0.7);
    AudioManagerSetBGMVolume(0.5);

    // Hard Reset
    memset(&g, 0, sizeof(Game));

    // My stuff
    LoadAssets(&a);

    // Load Scene
    SceneChangeTransition(SceneDefaultTransition);
    SceneInit(TimerInit(1, false));
    SceneAdd(0, GetSceneGameplay());
    SceneAdd(1, GetSceneMainMenu());
    SceneAdd(2, GetSceneHelp());
    SceneSwap(0);

}

void GameUnload(void)
{
    UnloadAssets(&a);
}
bool ShouldGameQuit(void)
{
    return false;
}
