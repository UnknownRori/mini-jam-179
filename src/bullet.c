#include <raylib.h>
#include <raymath.h>
#include <assert.h>
#include "include/bullet.h"
#include "include/audio.h"
#include "include/collision.h"
#include "include/enemy.h"
#include "include/event.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/particle.h"
#include "include/sprite.h"

void SpawnEnemyBullet(Vector2 vel, Vector2 position)
{
    Bullet b = {
        .velocity = vel,
        .position = position,
        .damage = 10,
        .collision = (CollisionBox) {
            .box = (Rectangle) {
                .x = -4,
                .y = -4,
                .width = 8,
                .height = 8,
            },
        },
        .group = ENEMY_BULLET_GROUP,
        .sprite = (Sprite) {
            .flipX = false,
            .rotation = 0,
            .scale = 1,
            .src = (Rectangle) {
                .x = 8,
                .y = 104,
                .width = 8,
                .height = 8,
            },
        },
    };
    InsertBullet(b);
}

void SpawnPlayerBullet(Vector2 vel, Vector2 position)
{
    Bullet b = {
        .damage = 10,
        .velocity = vel,
        .position = position,
        .collision = (CollisionBox) {
            .box = (Rectangle) {
                .x = -4,
                .y = -4,
                .width = 8,
                .height = 8,
            },
        },
        .group = PLAYER_BULLET_GROUP,
        .sprite = (Sprite) {
            .flipX = false,
            .rotation = 0,
            .scale = 1,
            .src = (Rectangle) {
                .x = 0,
                .y = 104,
                .width = 8,
                .height = 8,
            },
        },
    };
    InsertBullet(b);
}

void InsertBullet(Bullet bullet)
{
    for (int i = 0; i < MAX_BULLET; i++) {
        Bullet *temp = &g.bullet[i];
        if (temp->exist) continue;
        __LOG("Spawning Bullet %d", i);
        *temp = bullet;
        temp->exist = true;
        break;
    }
}
// Array of enemy it will check if it out of bound
void DrawBullet(Bullet *b, Assets *a)
{
    assert(b != NULL);
    assert(a != NULL);
    for (int i = 0; i < MAX_BULLET; i++) {
        Bullet *temp = &b[i];
        if (!temp->exist) continue;

        DrawSprite(a->atlas, temp->sprite, temp->position);
        if (g.debug_collision) {
            DrawCollisionBox(temp->collision);
        }
    }
}
void UpdateBullet(Bullet *b)
{
    assert(b != NULL);
    f32 delta = GetFrameTime();
    for (int i = 0; i < MAX_BULLET; i++) {
        Bullet *temp = &b[i];
        if (!temp->exist) continue;

        if (temp->group == ENEMY_BULLET_GROUP) {
            if (CheckCollisionBox(g.player.collision, temp->collision)) {
                temp->exist = false;
                g.player.hp -= temp->damage;
                AudioManagerPlaySFXRandomPitch(4, 5, 15);
                PushEvent(EVENT_HP_DECREASE);
                break;
            }
        }


        if (temp->group == PLAYER_BULLET_GROUP) {
            for (int i = 0; i < MAX_ENEMY; i++) {
                EnemyBot *enemy = &g.enemy[i];
                if (!enemy->exists) continue;
                if (CheckCollisionBox(enemy->collision, temp->collision)) {
                    Vector2 dir = Vector2Subtract(enemy->position, temp->position);
                    Vector2 dir_normal = Vector2Normalize(dir);
                    Vector2 dir_oposite = Vector2Scale(dir_normal, ENEMY_BULLET_SPEED);

                    temp->exist = false;
                    enemy->hp -= temp->damage;
                    AudioManagerPlaySFXRandomPitch(6, 5, 15);
                    break;
                }
            }
        }

        // Apply
        Vector2 vel = Vector2Scale(temp->velocity, delta);
        temp->position = Vector2Add(vel, temp->position);
        temp->collision.pos = temp->position;
    }
}
// Array of enemy it will check if it out of bound
void DespawnBullet(Bullet *b, Camera2D *cam)
{
    assert(b != NULL);
    assert(cam != NULL);
    for (int i = 0; i < MAX_ENEMY; i++) {
        Bullet *temp = &b[i];
        if (!temp->exist) continue;

        bool hit_obstacle = false;
        bool is_on_bottom = temp->position.y > cam->target.y + GAME_HEIGHT;
        bool is_on_top = temp->position.y < cam->target.y - GAME_HEIGHT;
        bool is_hit_wall_left = WallIntersectCollisionBox(&g.wall_left, &temp->collision);
        bool is_hit_wall_right = WallIntersectCollisionBox(&g.wall_right, &temp->collision);

        for (int i = 0; i < MAX_OBSTACLE; i++) {
            Obstacle *temp_obs = &g.obstacle[i];
            if (!temp_obs->exist) continue;

            if (CheckCollisionObstacle(temp_obs, &temp->collision)) {
                hit_obstacle = true;
                break;
            }
        }

        if (is_on_top || is_on_bottom || is_hit_wall_right || is_hit_wall_left || hit_obstacle) {
            __LOG("Despawn bullet %d", i);
            SpawnSmallExplosion(temp->position);
            temp->exist = false;
        }
    }
}
