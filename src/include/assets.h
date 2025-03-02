#pragma once

#ifndef ASSETS_H
#define ASSETS_H

#include <raylib.h>

#define MAX_SFX 8
#define MAX_BGM 2

typedef struct Assets {
    Texture2D atlas;
    Texture2D background;
    Texture2D ui_slot;
    Font font;

    RenderTexture2D buffer;
    RenderTexture2D light_mask;

    Shader lighting;

    Sound sfx[MAX_SFX];
    Music bgm[MAX_BGM];
} Assets;

void UnloadAssets(Assets*);
void LoadAssets(Assets*);

#endif
