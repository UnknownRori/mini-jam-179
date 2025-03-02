#include "help.h"

void HelpInit()
{

}

void HelpUpdate()
{

}

void HelpRender()
{

}

void HelpDeinit()
{

}

Scene GetSceneHelp()
{
    return (Scene) {
        .init = HelpInit,
        .deinit = HelpDeinit,
        .update = HelpUpdate,
        .render = HelpRender,
    };
}
