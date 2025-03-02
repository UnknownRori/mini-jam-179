#include <raylib.h>
#include <assert.h>
#include "include/obstacle.h"
#include "include/collision.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/sprite.h"
#include "include/utils.h"

// @params  Vector2 - pos
// @params  i32     - length
void InsertObstacle(Vector2 pos, i32 length, i32 flags)
{
    for (int i = 0; i < MAX_OBSTACLE; i++) {
        Obstacle *temp = &g.obstacle[i];
        if (temp->exist) continue;
        __LOG("Spawning Obstacle %d", i);
        *temp = (Obstacle) {
            .length = length,
            .position = pos,
            .collision = (CollisionBox) {
                .pos = pos,
                .box = (Rectangle) {
                    .x = -4,
                    .y = -4,
                    .width = OBSTACLE_WIDTH * length,
                    .height = OBSTACLE_HEIGHT,
                },
            },
            .end = (Sprite) {
                .flipX = ((flags & OBSTACLE_FLAG_LEFT) == OBSTACLE_FLAG_LEFT) ? 0 : 1,
                .rotation = 0,
                .scale = 1,
                .src = (Rectangle) {
                    .x = 16,
                    .y = 56,
                    .width = OBSTACLE_WIDTH,
                    .height = OBSTACLE_HEIGHT,
                },
            },
            .body = (Sprite) {
                .flipX = 0,
                .rotation = 0,
                .scale = 1,
                .src = (Rectangle) {
                    .x = 8,
                    .y = 56,
                    .width = OBSTACLE_WIDTH,
                    .height = OBSTACLE_HEIGHT,
                },
            },
            .flags = flags,
            .exist = true,
        };
        break;
    }
}

// Require obstacle to be an array and it will despawn if it outside the camera
void DrawObstacle(Obstacle *arr, Assets *a)
{
    assert(arr != NULL);
    assert(a != NULL);
    for (int i = 0; i < MAX_OBSTACLE; i++) {
        Obstacle *temp = &g.obstacle[i];
        if (!temp->exist) continue;

        i32 offsetX = 108 - (OBSTACLE_WIDTH * temp->length);
        i32 length = temp->length;
        i32 loopIndex = 0;

        if ((temp->flags & OBSTACLE_FLAG_LEFT) == OBSTACLE_FLAG_LEFT) {
            offsetX = -100;
            length -= 1;

            Vector2 pos = {
                .x = (temp->length - 1) * OBSTACLE_WIDTH + offsetX,
                .y = temp->position.y,
            };
            DrawSprite(a->atlas, temp->end, pos);
        } else {
            loopIndex += 1;
            Vector2 pos = {
                .x = offsetX - 8,
                .y = temp->position.y,
            };
            DrawSprite(a->atlas, temp->end, pos);
        }

        temp->collision.pos.x = offsetX;

        for (; loopIndex < length; loopIndex++) {
            Vector2 pos = {
                .x = loopIndex * OBSTACLE_WIDTH + offsetX,
                .y = temp->position.y,
            };
            DrawSprite(a->atlas, temp->body, pos);
        }

        if (g.debug_collision) {
            DrawCollisionBox(temp->collision);
        }
    }
}

void SpawnObstacle(Camera2D *cam, i32 threshold)
{
    assert(cam != NULL);
    int spawnValue = GetRandomValue(0, 1000);
    if (spawnValue > threshold) return;
    Vector2 min = {
        .x = 0,
        .y = cam->target.y - GAME_HEIGHT - 100,
    };
    Vector2 max = {
        .x = 0,
        .y = cam->target.y - GAME_HEIGHT,
    };
    Vector2 spawnPoint = GetRandomVector2(min, max);
    i32 length = GetRandomValue(4, 12);
    i32 flags = GetRandomValue(0, 1);
    InsertObstacle(spawnPoint, length, flags);
}

// Require obstacle to be an array and it will despawn if it outside the camera
void DespawnObstacle(Obstacle *obs, Camera2D * cam)
{
    for (int i = 0; i < MAX_OBSTACLE; i++) {
        Obstacle *temp = &obs[i];
        if (!temp->exist) continue;

        bool is_on_bottom = temp->position.y > cam->target.y + GAME_HEIGHT * 3;
        bool is_on_top = temp->position.y < cam->target.y - GAME_HEIGHT * 3;

        if (is_on_top || is_on_bottom) {
            __LOG("Despawn Obstacle %d", i);
            temp->exist = false;
        }
    }
}

bool CheckCollisionObstacle(Obstacle *b, CollisionBox *c)
{
    assert(b != NULL);
    return CheckCollisionBox(b->collision, *c);
}
