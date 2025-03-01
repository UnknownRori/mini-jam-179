#include <raylib.h>
#include <raymath.h>
#include "include/utils.h"
#include "include/game.h"

Vector2 GetMousePositionScaled()
{
    Vector2 mouseScreen = GetMousePosition();
    Vector2 mouseGame = {
        mouseScreen.x * GAME_WIDTH / SCREEN_WIDTH,
        mouseScreen.y * GAME_HEIGHT / SCREEN_HEIGHT
    };
    return mouseGame;
}

Vector2 GetRandomVector2(Vector2 min, Vector2 max)
{
    return (Vector2) {
        .x = GetRandomValue(min.x, max.x),
        .y = GetRandomValue(min.y, max.y),
    };
}

void CameraShake(Camera2D *c, f32* shakeness, f32 recover)
{
    f32 shake = *shakeness;
    c->target = Vector2Add((Vector2) {
        .x = GetRandomValue(-shake * 10, shake * 10) / 10.,
        .y = GetRandomValue(-shake * 10, shake * 10) / 10.,
    }, c->target);
    *shakeness -= recover;
    *shakeness = MAX(0.f, *shakeness);
}
