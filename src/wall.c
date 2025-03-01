#include <raylib.h>
#include <assert.h>
#include "include/wall.h"
#include "include/game.h"
#include "include/logger.h"


bool WallIntersectCollisionBox(Wall* w, CollisionBox* c)
{
    assert(w != NULL);
    assert(c != NULL);
    Rectangle w_rect = {
        .x = w->positionX,
        .y = 0,
        .width = w->depth,
        .height = w->depth,
    };
    Rectangle c_rect = {
        .x = c->pos.x,
        .y = 0,
        .width = c->box.width,
        .height = w->depth,
    };
    if (CheckCollisionRecs(w_rect, c_rect)) {
        return true;
    }
    return false;
}
