#ifndef WORLDSTAGE_H
#define WORLDSTAGE_H

#include "libs.h"
#include "types.h"
#include "Draw.h"
#include "Sound.h"
#include "LocalStage.h"
#include "WorldPlace.h"
#include "TextFrame.h"
#include "Dialog.h"
#include "StringScanner.h"
#include "Time.h"

class WorldStage {
private:
  WorldPlace place;
  WorldPlace revealed_place;
  HexPos camera_pos;

  bool quit;

  string player_name;
  HexPos player_pos;

  LocalStage local;

public:
  WorldStage();
  virtual ~WorldStage();

public:

// 출력 관련 함수
  void DrawPlace();
  void SetCameraPosToPlayer();
  void SetCameraPos(const Coord& pos);
  void CopyRevealedCell(const HexPos& target_pos);
  void UpdateRevealedPlace();
  void RevealRevealedPlace();
  void ConcealRevealedPlace();
  void UpdateStatusFrame();
  void Draw();

// 사용자 관련 함수
  void PlayerActMove(const HexDir& dir);
  void PlayerActWait();
  void TestEventDialog();

// 게임 루프
  void Prepare();
  void Run();
  void ProcessUserInput();
};

#endif // WORLDSTAGE_H
