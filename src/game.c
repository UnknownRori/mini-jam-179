#include <raylib.h>
#include "./include/game.h"
#include "include/assets.h"
#include "include/cursor.h"
#include "include/player.h"
#include "include/utils.h"

Game g = {0};
Assets a = {0};

void GameLoop(void)
{
    Vector2 mouse_position = GetMousePositionScaled();
    UpdatePlayer(&g.player, mouse_position);
    BeginDrawing();

    BeginMode2D(g.camera);
        BeginTextureMode(a.buffer);
            ClearBackground((Color){62, 32, 24, 255});
            DrawTexture(a.background, 0, 0, WHITE);
            DrawPlayer(&g.player, &a);
            DrawCursor(&a, mouse_position);
        EndTextureMode();
    EndMode2D();

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

    // My stuff
    LoadAssets(&a);
    PlayerInit(&g.player);

    g.debug_collision = 1;
    g.camera = (Camera2D) {
        .rotation = 0,
        .zoom = 0.5,
        .offset = (Vector2){SCREEN_WIDTH / 2., SCREEN_HEIGHT / 2.},
        .target = (Vector2){-50, -50},
    };
}
void GameUnload(void)
{
    UnloadAssets(&a);
}
bool ShouldGameQuit(void)
{
    return false;
}
