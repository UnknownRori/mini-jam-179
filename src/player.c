#include <raylib.h>
#include <raymath.h>
#include <assert.h>
#include "include/audio.h"
#include "include/bullet.h"
#include "include/collision.h"
#include "include/event.h"
#include "include/game.h"
#include "include/player.h"
#include "include/laser.h"
#include "include/logger.h"
#include "include/obstacle.h"
#include "include/sprite.h"
#include "include/timer.h"
#include "include/types.h"
#include "include/wall.h"

void PlayerInit(Player* p)
{
    assert(p != NULL);
    p->hp = 100;
    p->max_hp = 100;
    p->power = 100;
    p->max_power = 100;
    p->speed = PLAYER_SPEED;
    p->position = (Vector2) {
        .x = 0,
        .y = 0,
    };
    p->collision.pos = p->position;
    p->collision.box = (Rectangle) {
        .x = -7,
        .y = -7,
        .width = 14,
        .height = 14,
    };
    p->turret = (Sprite){
        .flipX = false,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 0,
            .y = 0,
            .width = 16,
            .height = 16,
        },
    };
    p->core = (Sprite){
        .flipX = false,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 16,
            .y = 0,
            .width = 16,
            .height = 16,
        },
    };
}
void DrawPlayer(Player* p, Assets *a, Vector2 mouse)
{
    assert(p != NULL);
    assert(a != NULL);
    if (g.debug_collision) {
        DrawCollisionBox(p->collision);
    }
    DrawSprite(a->atlas, p->core, p->position);

    DrawSprite(a->atlas, p->turret, p->position);

    // AIM
    Vector2 dir = Vector2Subtract(mouse, dir);
    DrawLineV(p->position, dir, (Color) {116, 79, 70, 255});
}


void UpdatePlayer(Player* p, Vector2 mouse)
{
    assert(p != NULL);
    // Movement
    f32 delta = GetFrameTime();
    Vector2 dir = Vector2Subtract(p->position, mouse);
    f32 angle = atan2(dir.y, dir.x) * RAD2DEG;
    angle += 90;

    p->turret.rotation = angle;
    p->collision.pos = p->position;

    // Shoot
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (g.player.power - SHOOT_ENERGY_COST) > 0) {
        Vector2 dir_norm = Vector2Normalize(dir);
        p->vel = Vector2Add(p->vel, Vector2Scale(dir_norm, p->speed));
        Vector2 vel = Vector2Scale(dir_norm, PLAYER_BULLET_SPEED);
        vel = Vector2Rotate(vel, 180 * DEG2RAD);

        p->power -= SHOOT_ENERGY_COST;
        PushEvent(EVENT_ENERGY_DECREASE);
        AudioManagerPlaySFXRandomPitch(0, 5, 15);

        SpawnPlayerBullet(vel, p->position);
    }


    // Collision
    bool collision = false;
    if (WallIntersectCollisionBox(&g.wall_left, &p->collision) && !p->collided) {
        p->vel.x = -p->vel.x;
        collision = true;
    }
    if (WallIntersectCollisionBox(&g.wall_right, &p->collision)&& !p->collided) {
        p->vel.x = -p->vel.x;
        collision = true;
    }
    for (int i = 0; i < MAX_OBSTACLE; i++) {
        Obstacle *temp = &g.obstacle[i];
        if (!temp->exist) continue;

        if (CheckCollisionObstacle(temp, &p->collision) && !p->collided) {
            p->vel.x = -(p->vel.x / 2.);
            p->vel.y = -p->vel.y;
            collision = true;
            break;
        }
    }
    for (int i = 0; i < MAX_LASER; i++) {
        Laser *temp = &g.laser[i];
        if (!temp->exist) continue;

        if (CheckCollisionBox(temp->collision, p->collision)) {
            TimerUpdate(&temp->damage_timer);
            if (TimerCompleted(&temp->damage_timer)) {
                p->hp -= temp->damage;
                AudioManagerPlaySFXRandomPitch(4, 5, 15);
                PushEvent(EVENT_HP_DECREASE);
            }
        } else {
            TimerReset(&temp->damage_timer);
            temp->damage_timer.m_completed = true;
        }
    }

    p->collided = collision;
    if (p->collided) {
        if (!AudioManagerIsPlayingSFX(3)) {
            AudioManagerPlaySFXRandomPitch(3, 5, 15);
        }
    }

    // Apply velocity
    p->vel = Vector2Scale(p->vel, 0.95);
    if (!p->collided) p->vel.y -= GRAVITY * delta;
    p->position = Vector2Add(p->position, Vector2Scale(p->vel, delta));
}
