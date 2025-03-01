#include <raylib.h>
#include <assert.h>
#include "include/obstacle.h"
#include "include/collision.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/sprite.h"

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
            .collision = (CollisionBox) {
                .box = (Rectangle) {
                    .x = -4,
                    .y = -4,
                    .width = OBSTACLE_WIDTH * length,
                    .height = OBSTACLE_HEIGHT,
                },
            },
            .end = (Sprite) {
                .flipX = (temp->flags & OBSTACLE_FLAG_LEFT) == OBSTACLE_FLAG_LEFT ? 1 : 0,
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
        i32 offsetX = (temp->flags & OBSTACLE_FLAG_LEFT) == OBSTACLE_FLAG_LEFT ? -100 : 108 - (OBSTACLE_WIDTH * temp->length);
        temp->collision.pos.x = offsetX;
        for (int i = 0; i < temp->length; i++) {
            Vector2 pos = {
                .x = i * OBSTACLE_WIDTH + offsetX,
                .y = temp->position.y,
            };
            DrawSprite(a->atlas, temp->body, pos);
        }
        if (g.debug_collision) {
            DrawCollisionBox(temp->collision);
        }
    }
}

// Require obstacle to be an array and it will despawn if it outside the camera
void DespawnObstacle(Obstacle*, Camera2D *);

void CheckCollisionObstacle(Obstacle*, CollisionBox*);
