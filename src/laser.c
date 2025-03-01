#include "include/laser.h"
#include "include/collision.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/sprite.h"
#include "include/timer.h"
#include <raylib.h>

void InsertLaser(Laser l)
{
    for (int i= 0; i < MAX_LASER; i++) {
        Laser *temp = &g.laser[i];
        if (temp->exist) continue;
        __LOG("Spawning Laser %d", i);
        *temp = l;
        temp->exist = true;
        break;
    }
}

void InsertEnemyLaserSide(Vector2 start_pos, i32 length)
{

    Sprite spr = {
        .flipX = false,
        .src = {
            .x = 0,
            .y = 112,
            .width = 8,
            .height = 40,
        },
        .scale = 1,
        .rotation = 0,
    };
    InsertLaser((Laser) {
        .start_position = start_pos,
        .collision = (CollisionBox) {
            .box = {
                .x = start_pos.x,
                .y = start_pos.y,
                .width = spr.src.width,
                .height = spr.src.height,
            },
            .pos = start_pos,
            .collided = false,
        },
        .damage = 10,
        .damage_timer = TimerInit(2, true),
        .sprite = spr,
        .state = LASER_STATE_DELAY,
        .delay = 2,
        .attack_time = 2.,
        .sustain_time = 12.,
        .decay_time = 2.,
        .length = length,
    });
}

void DrawLaser(Laser *arr, Assets *a)
{
    for (int i= 0; i < MAX_LASER; i++) {
        Laser *temp = &g.laser[i];
        if (!temp->exist) continue;
        switch (temp->state) {
            case LASER_STATE_NONE:
                // Do nothing
                break;
            case LASER_STATE_DELAY:
                if (g.debug_collision) {
                    DrawRectangleLines(
                        temp->start_position.x,
                        temp->start_position.y, 8,
                        8,
                        WHITE
                    );
                }
                break;
            case LASER_STATE_FIRING:
                if (g.debug_collision) {
                    DrawRectangleLines(
                        temp->start_position.x,
                        temp->start_position.y, 8,
                        8,
                        RED
                    );
                }
                break;
            case LASER_STATE_SUSTAIN:
                    DrawRectangleLines(
                        temp->start_position.x,
                        temp->start_position.y, 8,
                        8,
                        GREEN
                    );
                break;
            case LASER_STATE_DECAY:
                    DrawRectangleLines(
                        temp->start_position.x,
                        temp->start_position.y, 8,
                        8,
                        ORANGE
                    );
                break;
        }

        if (g.debug_collision) {
            DrawCollisionBox(temp->collision);
        }
    }
}

// This should be an array
void UpdateLaser(Laser *arr)
{
    f32 delta = GetFrameTime();
    for (int i = 0; i < MAX_LASER; i++)
    {
        Laser *temp = &arr[i];
        if (!temp->exist) continue;
        switch (temp->state) {
            case LASER_STATE_NONE:
                // Do nothing
                break;
            case LASER_STATE_DELAY:
                temp->delay -= delta;
                if (temp->delay < 0) temp->state = LASER_STATE_FIRING;
                __LOG("Laser [%d] Delay %f", i, temp->delay);
                break;
            case LASER_STATE_FIRING:
                temp->attack_time -= delta;
                if (temp->attack_time < 0) temp->state = LASER_STATE_SUSTAIN;
                break;
            case LASER_STATE_SUSTAIN:
                temp->sustain_time -= delta;
                if (temp->sustain_time < 0) temp->state = LASER_STATE_DECAY;
                break;
            case LASER_STATE_DECAY:
                temp->decay_time -= delta;
                break;
        }

        temp->collision.pos.x = temp->start_position.x;
        temp->collision.pos.y = temp->start_position.y;
        temp->collision.box.width = temp->sprite.src.width;
        temp->collision.box.height = temp->sprite.src.height;
    }
}

void DespawnLaser(Laser *arr)
{

    for (int i = 0; i < MAX_LASER; i++)
    {
        Laser *temp = &arr[i];
        if (!temp->exist) continue;
        if (temp->decay_time > 0) continue;
        __LOG("Despawning Laser [%d]", i);

        temp->exist = false;
    }
}
