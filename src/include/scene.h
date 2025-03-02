#pragma once

#ifndef SCENE_H

#include "timer.h"

typedef enum
{
    SCENE_CHANGE_NONE,
    SCENE_CHANGE_FORWARD,
    SCENE_CHANGE_BACKWARD
} SceneChangeType;

typedef void (*SceneFunction)(void);
typedef void (*SceneChangeTransitionFunction)(Timer, SceneChangeType);

typedef struct Scene
{
    SceneFunction init;
    SceneFunction render;
    SceneFunction update;
    SceneFunction deinit;
} Scene;
void SceneInit(Timer timeChange);
void SceneDefaultTransition(Timer, SceneChangeType);
void SceneChangeTransition(SceneChangeTransitionFunction);
// Change the scene using transition
void SceneChange(int index);
// Change the scene directly
void SceneSwap(int index);
void SceneAdd(int, Scene);
void SceneUpdate(void);
void SceneDraw(void);

#endif
