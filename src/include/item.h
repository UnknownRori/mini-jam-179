#pragma once

#ifndef ITEM_H
#define ITEM_H

#include <raylib.h>
#include "types.h"
#include "collision.h"
#include "assets.h"

typedef enum ItemType {
    ITEM_TYPE_NONE,
    ITEM_TYPE_ENERGY,
    ITEM_TYPE_HP,
} ItemType;

typedef struct Item {
    Vector2 position;
    Vector2 velocity;

    CollisionBox pickup;
    CollisionBox follow;

    ItemType type;
    f32 amount;
    bool exist;
} Item;

void InsertItem(Item);
void SpawnItem(Vector2, f32, ItemType);
void DropRandomItem(Vector2, i32);
// Item* should be an array
void DrawItem(Item *, Assets *);
// Item* should be an array
void UpdateItem(Item *);
// Item* should be an array
void DespawnItem(Item *, Camera2D *);

#endif
