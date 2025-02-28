#include <raylib.h>
#include "include/game.h"
#include "include/assets.h"
#include "include/cursor.h"
#include "include/parallax.h"
#include "include/player.h"
#include "include/utils.h"
#include "include/logger.h"

Game g = {0};
Assets a = {0};

void GameLoop(void)
{
    Vector2 mouse_position = GetMousePositionScaled();
    Vector2 mouse_position_world = GetScreenToWorld2D(mouse_position, g.camera);
    g.camera.target = g.player.position;
    UpdatePlayer(&g.player, mouse_position_world);
    BeginDrawing();

    BeginTextureMode(a.buffer);
        ClearBackground((Color){178, 156, 151, 255});

        DrawParallaxLayer(&g.layer, g.camera.target);
        BeginMode2D(g.camera);
            DrawPlayer(&g.player, &a);
            DrawCursor(&a, mouse_position_world);
        EndMode2D();

        DrawTexture(a.ui_slot, 0, 0, WHITE);
    EndTextureMode();

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

    g.layer = (ParallaxLayer) {
        .speedY = 1,
        .speedX = 1,
        .offset = (Vector2) {0, 0},
        .texture = a.background,
    };
    g.debug_collision = 1;
    g.camera = (Camera2D) {
        .rotation = 0,
        .zoom = 1.,
        .offset = (Vector2){GAME_WIDTH / 2., GAME_HEIGHT / 2.},
        .target = (Vector2){0, 0},
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
