#include <raylib.h>
#include "include/timer.h"

void TimerReset(Timer *time)
{
    time->m_remaining = time->m_lifetime;
    time->m_completed = false;
    time->m_previously_completed = false;
}

void TimerUpdate(Timer *time)
{
    if (time->m_paused) return;
    time->m_previously_completed = time->m_completed;
    if (time->m_completed && time->m_repeating) TimerReset(time);
    if(!time->m_repeating) time->m_completed = false;
    time->m_remaining -= GetFrameTime();
    if (time->m_remaining <= 0) time->m_completed = true;
}

bool TimerCompleted(const Timer *time)
{
    return time->m_completed;
}

Timer TimerInit(float lifetime, bool repeating)
{
    return (Timer){
        .m_remaining = lifetime,
        .m_lifetime = lifetime,
        .m_repeating = repeating,
        .m_completed = false,
        .m_previously_completed = false,
        .m_paused = false,
    };
}

bool IsTimerDone(const Timer *time)
{
    return time->m_lifetime > 0.;
}

f32 TimeProgress(const Timer *time)
{
    return (time->m_remaining / time->m_lifetime);
}
