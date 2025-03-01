#include <raylib.h>
#include <raymath.h>
#include "include/collision.h"
#include "include/game.h"
#include "include/player.h"
#include "include/logger.h"
#include "include/sprite.h"
#include "include/types.h"
#include "include/wall.h"

void PlayerInit(Player* p)
{
    p->hp = 5;
    p->power = 5;
    p->speed = PLAYER_SPEED;
    p->position = (Vector2) {
        .x = 0,
        .y = 0,
    };
    p->collision.pos = p->position;
    p->collision.box = (Rectangle) {
        .x = -7,
        .y = -7,
        .width = 14,
        .height = 14,
    };
    p->turret = (Sprite){
        .flipX = false,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 0,
            .y = 0,
            .width = 16,
            .height = 16,
        },
    };
    p->core = (Sprite){
        .flipX = false,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 16,
            .y = 0,
            .width = 16,
            .height = 16,
        },
    };
}
void DrawPlayer(Player* p, Assets *a, Vector2 mouse)
{
    if (g.debug_collision) {
        DrawCollisionBox(p->collision);
    }
    DrawSprite(a->atlas, p->core, p->position);

    DrawSprite(a->atlas, p->turret, p->position);

    // AIM
    Vector2 dir = Vector2Subtract(mouse, dir);
    DrawLineV(p->position, dir, (Color) {116, 79, 70, 255});
}


void UpdatePlayer(Player* p, Vector2 mouse)
{
    // Movement
    f32 delta = GetFrameTime();
    Vector2 dir = Vector2Subtract(p->position, mouse);
    f32 angle = atan2(dir.y, dir.x) * RAD2DEG;
    angle += 90;

    p->turret.rotation = angle;
    p->collision.pos = p->position;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 dir_norm = Vector2Normalize(dir);
        p->vel = Vector2Add(p->vel, Vector2Scale(dir_norm, p->speed));
    }


    // Collision
    if (WallIntersectCollisionBox(&g.wall_left, &p->collision) && !p->collided) {
        p->vel.x = -p->vel.x;
        p->collided = true;
    } else {
        p->collided = false;
    }
    if (WallIntersectCollisionBox(&g.wall_right, &p->collision)&& !p->collided) {
        p->vel.x = -p->vel.x;
        p->collided = true;
    } else {
        p->collided = false;
    }

    // Apply velocity
    p->vel = Vector2Scale(p->vel, 0.95);
    p->vel.y -= GRAVITY * delta;
    p->position = Vector2Add(p->position, Vector2Scale(p->vel, delta));
}
