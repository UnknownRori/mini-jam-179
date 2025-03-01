#pragma once

#ifndef LASER_H
#define LASER_H

#include <raylib.h>
#include <stdbool.h>
#include "types.h"
#include "sprite.h"
#include "bullet.h"
#include "collision.h"
#include "timer.h"
#include "assets.h"

typedef enum LaserStateMachine {
    LASER_STATE_NONE,
    LASER_STATE_DELAY,
    LASER_STATE_FIRING,
    LASER_STATE_SUSTAIN,
    LASER_STATE_DECAY,
} LaserStateMachine;

typedef struct Laser {
    // go negative if you want other direction
    i32 length;
    Vector2 start_position;
    CollisionBox collision;
    Sprite sprite;

    f32 damage;
    f32 delay;
    f32 attack_time;
    f32 sustain_time;
    f32 decay_time;
    Timer damage_timer;

    LaserStateMachine state;
    bool exist;
} Laser;

void InsertEnemyLaserSide(Vector2 start_pos, i32 length);
void InsertLaser(Laser);
void DrawLaser(Laser *, Assets *);
// This should be an array
void UpdateLaser(Laser *);
void DespawnLaser(Laser *);

#endif
