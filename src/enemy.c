#include <raylib.h>
#include <raymath.h>
#include <assert.h>
#include "include/enemy.h"
#include "include/audio.h"
#include "include/bullet.h"
#include "include/collision.h"
#include "include/game.h"
#include "include/item.h"
#include "include/logger.h"
#include "include/particle.h"
#include "include/player.h"
#include "include/sprite.h"
#include "include/timer.h"
#include "include/ui.h"
#include "include/utils.h"

void InsertEnemy(Vector2 pos)
{
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (temp->exists) continue;
        __LOG("Spawning enemy %d", i);

        temp->position = pos;
        temp->exists = true;
        temp->hp = 10;
        temp->max_hp = 10;
        temp->shot_cooldown = TimerInit(4, true);
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
    assert(cam != NULL);
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
    assert(arr != NULL);
    assert(cam != NULL);
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (!temp->exists) continue;
        if (temp->position.y > cam->target.y + GAME_HEIGHT * 2 || temp->hp < 0) {
            DropRandomItem(temp->position, ENEMY_DROP_CHANCE);
            AudioManagerPlaySFXRandomPitch(2, 5, 15);
            SpawnMediumExplosion((Vector2) {
                .x = temp->position.x - temp->sprite.src.width / 2.,
                .y = temp->position.y - temp->sprite.src.height / 2.,
            });
            __LOG("Despawn enemy %d", i);
            temp->exists = false;
        }
    }
}

void DrawEnemy(EnemyBot *arr, Assets *a)
{
    assert(arr != NULL);
    assert(a != NULL);
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (!temp->exists) continue;

        DrawSprite(a->atlas, temp->sprite, temp->position);
        /*DrawHPBar(temp->hp, temp->max_hp, temp->position, (Vector2) {temp->sprite.src.width, temp->sprite.src.height});*/
        if (g.debug_collision) {
            DrawCollisionBox(temp->collision);
        }
    }
}

void UpdateEnemy(EnemyBot *arr, Player *p)
{
    assert(arr != NULL);
    assert(p != NULL);
    f32 delta = GetFrameTime();
    for (int i = 0; i < MAX_ENEMY; i++) {
        EnemyBot *temp = &g.enemy[i];
        if (!temp->exists) continue;
        // Player Direction
        Vector2 dir = Vector2Subtract(p->position, temp->position);

        TimerUpdate(&temp->shot_cooldown);

        if (TimerCompleted(&temp->shot_cooldown)) {
            Vector2 dir_shot = Vector2Normalize(dir);
            dir_shot = Vector2Scale(dir_shot, ENEMY_BULLET_SPEED);

            AudioManagerPlaySFXRandomPitch(1, 5, 15);
            SpawnEnemyBullet(dir_shot, temp->position);
        }

        // Movement
        dir = Vector2Normalize(dir);
        dir = Vector2Scale(dir, ENEMY_SPEED);

        for (int i = 0; i < MAX_OBSTACLE; i++) {
            Obstacle *temp_obs = &g.obstacle[i];
            if (!temp_obs->exist) continue;

            if (CheckCollisionObstacle(temp_obs, &temp->collision) && !temp->collided) {
                dir.y = -dir.y; // push a bit?
                temp->collided = true;
                break;
            } else {
                temp->collided = false;
            }
        }


        // Apply
        temp->vel = Vector2Add(dir, temp->vel);
        temp->vel = Vector2Scale(temp->vel, FRICTION);
        temp->vel = Vector2Clamp(temp->vel, (Vector2) {-ENEMY_MAX_SPEED, -ENEMY_MAX_SPEED}, (Vector2){ENEMY_MAX_SPEED, ENEMY_MAX_SPEED});
        temp->position = Vector2Add(temp->position, Vector2Scale(temp->vel, delta));
        temp->collision.pos = temp->position;
    }
}
