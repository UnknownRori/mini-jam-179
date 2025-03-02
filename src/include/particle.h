#pragma once

#ifndef PARTICLE_H
#define PARTICLE_H

#include <raylib.h>
#include <stdbool.h>
#include "sprite.h"
#include "assets.h"
#include "timer.h"

typedef struct AnimatedParticle {
    Vector2 position;
    Vector2 velocity;
    Timer timeout;

    AnimatedSprite sprite;

    bool exist;
} AnimatedParticle;

void InsertAnimatedParticle(AnimatedParticle);

void DrawAnimatedParticle(AnimatedParticle *, Assets *);

void UpdateAnimatedParticle(AnimatedParticle *);

void DespawnAnimatedParticle(AnimatedParticle *);


void SpawnMediumExplosion(Vector2 position);
void SpawnSmallExplosion(Vector2 position);

typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    Timer timeout;

    Sprite sprite;

    bool exist;
} Particle;

void InsertParticle(Particle);

void DrawParticle(Particle *, Assets *);

void UpdateParticle(Particle *);

void DespawnParticle(Particle *);

void SpawnCometRandomly(i32 threshold);
void SpawnComet(Vector2 position, Vector2 velocity);

#endif
