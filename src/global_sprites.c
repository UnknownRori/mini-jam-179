#include "include/obstacle.h"
#include "include/global_sprites.h"

const Sprite CURSOR_SPRITE = {
    .rotation = 0,
    .scale = 1,
    .flipX = 0,
    .src = (Rectangle) {
        .x = 64,
        .y = 224,
        .width = 8,
        .height = 8,
    }
};

const Sprite PLAYER_SPRITE = {
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
const Sprite PLAYER_TURRET_SPRITE = {
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
const Sprite ROBOT_SPRITE = {
        .flipX = 0,
        .rotation = 0,
        .scale = 1.,
        .src = (Rectangle) {
            .x = 0,
            .y = 16,
            .width = 16,
            .height = 16,
        }
    };

const Sprite PLAYER_BULLET_SPRITE = {
        .flipX = false,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 0,
            .y = 104,
            .width = 8,
            .height = 8,
        },
    };
const Sprite ENEMY_BULLET_SPRITE = {
        .flipX = false,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 8,
            .y = 104,
            .width = 8,
            .height = 8,
        },
    };
const Sprite SIDE_LASER_SPRITE = {
        .flipX = false,
        .src = {
            .x = 0,
            .y = 112,
            .width = 8,
            .height = 40,
        },
        .scale = 1,
        .rotation = 0,
    };

const Sprite OBSTACLE_SPRITE = {
        .flipX = 0,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 8,
            .y = 56,
            .width = OBSTACLE_WIDTH,
            .height = OBSTACLE_HEIGHT,
        },
    };
const Sprite OBSTACLE_END_SPRITE = {
        .flipX = 0,
        .rotation = 0,
        .scale = 1,
        .src = (Rectangle) {
            .x = 16,
            .y = 56,
            .width = OBSTACLE_WIDTH,
            .height = OBSTACLE_HEIGHT,
        },
    };


const Sprite HP_ITEM_SPRITE = {
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
const Sprite HP_SPRITE;

const Sprite ENERGY_ITEM_SPRITE = {
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
const Sprite ENERGY_SPRITE;
