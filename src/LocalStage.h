#ifndef LOCALSTAGE_H
#define LOCALSTAGE_H

#include "libs.h"
#include "types.h"
#include "LocalPlace.h"
#include "CreatureVector.h"
#include "Draw.h"
#include "Sound.h"
#include "TextFrame.h"
#include "Dialog.h"
#include "StringScanner.h"
#include "Time.h"

class LocalStage {
  friend class Creature;

private:
  LocalPlace place;
  LocalPlace revealed_place;
  HexPos camera_pos;
  CreatureVector crets;

  bool quit;

  string player_name;
  int    player_id;
  int    ai_distance_limit;
  int    ai_distance_slow;

public:
  LocalStage();
  virtual ~LocalStage();

public:

// 출력 관련 함수
  int GetSideLevel(Coord& pos) const;
  void DrawPlace();
  void DrawMinimap();
  void DrawDialogMap();
  void SetCameraPosToPlayer();
  void SetCameraPos(const Coord& pos);
  void UpdateRevealedPlace();
  void RevealRevealedPlace();
  void ConcealRevealedPlace();
  void UpdateStatusFrame();
  void Draw();
  void TestStringScanner();

// 크리쳐 행동 관련 함수
  void FlowTick();
  void ProcessCreatures();
  void ProcessCreatureAct(const int& id);
  void PlayerActMove(const HexDir& dir);
  void PlayerActWait();

// 사용자 관련 함수
  void UserShowDialogMap();
  void TestEventDialog();

// 게임 루프
  void Prepare();
  void Run();
  void ProcessUserInput();
};

#endif // LOCALSTAGE_H
