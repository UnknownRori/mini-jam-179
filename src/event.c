#include <assert.h>
#include <string.h>
#include "include/event.h"
#include "include/logger.h"
#include "include/types.h"

i32 event_index = 0;
EventType event_buffer[EVENT_BUFFER_SIZE] = {0};

void ResetEventBuffer()
{
    event_index = EVENT_BUFFER_SIZE - 1;
    memset(event_buffer, 0, EVENT_BUFFER_SIZE * sizeof(EventType));
}
void PushEvent(EventType event)
{
    assert(EVENT_BUFFER_SIZE > event_index);
    event_buffer[event_index] = event;
    event_index += 1;
}
EventType GetEvent()
{
    return event_buffer[event_index - 1];
}
void PopEvent()
{
    assert(event_index > 0);
    event_index -= 1;
    event_buffer[event_index] = EVENT_NONE;
}
