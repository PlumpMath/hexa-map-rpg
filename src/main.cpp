#include "libs.h"
#include <time.h>
#include "video.h"
#include "Sound.h"
#include "Random.h"
#include "WorldStage.h"
#include "LocalStage.h"
#include "DataManager.h"

using namespace std;
using namespace video;
using namespace draw;
using namespace sound;

bool InitializeEverything() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    cerr << "[오류] SDL 초기화에 실패했습니다." << endl;
    return false;
  }
  SDL_WM_SetCaption("정육각형 타일맵", NULL);
  if (!InitializeVideo()) {
    cerr << "[오류] 그래픽 초기화에 실패했습니다." << endl;
    return false;
  }
  InitializeFrames();
  InitializeSound();
  InitializeRandom();
  const int key_delay = 160;
  const int key_interval = 90;
  SDL_EnableKeyRepeat(key_delay, key_interval);
  SDL_EnableUNICODE(SDL_ENABLE);
  LoadObjectTemplate();
  LoadTerrainTemplate();
  LoadSightMask();
  return true;
}

bool CleanUpEverything() {
  StopMusic();
  CleanUpSound();
  CleanUpVideo();
  SDL_Quit();
  return true;
}

int main(int argc, char** args) {
  if (!InitializeEverything())
    return 1;
  if (!(Refresh())) {
    cerr << "[오류] 화면 갱신에 실패했습니다." << endl;
    return 1;
  }
  DrawBackground();
  Refresh();

  WorldStage world;
  world.Prepare();
  world.Run();

  CleanUpEverything();
  return 0;
}
