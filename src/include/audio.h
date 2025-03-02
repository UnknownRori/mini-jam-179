#pragma once

#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>

#ifndef MAX_COMPOUND
#define MAX_COMPOUND 4
#endif

typedef struct CompoundAudio
{
    Sound *audio[MAX_COMPOUND];
} CompoundAudio;

void AudioManagerSetMasterVolume(float);
void AudioManagerSetSFXVolume(float);
void AudioManagerSetBGMVolume(float);

float AudioManagerGetMasterVolume();
float AudioManagerGetSFXVolume();
float AudioManagerGetBGMVolume();

void AudioManagerPlayCompoundSFX(int id);
void AudioManagerPlaySFXRandomPitch(int id, int min, int max);
void AudioManagerPlaySFX(int id);
bool AudioManagerIsPlayingSFX(int id);
void AudioManagerPlayMusic(int id);

#endif
