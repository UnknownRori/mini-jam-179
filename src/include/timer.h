#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include "../include/types.h"

typedef struct {
    f32 m_remaining;
    f32 m_lifetime;
    bool m_repeating;
    bool m_paused;
    bool m_completed;
    bool m_previously_completed;
} Timer;

void TimerReset(Timer *time);
void TimerUpdate(Timer *time);
bool TimerCompleted(const Timer *time);
f32 TimeProgress(const Timer *time);
Timer TimerInit(float lifetime, bool repeating);
bool IsTimerDone(const Timer *time);

#endif
