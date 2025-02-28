#include "include/assets.h"
#include "include/game.h"
#include <raylib.h>

void UnloadAssets(Assets *a)
{
    UnloadTexture(a->atlas);
    UnloadFont(a->font);
    UnloadRenderTexture(a->buffer);
}
void LoadAssets(Assets *a)
{
    a->background = LoadTexture("resources/background.png");
    SetTextureFilter(a->background, TEXTURE_FILTER_POINT);

    a->atlas = LoadTexture("resources/atlas.png");
    SetTextureFilter(a->atlas, TEXTURE_FILTER_POINT);

    a->font = LoadFont("resources/PressStart2P-Regular.ttf");
    SetTextureFilter(a->font.texture, TEXTURE_FILTER_POINT);

    a->buffer = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(a->buffer.texture, TEXTURE_FILTER_POINT);
}
