#include <raylib.h>
#include <string.h>
#include <math.h>

#include "gameplay.h"

#include "../include/logger.h"
#include "../include/game.h"
#include "../include/assets.h"
#include "../include/bullet.h"
#include "../include/cursor.h"
#include "../include/enemy.h"
#include "../include/event.h"
#include "../include/item.h"
#include "../include/laser.h"
#include "../include/obstacle.h"
#include "../include/parallax.h"
#include "../include/player.h"
#include "../include/scene.h"
#include "../include/ui.h"
#include "../include/utils.h"
#include "../include/wall.h"

void GameReset()
{
    memset(g.enemy, 0, sizeof(EnemyBot) * MAX_ENEMY);
    memset(g.bullet, 0, sizeof(Bullet) * MAX_BULLET);
    memset(g.laser, 0, sizeof(Laser) * MAX_LASER);
    memset(g.item, 0, sizeof(Item) * MAX_ITEM);
    memset(g.obstacle, 0, sizeof(Obstacle) * MAX_OBSTACLE);

    PlayerInit(&g.player);
    ResetEventBuffer();
    g.score = 0;
    g.state = GAME_STATE_RUNNING;

    /*SpawnItem((Vector2) {20, 20}, 5, ITEM_TYPE_ENERGY);*/

    /*InsertEnemyLaserSide((Vector2) {100, -50}, 8, true);*/
    /*InsertEnemyLaserSide((Vector2) {-100, 40}, 18, false);*/
    /*InsertWarning((Vector2) {100, 0});*/
    /*InsertEnemy((Vector2) {0, 0});*/
    /*InsertObstacle((Vector2) {.x = 50, .y = 200}, 8, 0);*/
    /*InsertObstacle((Vector2) {.x = 50, .y = 50}, 12, 1);*/
    g.layer = (ParallaxLayer) {
        .speedY = 1,
        .speedX = 1,
        .offset = (Vector2) {0, 0},
        .texture = a.background,
    };
    g.wall_left = (Wall) {
        .depth = 16,
        .positionX = -115,
    };
    g.wall_right = (Wall) {
        .depth = 16,
        .positionX = 110,
    };
    g.debug_collision = 1;
    g.camera = (Camera2D) {
        .rotation = 0,
        .zoom = 1.,
        .offset = (Vector2){GAME_WIDTH / 2., GAME_HEIGHT / 2.},
        .target = (Vector2){0, 0},
    };

}


void GameplayInit()
{
    GameReset();
}

void GameplayUpdate()
{
    Vector2 mouse_position = GetMousePositionScaled();
    Vector2 mouse_position_world = GetScreenToWorld2D(mouse_position, g.camera);
    g.camera.target = g.player.position;

    if (IsKeyPressed(KEY_F1)) {
        g.debug_collision = !g.debug_collision;
    }
    if (IsKeyPressed(KEY_ESCAPE) && g.state != GAME_STATE_GAME_OVER) {
        g.state = g.state == GAME_STATE_PAUSED ? GAME_STATE_RUNNING : GAME_STATE_PAUSED;
    }
    if (g.player.hp < 0) g.state = GAME_STATE_GAME_OVER;

    if (g.state == GAME_STATE_RUNNING) {
        g.score = MIN(g.score, -g.camera.target.y / 2.);

        SpawnEnemy(&g.camera, 7);
        SpawnObstacle(&g.camera, 10);
        SpawnLaser(&g.camera, 2);

        DespawnEnemy(g.enemy, &g.camera);
        DespawnBullet(g.bullet, &g.camera);
        DespawnObstacle(g.obstacle, &g.camera);
        DespawnLaser(g.laser);
        DespawnItem(g.item, &g.camera);

        UpdateWarning(g.warning_info);
        UpdateEnemy(g.enemy, &g.player);
        UpdateBullet(g.bullet);
        UpdateLaser(g.laser);
        UpdateItem(g.item);
        UpdatePlayer(&g.player, mouse_position_world);

        CameraShake(&g.camera, &g.shakeness, 1);
    }
}

void DrawLightMask()
{
    BeginTextureMode(a.light_mask);
        ClearBackground((Color) {106, 109, 132, 200});
        DrawRectangle(0, 0, 82, 240, WHITE);
        DrawRectangle(305, 0, 82, 240, WHITE);
        BeginMode2D(g.camera);
            DrawCircle(g.player.position.x, g.player.position.y, 80, WHITE);
            DrawLaserLightMask(g.laser);
            for (int i = 0; i < MAX_ITEM; i++) {
                Item *temp = &g.item[i];
                if (!temp->exist) continue;
                DrawCircle(temp->position.x, temp->position.y, 20, WHITE);
            }
            for (int i = 0; i < MAX_BULLET; i++) {
                Bullet *temp = &g.bullet[i];
                if (!temp->exist) continue;
                DrawCircle(temp->position.x, temp->position.y, 20, WHITE);
            }
        EndMode2D();
    EndTextureMode();
}

static void GameplayRender()
{
    Vector2 mouse_position = GetMousePositionScaled();
    Vector2 mouse_position_world = GetScreenToWorld2D(mouse_position, g.camera);
    DrawLightMask();

    BeginTextureMode(a.buffer);
        ClearBackground((Color){178, 156, 151, 255});

        DrawParallaxLayer(&g.layer, g.camera.target);
        BeginMode2D(g.camera);
            DrawObstacle(g.obstacle, &a);
            DrawPlayer(&g.player, &a, mouse_position_world);
            DrawEnemy(g.enemy, &a);
            DrawBullet(g.bullet, &a);
            DrawItem(g.item, &a);
            DrawWarning(g.warning_info, &a);
            DrawLaser(g.laser, &a);
            DrawCursor(&a, mouse_position_world);
        EndMode2D();

        if (g.state == GAME_STATE_PAUSED) {
            UIText("Game Paused", (Vector2) {115, 50}, 12, &a);
            if (UITextButton("Continue", (Vector2) {105, 90}, mouse_position, &a)) {
                g.state = GAME_STATE_RUNNING;
            }
            if (UITextButton("Exit", (Vector2) {225, 90}, mouse_position, &a)) {
                SceneChange(1);
            }

        } else if (g.state == GAME_STATE_GAME_OVER) {
            char buffer[32] = {0};
            sprintf(buffer, "SCORE : %d", g.score);

            UIText("Game Over", (Vector2) {125, 50}, 12, &a);
            UIText(buffer, (Vector2) {115, 95}, 8, &a);

            sprintf(buffer, "HI SCORE : %d", g.high_score);
            UIText(buffer, (Vector2) {115, 115}, 8, &a);
            if (g.score > g.high_score) UIText("New High Score!", (Vector2) {115, 75}, 8, &a);
            if (UITextButton("Continue", (Vector2) {105, 150}, mouse_position, &a)) {
                SceneChange(0);
                g.high_score = MIN(g.high_score, g.score);
                SaveFileData("resources/score.txt", &g.high_score, sizeof(i32));
            }
            if (UITextButton("Exit", (Vector2) {225, 150}, mouse_position, &a)) {
                SceneChange(1);
                g.high_score = MIN(g.high_score, g.score);
                SaveFileData("resources/score.txt", &g.high_score, sizeof(i32));
            }
        }

        BeginBlendMode(BLEND_MULTIPLIED);
        BeginShaderMode(a.lighting);
            DrawTexturePro(
                a.light_mask.texture,
                (Rectangle) {.x = 0, .y = 0, .width = a.buffer.texture.width, .height = -a.buffer.texture.height},
                (Rectangle) {.x = 0, .y = 0, .width = GAME_WIDTH, .height = GAME_HEIGHT},
                (Vector2) {0, 0},
                0,
                WHITE
            );
        EndShaderMode();
        EndBlendMode();

        DrawTexture(a.ui_slot, 0, 0, WHITE);
        DrawScore(g.score, &a);
        DrawHP(g.player.hp, g.player.max_hp, &a);
        DrawEnergy(g.player.power, g.player.max_power, &a);

    EndTextureMode();
}

void GameplayDeinit()
{

}

Scene GetSceneGameplay()
{
    return (Scene) {
        .init = GameplayInit,
        .deinit = GameplayDeinit,
        .update = GameplayUpdate,
        .render = GameplayRender,
    };
}
