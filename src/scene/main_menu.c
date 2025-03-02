#include "main_menu.h"

void MainMenuInit()
{

}

void MainMenuUpdate()
{

}

void MainMenuRender()
{

}

void MainMenuDeinit()
{

}

Scene GetSceneMainMenu()
{
    return (Scene) {
        .init = MainMenuInit,
        .deinit = MainMenuDeinit,
        .update = MainMenuUpdate,
        .render = MainMenuRender,
    };
}
