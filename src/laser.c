#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include "include/laser.h"
#include "include/assets.h"
#include "include/collision.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/sprite.h"
#include "include/timer.h"
#include "include/ui.h"
#include "include/utils.h"

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
                .x = -(spr.src.width / 2.),
                .y = -(spr.src.height / 2.),
                .width = spr.src.width,
                .height = spr.src.height,
            },
            .pos = start_pos,
            .collided = false,
        },
        .damage = 10,
        .damage_timer = TimerInit(0.5, true),
        .attack_timer = TimerInit(2, false),
        .sustain_timer = TimerInit(4, false),
        .decay_timer = TimerInit(2., false),
        .sprite = spr,
        .state = LASER_STATE_DELAY,
        .delay = 2,
        .length = length,
    });
}

void RenderLaserRepeat(Laser *ar, i32 progress_step, Assets *a)
{
    assert(ar != NULL);
    for (int i = 0; i < progress_step; i++) {
        Vector2 pos = {
            .x = ar->start_position.x,
            .y = ar->start_position.y,
        };
        if (ar->left) {
            pos.x -= (i * ar->sprite.src.width);
        } else {
            pos.x += (i * ar->sprite.src.width);
        }
        DrawSprite(a->atlas, ar->sprite, pos);
    }
}

void DrawLaser(Laser *arr, Assets *a)
{
    assert(arr != NULL);
    for (int i= 0; i < MAX_LASER; i++) {
        Laser *temp = &g.laser[i];
        if (!temp->exist) continue;
        switch (temp->state) {
            case LASER_STATE_NONE:
                // Do nothing
                break;
            case LASER_STATE_DELAY: {
                if (g.debug_collision) {
                    DrawRectangleLines(
                        temp->start_position.x,
                        temp->start_position.y, 8,
                        8,
                        WHITE
                    );
                }
                break;
            }
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
                RenderLaserRepeat(temp, progress_step, a);
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

                    RenderLaserRepeat(temp, temp->length, a);
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
                    RenderLaserRepeat(temp, progress_step, a);
                }
                break;
        }

        if (g.debug_collision) {
            DrawCollisionBox(temp->collision);
        }
    }
}

void SpawnLaser(Camera2D *cam, i32 threshold)
{
    assert(cam != NULL);
    int spawnValue = GetRandomValue(0, 1000);
    if (spawnValue > threshold) return;
    int is_left = GetRandomValue(0, 1);
    f32 spawnPointY = GetRandomValue(cam->target.y - GAME_HEIGHT - 100, cam->target.y + GAME_HEIGHT);
    i32 length = GetRandomValue(1, 20);
    InsertWarning((Vector2) {
        .x = is_left ? 100 : -100,
        .y = spawnPointY,
    });
    InsertEnemyLaserSide(
        (Vector2) {
            .x = is_left ? 100 : -100,
            .y = spawnPointY,
        },
        length,
        is_left
    );
}

void UpdateLaserCollision(Laser *temp, i32 progress_step)
{
    assert(temp != NULL);
    temp->collision.pos.x = temp->left ? temp->start_position.x - temp->sprite.src.width * progress_step + temp->sprite.src.width
        : temp->start_position.x;
    temp->collision.pos.y = temp->start_position.y;
    temp->collision.box.width = temp->sprite.src.width * progress_step;
    temp->collision.box.height = temp->sprite.src.height;
}

// This should be an array
void UpdateLaser(Laser *arr)
{
    assert(arr != NULL);
    f32 delta = GetFrameTime();
    for (int i = 0; i < MAX_LASER; i++)
    {
        Laser *temp = &arr[i];
        if (!temp->exist) continue;
        switch (temp->state) {
            case LASER_STATE_NONE:
                // Do nothing
                break;
            case LASER_STATE_DELAY: {
                temp->delay -= delta;

                temp->collision.box.width = 0;
                temp->collision.box.height = 0;

                if (temp->delay < 0) temp->state = LASER_STATE_FIRING;
                break;
            }
            case LASER_STATE_FIRING: {
                TimerUpdate(&temp->attack_timer);

                f32 progress = TimeProgress(&temp->attack_timer);
                i32 progress_step = Lerp(temp->length, 1., progress);
                UpdateLaserCollision(temp, progress_step);

                if (TimerCompleted(&temp->attack_timer)) temp->state = LASER_STATE_SUSTAIN;
                break;
            }
            case LASER_STATE_SUSTAIN: {
                TimerUpdate(&temp->sustain_timer);

                UpdateLaserCollision(temp, temp->length);

                if (TimerCompleted(&temp->sustain_timer)) temp->state = LASER_STATE_DECAY;
            }
                break;
            case LASER_STATE_DECAY: {
                TimerUpdate(&temp->decay_timer);

                f32 progress = TimeProgress(&temp->decay_timer);
                i32 progress_step = Lerp(1., temp->length, progress);
                UpdateLaserCollision(temp, progress_step);
                break;
            }
        }
    }
}

void DespawnLaser(Laser *arr)
{
    assert(arr != NULL);

    for (int i = 0; i < MAX_LASER; i++)
    {
        Laser *temp = &arr[i];
        if (!temp->exist) continue;
        if (!TimerCompleted(&temp->decay_timer)) continue;
        __LOG("Despawning Laser [%d]", i);

        temp->exist = false;
    }
}
