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
