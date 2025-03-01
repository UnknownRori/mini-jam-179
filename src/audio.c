#include <assert.h>
#include <raylib.h>
#include "include/audio.h"
#include "include/assets.h"
#include "include/game.h"
#include "include/logger.h"

float g_master = 0;
float g_sfx = 0;
float g_bgm = 0;

void AudioManagerSetMasterVolume(float master)
{
    g_master = master;
}
void AudioManagerSetSFXVolume(float sfx)
{
    g_sfx = sfx;
}
void AudioManagerSetBGMVolume(float bgm)
{
    g_bgm = bgm;
}
void AudioManagerPlayCompoundSFX(int id) {
    __ERROR("not implemented!");
    assert(false);
}
void AudioManagerPlaySFXRandomPitch(int id, int min, int max) {
    assert(MAX_SFX > id);
    float pitch = (float)(GetRandomValue(min, max)) / 10.;
    __LOG("%f", pitch);
    SetSoundPitch(a.sfx[id], pitch);
    SetSoundVolume(a.sfx[id], g_master * g_sfx);
    PlaySound(a.sfx[id]);
}
void AudioManagerPlaySFX(int id)
{
    assert(MAX_SFX > id);
    SetSoundPitch(a.sfx[id], 0);
    SetSoundVolume(a.sfx[id], g_master * g_sfx);
    PlaySound(a.sfx[id]);
}
void AudioManagerPlayMusic(int id) {
    assert(MAX_BGM > id);
    PlayMusicStream(a.bgm[id]);
}
