#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>

#define EVENT_BUFFER_SIZE 20

typedef enum EventType {
    EVENT_NONE,
    EVENT_HP_DECREASE,
    EVENT_ENERGY_DECREASE,
} EventType;


extern EventType event_buffer[EVENT_BUFFER_SIZE];

void ResetEventBuffer();
void PushEvent(EventType);
EventType GetEvent();
void PopEvent();

#endif
