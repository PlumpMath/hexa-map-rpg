#include "sound.h"

namespace sound {

vector<string>  music_filename;

const int       rate               = 22050;
const bool      bit16              = true;
const bool      stereo             = false;
const int       samples            = 512;
const int       number_of_musics   = 15;
int             music_number       = 0;

bool            is_no_sound        = true;
bool            is_music_started   = false;
bool            is_music_paused    = false;
int             volume             = SDL_MIX_MAXVOLUME;
Timer           fade_timer         = Timer();

short int*      buf                = 0;
int             buf_size           = samples * (1+bit16) * (1+stereo);
Uint8*          audio_chunk        = 0;
int             audio_chunk_size   = 0x1000000;
Uint32          audio_len          = 0;
Uint8*          audio_head         = 0;
Uint32          audio_remain       = 0;
Uint8*          audio_at           = 0;

bool LoadNoSoundOption() {
  ifstream f;
  string   config_item_key;
  cout << "Loading sound config data..." << endl;
  f.open(config_sound_path.c_str());
  f >> config_item_key >> is_no_sound;
  cout << config_item_key << " = " << is_no_sound << endl;
  f.close();
  return true;
}

bool InitializeSound() {
  LoadNoSoundOption();
  if (is_no_sound)
    return true;
  SDL_AudioSpec audio;
  audio.freq     = rate;
  audio.format   = bit16  ? AUDIO_S16 : AUDIO_S8;
  audio.channels = stereo ? 2 : 1;
  audio.samples  = buf_size;
  audio.callback = fill_audio;
  audio.userdata = NULL;
  buf = new short int[buf_size];
  audio_chunk = new Uint8[audio_chunk_size];
  if (SDL_OpenAudio(&audio, NULL) < 0) {
    cout << "[오류] 사운드 초기화 실패: " << SDL_GetError() << endl;
    return false;
  }
  return true;
}

void CleanUpSound() {
  if (is_no_sound)
    return;
  delete [] buf;
  delete [] audio_chunk;
  SDL_CloseAudio();
}

void fill_audio(void *udata, Uint8 *stream, int len) {
  if (is_no_sound)
    return;
  if (audio_remain == 0) {
    audio_remain = audio_len;
    audio_at = audio_head;
  }
  len = (len > (int)audio_remain ? audio_remain : len);
  SDL_MixAudio(stream, audio_at, len, volume);
  audio_at += len;
  audio_remain -= len;
}

bool LoadAdrib(const string& filename) {
  if (is_no_sound)
    return true;
  CEmuopl       opl(rate, bit16, stereo);
  CPlayer*      p = CAdPlug::factory(filename.c_str(), &opl);
  short         buf[buf_size];
  unsigned long	towrite;
  unsigned long write;

  if (!p) {
    cerr << "애드립 파일을 열 수 없습니다 : " << filename << endl;
    return false;
  }
  audio_len = 0;
  while (p->update()) {
    for (towrite = rate / p->getrefresh(); towrite; towrite -= write) {
      write = ((int)towrite > buf_size ? buf_size : towrite);
      opl.update(buf, write);
      memcpy(&(audio_chunk[audio_len]), buf, write*2);
      audio_len += write*2;
    }
  }
  audio_head = audio_chunk;
  audio_at = audio_head;
  audio_remain = audio_len;
  return true;
}

int PlayMusicRandom() {
  if (is_no_sound)
    return -1;
  music_number = Random()%number_of_musics;
  PlayMusic(music_number);
  return music_number;
}

void PlayMusic(const int& music_number) {
  if (is_no_sound)
    return;
  if (number_of_musics <= music_number)
    return;
  if (is_music_started)
    StopMusic();
  SDL_LockAudio();
  LoadAdrib(music_filename[music_number]);
//  cout << "The size of music " << music_number << " : " << audio_len/1024
//    << endl;
  SDL_UnlockAudio();
  SDL_PauseAudio(0);
  is_music_started = true;
  is_music_paused = false;
}

void FadeOutMusic() {
  if (is_no_sound)
    return;
  if (!is_music_started)
    return;
  volume = SDL_MIX_MAXVOLUME;
  fade_timer.Start();
  while (volume>4) {
    if(fade_timer.GetTicks() >= 20) {
      volume *= 0.97;
      fade_timer.Start();
    }
  }
  fade_timer.Stop();
  SDL_PauseAudio(1);
  is_music_started = false;
  volume = SDL_MIX_MAXVOLUME;
}

void StopMusic() {
  if (is_no_sound)
    return;
  if (!is_music_started)
    return;
  SDL_PauseAudio(1);
  is_music_started = false;
}

void PauseMusic() {
  if (is_no_sound)
    return;
  if (!is_music_started)
    return;
  if (is_music_paused)
    return;
  SDL_PauseAudio(1);
  is_music_paused = true;
}

void ResumeMusic() {
  if (is_no_sound)
    return;
  if (!is_music_started)
    return;
  if (!is_music_paused)
    return;
  SDL_PauseAudio(0);
  is_music_paused = false;
}

} // namespace sound
