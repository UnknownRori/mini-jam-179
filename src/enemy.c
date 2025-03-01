#include <raylib.h>
#include <raymath.h>
#include "include/enemy.h"
#include "include/collision.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/player.h"
#include "include/sprite.h"
#include "include/utils.h"

void InsertEnemy(Vector2 pos)
{
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (temp->exists) continue;
        __LOG("Spawning enemy %d", i);

        temp->position = pos;
        temp->exists = true;
        temp->hp = 5;
        temp->collision = (CollisionBox) {
            .box = (Rectangle) {
                .x = -8,
                .y = -8,
                .width = 16,
                .height = 16,
            },
        };
        temp->sprite = (Sprite){
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
        break;
    }
}

void SpawnEnemy(Camera2D * cam, int threshold)
{
    int spawnValue = GetRandomValue(0, 1000);
    if (spawnValue > threshold) return;
    Vector2 min = {
        .x = -100,
        .y = cam->target.y - GAME_HEIGHT - 100,
    };
    Vector2 max = {
        .x = 100,
        .y = cam->target.y - GAME_HEIGHT,
    };
    Vector2 spawnPoint = GetRandomVector2(min, max);
    InsertEnemy(spawnPoint);
}
void DespawnEnemy(EnemyBot * arr, Camera2D * cam)
{
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (!temp->exists) continue;
        if (temp->position.y > cam->target.y + GAME_HEIGHT) {
        __LOG("Despawn enemy %d", i);
            temp->exists = false;
        }
    }
}

void DrawEnemy(EnemyBot *arr, Assets *a)
{
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (!temp->exists) continue;

        DrawSprite(a->atlas, temp->sprite, temp->position);
        if (g.debug_collision) {
            DrawCollisionBox(temp->collision);
        }
    }
}

void UpdateEnemy(EnemyBot *arr, Player *p)
{
    f32 delta = GetFrameTime();
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (!temp->exists) continue;
        Vector2 dir = Vector2Subtract(p->position, temp->position);
        dir = Vector2Normalize(dir);
        dir = Vector2Scale(dir, 15);
        dir = Vector2Scale(dir, delta);
        temp->position = Vector2Add(dir, temp->position);
        temp->collision.pos = temp->position;
    }
}
