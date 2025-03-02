#pragma once

#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <raylib.h>

typedef enum Resolution {
    RESOLUTION_1366,
    RESOLUTION_900,
    RESOLUTION_600,
} Resolution;

Vector2 GetScreenSizeBasedResolution(Resolution);

#endif

