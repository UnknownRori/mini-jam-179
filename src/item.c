#include <raylib.h>
#include <raymath.h>
#include <assert.h>
#include <stdbool.h>
#include "include/item.h"
#include "include/audio.h"
#include "include/collision.h"
#include "include/logger.h"
#include "include/game.h"
#include "include/sprite.h"
#include "include/types.h"
#include "include/utils.h"

const Sprite HP_SPRITE = (Sprite) {
    .flipX = false,
    .rotation = 0,
    .scale = 1,
    .src = (Rectangle) {
        .x = 72,
        .y = 224,
        .width = 8,
        .height = 8,
    },
};

const Sprite ENERGY_SPRITE = (Sprite) {
    .flipX = false,
    .rotation = 0,
    .scale = 1.,
    .src = (Rectangle) {
        .x = 72,
        .y = 232,
        .width = 8,
        .height = 8,
    },
};

void DropRandomItem(Vector2 pos, i32 threshold)
{
    int spawnValue = GetRandomValue(0, 1000);
    if (spawnValue > threshold && g.player.power > 30 && g.player.hp > 30) return;
    f32 amount = GetRandomValue(50, 80);
    i32 type = GetRandomValue(1, 2);
    if (g.player.power < 30) type = ITEM_TYPE_ENERGY;
    if (g.player.hp < 30) type = ITEM_TYPE_HP;
    SpawnItem(pos, amount, type);
}

void SpawnItem(Vector2 pos, f32 amount, ItemType type)
{
    Item item = {0};
    item.amount = amount;
    item.type = type;
    item.position = pos;
    item.pickup = (CollisionBox) {
        .pos = pos,
        .box = (Rectangle) {
            .x = -4,
            .y = -4,
            .width = 8,
            .height = 8,
        },
    };
    item.follow = (CollisionBox) {
        .pos = pos,
        .box = (Rectangle) {
            .x = -4 * 6,
            .y = -4 * 6,
            .width = 8 * 6,
            .height = 8 * 6,
        },
    };

    InsertItem(item);
}

void InsertItem(Item item)
{
    for (int i = 0; i < MAX_ITEM; i++) {
        Item *temp = &g.item[i];
        if (temp->exist) continue;
        __LOG("Spawning Item %d", i);

        *temp = item;
        temp->exist = true;
        break;
    }
}

// Item* should be an array
void DrawItem(Item *arr, Assets *a)
{
    assert(arr != NULL);
    assert(a != NULL);

    for (int i = 0; i < MAX_ITEM; i++) {
        Item *temp = &g.item[i];
        if (!temp->exist) continue;

        Sprite spr;
        switch(temp->type) {
            case ITEM_TYPE_NONE:
                assert(false);
            case ITEM_TYPE_ENERGY:
                spr = ENERGY_SPRITE;
                break;
            case ITEM_TYPE_HP:
                spr = HP_SPRITE;
                break;
        }

        DrawSprite(a->atlas, spr, temp->position);

        if (g.debug_collision) {
            DrawCollisionBox(temp->pickup);
            DrawCollisionBox(temp->follow);
        }
    }
}

void UpdateItem(Item * arr)
{
    assert(arr != NULL);

    f32 delta = GetFrameTime();

    for (int i = 0; i < MAX_ITEM; i++) {
        Item *temp = &g.item[i];
        if (!temp->exist) continue;

        if (!CheckCollisionBox(temp->follow, g.player.collision)) continue;

        if (CheckCollisionBox(temp->pickup, g.player.collision)) {
            switch (temp->type) {
                case ITEM_TYPE_NONE:
                    // Do nothing
                    break;
                case ITEM_TYPE_ENERGY:
                    g.player.power = MAX(g.player.power + temp->amount, g.player.max_power);
                    break;
                case ITEM_TYPE_HP:
                    g.player.hp = MAX(g.player.hp + temp->amount, g.player.max_hp);
                    break;
            }
            AudioManagerPlaySFXRandomPitch(5, 8, 12);
            temp->exist = false;
            continue;
        }

        Vector2 dir = Vector2Subtract(g.player.position, temp->position);

        dir = Vector2Normalize(dir);
        dir = Vector2Scale(dir, ITEM_SPEED);
        dir = Vector2Scale(dir, delta);

        temp->position = Vector2Add(dir, temp->position);
        temp->pickup.pos = temp->position;
        temp->follow.pos = temp->position;
    }
}

// Item* should be an array
void DespawnItem(Item *arr, Camera2D *cam)
{
    assert(arr != NULL);
    assert(cam != NULL);

    for (int i = 0; i < MAX_ITEM; i++) {
        Item *temp = &g.item[i];
        if (!temp->exist) continue;
        if (temp->position.y > cam->target.y + GAME_HEIGHT * 4) {
        __LOG("Despawn item %d", i);
            temp->exist = false;
        }
    }
}
