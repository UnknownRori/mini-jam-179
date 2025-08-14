#define BUILD_PATH  "./build"
#define DIST_PATH   "./dist"
#define RAYLIB_SRC  "./raylib/src"

char* raylib_module[] = {
    "rcore",
    "raudio",
    "rglfw",
    "rmodels",
    "rshapes",
    "rtext",
    "rtextures",
    "utils",
};

char* minijam_module[] = {
    "assets",
    "audio",
    "bullet",
    "collision",
    "cursor",
    "enemy",
    "event",
    "game",
    "global_sprites",
    "item",
    "laser",
    "main",
    "obstacle",
    "parallax",
    "particle",
    "player",
    "resolution",
    "scene",
    "sprite",
    "timer",
    "ui",
    "utils",
    "wall",
    "scene/gameplay",
    "scene/help",
    "scene/main_menu",
    "scene/option",
};

int build_raylib();
int build_project();
int build_dist();

