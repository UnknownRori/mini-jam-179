#include "include/collision.h"
#include <raylib.h>

void DrawCollisionBox(CollisionBox c)
{
    DrawRectangleLines(c.pos.x + c.box.x, c.pos.y + c.box.y, c.box.width, c.box.height, BLUE);
}

bool CheckCollisionBox(CollisionBox a, CollisionBox b)
{
    Rectangle a_rect = a.box;
    a_rect.x += a.pos.x;
    a_rect.y += a.pos.y;
    Rectangle b_rect = b.box;
    b_rect.x += b.pos.x;
    b_rect.y += b.pos.y;

    return CheckCollisionRecs(a_rect, b_rect);
}
