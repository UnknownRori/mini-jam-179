#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include "include/scene.h"
#include "include/game.h"
#include "include/logger.h"

static Timer s_timeToChange = {0};
static u32 s_activeScene = 0;
static u32 s_nextScene = 0;
static SceneChangeType s_sceneChanging = SCENE_CHANGE_NONE;
static Scene s_scenePtr[MAX_SCENE] = {0};
static SceneChangeTransitionFunction s_transitionFunction = {0};

void SceneInit(Timer timeChange)
{
    s_timeToChange = timeChange;
}

void SceneChangeTransition(SceneChangeTransitionFunction func)
{
    s_transitionFunction = func;
}
// Change the scene using transition
void SceneChange(int index)
{
    Clamp(index, 0, MAX_SCENE);
    TimerReset(&s_timeToChange);
    s_sceneChanging = SCENE_CHANGE_FORWARD;
    s_nextScene = index;
}
// Change the scene directly
void SceneSwap(int index)
{
    Clamp(index, 0, MAX_SCENE);
    s_scenePtr[s_activeScene].deinit();
    s_activeScene = index;
    s_scenePtr[s_activeScene].init();
}

void SceneAdd(int index, Scene scene)
{
    Clamp(index, 0, MAX_SCENE);
    s_scenePtr[index] = scene;
}
void SceneUpdate(void)
{
    if (s_sceneChanging) {
        TimerUpdate(&s_timeToChange);
        if (TimerCompleted(&s_timeToChange) && s_sceneChanging == SCENE_CHANGE_FORWARD) {
            s_scenePtr[s_activeScene].deinit();
            s_activeScene = s_nextScene;
            s_scenePtr[s_activeScene].init();
            s_sceneChanging = SCENE_CHANGE_BACKWARD;
            TimerReset(&s_timeToChange);
        }
        if (TimerCompleted(&s_timeToChange) && s_sceneChanging == SCENE_CHANGE_BACKWARD) {
            s_sceneChanging = SCENE_CHANGE_NONE;
            TimerReset(&s_timeToChange);
        }
        return;
    }

    (s_scenePtr[s_activeScene].update)();
}
void SceneDraw(void)
{
    (s_scenePtr[s_activeScene].render)();
    if (s_sceneChanging)  s_transitionFunction(s_timeToChange, s_sceneChanging);
}

void SceneDefaultTransition(Timer timeToChange, SceneChangeType sceneChanging)
{
    f32 progress = 0.;
    int numSteps = 10;
    if (sceneChanging == SCENE_CHANGE_FORWARD) progress = 1. - TimeProgress(&timeToChange);
    if (sceneChanging == SCENE_CHANGE_BACKWARD) progress = TimeProgress(&timeToChange);
    f32 stepHeight = (f32)GAME_WIDTH / numSteps;

    f32 filledHeight = (int)(progress * numSteps) * stepHeight;

    BeginTextureMode(a.buffer);
        DrawRectangle(0, 0, GAME_WIDTH, filledHeight, (Color) {178, 156, 151, 255});
    EndTextureMode();
}
