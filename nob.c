#define NOB_IMPLEMENTATION
#include "./nob.h/nob.h"
#include <string.h>

#define BUILD_PATH "./build"
#define RAYLIB_SRC "./raylib/src"

int build_raylib();
int build_project();
int build_dist();

int main(int argc, char** argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    nob_mkdir_if_not_exists(BUILD_PATH);

    const char *program = nob_shift_args(&argc, &argv);
    if (argc <= 0) {
        const char* usage = nob_temp_sprintf("Usage %s <platform>", program);
        nob_log(NOB_INFO, usage);
    }

    const char *platform = nob_shift(argv, argc);

    Nob_Cmd cmd = {0};

    nob_log(NOB_INFO, "Starting Raylib Build");

    if (strcmp(platform, "desktop") == 0) {
        const char *cc = "./build/nob_desktop";
        nob_cmd_append(&cmd, NOB_REBUILD_URSELF(cc, "./src-build/nob_desktop.c"));
        if (!nob_cmd_run_sync(cmd)) return 1;

        cmd.count = 0;
        nob_cmd_append(&cmd, cc);
        if (!nob_cmd_run_sync(cmd)) return 1;
    }

    if (strcmp(platform, "web") == 0) {
        const char *cc = "./build/nob_web";
        nob_cmd_append(&cmd, NOB_REBUILD_URSELF(cc, "./src-build/nob_web.c"));
        if (!nob_cmd_run_sync(cmd)) return 1;

        cmd.count = 0;
        nob_cmd_append(&cmd, cc);
        if (!nob_cmd_run_sync(cmd)) return 1;
    }
    return 0;
}



