#include <raylib.h>
#include <string.h>
#include "include/game.h"
#include "include/assets.h"
#include "include/audio.h"
#include "include/logger.h"
#include "include/resolution.h"
#include "include/scene.h"
#include "include/timer.h"

#include "scene/gameplay.h"
#include "scene/help.h"
#include "scene/main_menu.h"
#include "scene/option.h"

Game g = {0};
Assets a = {0};

void GameLoop(void)
{
    char buffer[32] = {0};
    sprintf(buffer, "FPS : %d", GetFPS());

    if (IsKeyPressed(KEY_F1)) {
        g.debug_collision = !g.debug_collision;
    }

    AudioManagerUpdateMusic();
    SceneUpdate();

    BeginDrawing();

        SceneDraw();

        ClearBackground(WHITE);
        DrawTexturePro(
            a.buffer.texture,
            (Rectangle) {.x = 0, .y = 0, .width = a.buffer.texture.width, .height = -a.buffer.texture.height},
            (Rectangle) {.x = 0, .y = 0, .width = GetScreenSizeBasedResolution(g.resolution).x, .height = GetScreenSizeBasedResolution(g.resolution).y},
            (Vector2) {0, 0},
            0,
            WHITE
        );
        DrawText(buffer, 12, 12, 18, (Color) {178, 156, 151, 255});
        DrawText("MEM : ± 152 M", 12, 34, 18, (Color) {178, 156, 151, 255});

    EndDrawing();
}


void GameInit(void)
{
    // Raylib stuff
    SetExitKey(KEY_F12);
#if defined(PLATFORM_WEB)
#else
    HideCursor();
#endif


    // Setup config
    AudioManagerSetMasterVolume(1.);
    AudioManagerSetSFXVolume(0.5);
    AudioManagerSetBGMVolume(0.3);

    // Hard Reset
    memset(&g, 0, sizeof(Game));
    g.resolution = RESOLUTION_1366;
    SetWindowSize(GetScreenSizeBasedResolution(g.resolution).x, GetScreenSizeBasedResolution(g.resolution).y);

    // My stuff
    LoadAssets(&a);

    int size = 0;
    unsigned char *data = LoadFileData("resources/score.txt", &size);
    if (data != NULL) g.high_score = *(i32*)data;

    // Load Scene
    SceneChangeTransition(SceneDefaultTransition);
    SceneInit(TimerInit(1, false));
    SceneAdd(0, GetSceneGameplay());
    SceneAdd(1, GetSceneMainMenu());
    SceneAdd(2, GetSceneHelp());
    SceneAdd(3, GetSceneOption());
    SceneSwap(1);

}

void GameUnload(void)
{
    UnloadAssets(&a);
}
bool ShouldGameQuit(void)
{
    return g.should_quit;
}
