#include "include/assets.h"
#include "include/game.h"
#include <raylib.h>

void UnloadAssets(Assets *a)
{
    UnloadTexture(a->atlas);
    UnloadFont(a->font);
    UnloadRenderTexture(a->buffer);
    UnloadRenderTexture(a->light_mask);
    UnloadShader(a->lighting);

    for (int i = 0; i < MAX_SFX; i++) {
        UnloadSound(a->sfx[i]);
    }
    for (int i = 0; i < MAX_BGM; i++) {
        UnloadMusicStream(a->bgm[i]);
    }
}

void LoadAssets(Assets *a)
{
    a->background = LoadTexture("resources/background.png");
    SetTextureFilter(a->background, TEXTURE_FILTER_POINT);

    a->ui_slot = LoadTexture("resources/ui-slot.png");
    SetTextureFilter(a->ui_slot, TEXTURE_FILTER_POINT);

    a->atlas = LoadTexture("resources/atlas.png");
    SetTextureFilter(a->atlas, TEXTURE_FILTER_POINT);

    a->ui_dialog = LoadTexture("resources/ui-dialog.png");
    SetTextureFilter(a->ui_dialog, TEXTURE_FILTER_POINT);

    a->font = LoadFont("resources/PressStart2P-Regular.ttf");
    SetTextureFilter(a->font.texture, TEXTURE_FILTER_POINT);

    a->buffer = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(a->buffer.texture, TEXTURE_FILTER_POINT);

    a->light_mask = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(a->buffer.texture, TEXTURE_FILTER_POINT);

    a->lighting = LoadShader(0, "resources/lighting.fs");

    a->sfx[0] = LoadSound("resources/shoot.wav");
    a->sfx[1] = LoadSound("resources/enemy-shoot.wav");
    a->sfx[2] = LoadSound("resources/explosion.wav");
    a->sfx[3] = LoadSound("resources/hit-obstacle.wav");
    a->sfx[4] = LoadSound("resources/hit-player.wav");
    a->sfx[5] = LoadSound("resources/pickup.wav");
    a->sfx[6] = LoadSound("resources/hit-enemy.wav");
}
