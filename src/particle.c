#include <raylib.h>
#include <raymath.h>
#include <assert.h>
#include <string.h>
#include "include/particle.h"
#include "include/game.h"
#include "include/logger.h"
#include "include/timer.h"
#include "include/types.h"
#include "include/utils.h"

void InsertAnimatedParticle(AnimatedParticle particle)
{
    for (int i = 0; i < MAX_PARTICLE; i++) {
        AnimatedParticle *temp = &g.anim_particle[i];
        if (temp->exist) continue;

        __LOG("Animated Particle spawn %d", i);
        *temp = particle;
        temp->exist = true;
        break;
    }
}

void DrawAnimatedParticle(AnimatedParticle *arr, Assets *a)
{
    assert(arr != NULL);
    assert(a != NULL);
    for (int i = 0; i < MAX_PARTICLE; i++) {
        AnimatedParticle *temp = &g.anim_particle[i];
        if (!temp->exist) continue;

        AnimatedSpriteDraw(a->atlas, &temp->sprite, temp->position);
    }
}

void UpdateAnimatedParticle(AnimatedParticle *arr)
{
    assert(arr != NULL);

    f32 delta = GetFrameTime();

    for (int i = 0; i < MAX_PARTICLE; i++) {
        AnimatedParticle *temp = &g.anim_particle[i];
        if (!temp->exist) continue;

        TimerUpdate(&temp->timeout);

        /*temp->velocity = Vector2Scale(temp->velocity, FRICTION);*/
        temp->position = Vector2Add(temp->position, Vector2Scale(temp->velocity, delta));
    }
}

void DespawnAnimatedParticle(AnimatedParticle *arr)
{
    for (int i = 0; i < MAX_PARTICLE; i++) {
        AnimatedParticle *temp = &g.anim_particle[i];
        if (!temp->exist) continue;

        if (temp->sprite.maxFrame < temp->sprite.frame || TimerCompleted(&temp->timeout)) {
            temp->exist = false;
            __LOG("Despawn Animated Particle %d", i);
        }
    }
}

void InsertParticle(Particle particle)
{
    for (int i = 0; i < MAX_PARTICLE; i++) {
        Particle *temp = &g.particle[i];
        if (temp->exist) continue;

        __LOG("Particle spawn %d", i);
        *temp = particle;
        temp->exist = true;
        break;
    }
}

void DrawParticle(Particle *arr, Assets *a)
{
    assert(arr != NULL);
    assert(a != NULL);
    for (int i = 0; i < MAX_PARTICLE; i++) {
        Particle *temp = &g.particle[i];
        if (!temp->exist) continue;

        DrawSprite(a->atlas, temp->sprite, temp->position);
    }
}

void UpdateParticle(Particle * arr)
{
    f32 delta = GetFrameTime();

    for (int i = 0; i < MAX_PARTICLE; i++) {
        Particle *temp = &g.particle[i];
        if (!temp->exist) continue;

        TimerUpdate(&temp->timeout);


        /*temp->velocity = Vector2Scale(temp->velocity, FRICTION);*/
        temp->position = Vector2Add(temp->position, Vector2Scale(temp->velocity, delta));
    }
}

void DespawnParticle(Particle *arr)
{
    assert(arr != NULL);
    for (int i = 0; i < MAX_PARTICLE; i++) {
        Particle *temp = &g.particle[i];
        if (!temp->exist) continue;

        if (TimerCompleted(&temp->timeout)) {
            temp->exist = false;
            __LOG("Despawn Particle %d", i);
        }
    }
}


void SpawnMediumExplosion(Vector2 position)
{
    InsertAnimatedParticle((AnimatedParticle) {
        .position = position,
        .velocity = VECTOR_ZERO,
        .timeout = TimerInit(3, false),
        .sprite = (AnimatedSprite) {
            .defaultFrameDelay = 1,
            .maxFrame = 4,
            .src = (Rectangle) {.x = 0, .y = 80, .width = 16, .height = 16},
            .scale = 1,
            .rotation = 0,
            .flipX = 0,
        },
    });
}
void SpawnSmallExplosion(Vector2 position)
{
    InsertAnimatedParticle((AnimatedParticle) {
        .position = position,
        .velocity = VECTOR_ZERO,
        .timeout = TimerInit(3, false),
        .sprite = (AnimatedSprite) {
            .defaultFrameDelay = 1,
            .maxFrame = 4,
            .src = (Rectangle) {.x = 0, .y = 96, .width = 8, .height = 8},
            .scale = 1,
            .rotation = 0,
            .flipX = 0,
        },
    });

}

void SpawnComet(Vector2 position, Vector2 velocity)
{
    InsertParticle((Particle) {
        .position = position,
        .velocity = velocity,
        .timeout = TimerInit(3, false),
        .sprite = (Sprite) {
            .src = (Rectangle) {.x = 8, .y = 112, .width = 8, .height = 39},
            .scale = 1,
            .rotation = 0,
            .flipX = 0,
        },
    });

}

void SpawnCometRandomly(i32 threshold)
{
    int spawnValue = GetRandomValue(0, 1000);
    if (spawnValue > threshold) return;

    int is_left = GetRandomValue(0, 1);
    Vector2 min, max;
    if (is_left) {
        min = (Vector2){
            .x = 10,
            .y = GAME_HEIGHT,
        };
        max = (Vector2){
            .x = 80,
            .y = GAME_HEIGHT,
        };

    } else {
        min = (Vector2){
            .x = 320,
            .y = GAME_HEIGHT,
        };
        max = (Vector2){
            .x = GAME_WIDTH - 30,
            .y = GAME_HEIGHT,
        };
    }
    Vector2 spawnPoint = GetRandomVector2(min, max);
    SpawnComet(spawnPoint, (Vector2) {
        .x = 0,
        .y = -GetRandomValue(100, 300)
    });
}
