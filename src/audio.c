#include <assert.h>
#include <raylib.h>
#include "include/audio.h"
#include "include/assets.h"
#include "include/game.h"
#include "include/logger.h"

float g_master = 0;
float g_sfx = 0;
float g_bgm = 0;

i32 current_music = 0;

float AudioManagerGetMasterVolume()
{
    return g_master;
}
float AudioManagerGetSFXVolume()
{
    return g_sfx;
}
float AudioManagerGetBGMVolume()
{
    return g_bgm;
}

void AudioManagerSetMasterVolume(float master)
{
    g_master = master;
    SetMusicVolume(a.bgm[current_music], g_master * g_bgm);
}
void AudioManagerSetSFXVolume(float sfx)
{
    g_sfx = sfx;
}
void AudioManagerSetBGMVolume(float bgm)
{
    g_bgm = bgm;
    SetMusicVolume(a.bgm[current_music], g_master * g_bgm);
}
void AudioManagerPlayCompoundSFX(int id) {
    __ERROR("not implemented!");
    assert(false);
}
void AudioManagerPlaySFXRandomPitch(int id, int min, int max) {
    assert(MAX_SFX > id);
    float pitch = (float)(GetRandomValue(min, max)) / 10.;
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

void AudioManagerStopMusic() {
    StopMusicStream(a.bgm[current_music]);
}

void AudioManagerUpdateMusic()
{
    UpdateMusicStream(a.bgm[current_music]);
}

void AudioManagerPlayMusic(int id) {
    assert(MAX_BGM > id);
    StopMusicStream(a.bgm[current_music]);
    current_music = id;
    SetMusicVolume(a.bgm[id], g_master * g_bgm);
    PlayMusicStream(a.bgm[id]);
}
bool AudioManagerIsPlayingSFX(int id) {
    assert(MAX_SFX > id);
    IsSoundPlaying(a.sfx[id]);
}
