#pragma once

#ifndef ASSETS_H
#define ASSETS_H

#include <raylib.h>

typedef struct Assets {
    Texture2D atlas;
    Texture2D background;
    Texture2D ui_slot;
    Font font;

    RenderTexture2D buffer;
} Assets;

void UnloadAssets(Assets*);
void LoadAssets(Assets*);

#endif
