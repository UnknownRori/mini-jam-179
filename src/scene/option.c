#include "option.h"

void OptionInit()
{

}

void OptionUpdate()
{

}

void OptionRender()
{

}

void OptionDeinit()
{

}

Scene GetSceneOption()
{
    return (Scene) {
        .init = OptionInit,
        .deinit = OptionDeinit,
        .update = OptionUpdate,
        .render = OptionRender,
    };
}
