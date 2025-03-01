#include "include/utils.h"
#include "include/game.h"
#include <raylib.h>

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
