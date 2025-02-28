#include "include/collision.h"

void DrawCollisionBox(CollisionBox c)
{
    DrawRectangleLines(c.pos.x + c.box.x, c.pos.y + c.box.y, c.box.width, c.box.height, BLUE);
}
