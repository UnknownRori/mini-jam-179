#include <raylib.h>
#include <raymath.h>
#include "include/laser.h"
#include "include/collision.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/sprite.h"
#include "include/timer.h"

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

void InsertEnemyLaserSide(Vector2 start_pos, i32 length, bool left)
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
        .left = left,
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
        .attack_timer = TimerInit(2, false),
        .sustain_timer = TimerInit(4, false),
        .decay_timer = TimerInit(2., false),
        .sprite = spr,
        .state = LASER_STATE_DELAY,
        .delay = 2,
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
            case LASER_STATE_FIRING: {
                if (g.debug_collision) {
                    DrawRectangleLines(
                        temp->start_position.x,
                        temp->start_position.y, 8,
                        8,
                        RED
                    );
                }
                f32 progress = TimeProgress(&temp->attack_timer);
                i32 progress_step = Lerp(temp->length, 1., progress);
                /*i32 progress_step = 1. + (1. - progress) * (temp->length - 1.);*/
                for (int i = 0; i < progress_step; i++) {
                    Vector2 pos = {
                        .x = temp->start_position.x,
                        .y = temp->start_position.y,
                    };
                    if (temp->left) {
                        pos.x -= (i * temp->sprite.src.width);
                    } else {
                        pos.x += (i * temp->sprite.src.width);
                    }
                    DrawSprite(a->atlas, temp->sprite, pos);
                }
            }
                break;
            case LASER_STATE_SUSTAIN: {
                    if (g.debug_collision) {
                        DrawRectangleLines(
                            temp->start_position.x,
                            temp->start_position.y, 8,
                            8,
                            GREEN
                        );
                    }

                    for (int i = 0; i < temp->length; i++) {
                        Vector2 pos = {
                            .x = temp->start_position.x,
                            .y = temp->start_position.y,
                        };
                        if (temp->left) {
                            pos.x -= (i * temp->sprite.src.width);
                        } else {
                            pos.x += (i * temp->sprite.src.width);
                        }
                        DrawSprite(a->atlas, temp->sprite, pos);
                    }
                }
                break;
            case LASER_STATE_DECAY: {
                    if (g.debug_collision) {
                        DrawRectangleLines(
                            temp->start_position.x,
                            temp->start_position.y, 8,
                            8,
                            ORANGE
                        );
                    }
                    f32 progress = TimeProgress(&temp->decay_timer);
                    i32 progress_step = Lerp(1., temp->length, progress);
                    __LOG("%d", progress_step);

                    for (int i = 0; i < progress_step; i++) {
                        Vector2 pos = {
                            .x = temp->start_position.x,
                            .y = temp->start_position.y,
                        };
                        if (temp->left) {
                            pos.x -= (i * temp->sprite.src.width);
                        } else {
                            pos.x += (i * temp->sprite.src.width);
                        }
                        DrawSprite(a->atlas, temp->sprite, pos);
                }
                }
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
                break;
            case LASER_STATE_FIRING:
                TimerUpdate(&temp->attack_timer);
                if (TimerCompleted(&temp->attack_timer)) temp->state = LASER_STATE_SUSTAIN;
                break;
            case LASER_STATE_SUSTAIN:
                TimerUpdate(&temp->sustain_timer);
                if (TimerCompleted(&temp->sustain_timer)) temp->state = LASER_STATE_DECAY;
                break;
            case LASER_STATE_DECAY:
                TimerUpdate(&temp->decay_timer);
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
        if (!TimerCompleted(&temp->decay_timer)) continue;
        __LOG("Despawning Laser [%d]", i);

        temp->exist = false;
    }
}
