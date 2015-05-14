#ifndef SOUND_H
#define SOUND_H

#include "libs.h"
#include "progopt.h"
#include "adplug/adplug.h"
#include "adplug/emuopl.h"
#include "Random.h"
#include "Timer.h"

namespace sound {

extern const int number_of_musics;
extern int music_number;

void fill_audio(void *udata, Uint8 *stream, int len);
bool LoadAdrib(const string& filename);
bool LoadNoSoundOption();

bool InitializeSound();
void CleanUpSound();

int PlayMusicRandom();
void PlayMusic(const int& music_number);
void StopMusic();
void FadeOutMusic();
void PauseMusic();
void ResumeMusic();

} // namespace sound

#endif // SOUND_H
