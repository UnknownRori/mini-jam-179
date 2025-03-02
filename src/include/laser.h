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
    Timer attack_timer;
    Timer sustain_timer;
    Timer decay_timer;
    Timer damage_timer;

    LaserStateMachine state;
    bool left;
    bool exist;
} Laser;

void InsertEnemyLaserSide(Vector2 start_pos, i32 length, bool left);
void InsertLaser(Laser);
void DrawLaser(Laser *, Assets *);
void DrawLaserLightMask(Laser *);
// This should be an array
void SpawnLaser(Camera2D *, i32);
// This should be an array
void UpdateLaser(Laser *);
// This should be an array
void DespawnLaser(Laser *);

#endif
