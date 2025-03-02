#include "include/resolution.h"

Vector2 GetScreenSizeBasedResolution(Resolution res)
{
    switch (res) {
    case RESOLUTION_1366:
        return (Vector2) {1366, 768};
    case RESOLUTION_900:
        return (Vector2) {900, 506};
    case RESOLUTION_600:
        return (Vector2) {600, 338};
    }
}
