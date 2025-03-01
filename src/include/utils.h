#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (y) : (x))

#define VECTOR_ZERO (Vector2) {0, 0}

Vector2 GetMousePositionScaled();
Vector2 GetRandomVector2(Vector2 min, Vector2 max);
#endif
