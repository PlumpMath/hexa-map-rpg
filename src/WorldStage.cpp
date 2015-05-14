#include "WorldStage.h"

using namespace draw;
using namespace sound;
using namespace rule;

// 생성자 및 소멸자
WorldStage::WorldStage()
    : place(256, 256),
      revealed_place(256, 256),
      camera_pos(0, 0),
      quit(false),
      player_name("주인공"),
      player_pos(0, 0) {
}

WorldStage::~WorldStage() {
}

void WorldStage::CopyRevealedCell(const HexPos& target_pos) {
  if (revealed_place.IsOutOfRange(target_pos))
    return;
  revealed_place.SetTerrain(target_pos, place.GetTerrain(target_pos));
  revealed_place.SetTerrainName(target_pos, place.GetTerrainName(target_pos));
  revealed_place.SetObject(target_pos, place.GetObject(target_pos));
  revealed_place.SetObjectName(target_pos, place.GetObjectName(target_pos));
}

void WorldStage::UpdateRevealedPlace() {
  HexPos target_pos;
  target_pos = player_pos;
  target_pos.MoveTo(HexDir::nwest);
  CopyRevealedCell(target_pos);
  target_pos = player_pos;
  target_pos.MoveTo(HexDir::neast);
  CopyRevealedCell(target_pos);
  target_pos = player_pos;
  target_pos.MoveTo(HexDir::west);
  CopyRevealedCell(target_pos);
  target_pos = player_pos;
  target_pos.MoveTo(HexDir::east);
  CopyRevealedCell(target_pos);
  target_pos = player_pos;
  target_pos.MoveTo(HexDir::swest);
  CopyRevealedCell(target_pos);
  target_pos = player_pos;
  target_pos.MoveTo(HexDir::seast);
  CopyRevealedCell(target_pos);
  CopyRevealedCell(player_pos);
}

void WorldStage::RevealRevealedPlace() {
  HexPos pos;
  for (int y = 0; y<place.GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x<place.GetCols(); ++x) {
      pos.set_x(x);
      revealed_place.SetHeight(pos, place.GetHeight(pos));
      revealed_place.SetTerrain(pos, place.GetTerrain(pos));
      revealed_place.SetObject(pos, place.GetObject(pos));
    }
  }
}

void WorldStage::ConcealRevealedPlace() {
  HexPos pos;
  for (int y = 0; y<place.GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x<place.GetCols(); ++x) {
      pos.set_x(x);
      revealed_place.SetTerrain(pos, WorldTerrainType::none);
      revealed_place.SetObject(pos, WorldObjectType::none);
    }
  }
}

void WorldStage::SetCameraPos(const Coord& pos) {
  camera_pos = pos;
}


//const bool WorldStage::Load(const string& filename) {
//    Clear();
//
//    ifstream f(filename.c_str(), ios_base::in | ios_base::binary);
//    if (!f.is_open()) {
//        cerr << filename.c_str() << " 파일을 읽을 수 없습니다." << endl;
//    }
//
//    f.read((char*)&cols, sizeof(cols));
//    f.read((char*)&rows, sizeof(rows));
//
//    int terrain = -1;
//    int wall = -1;
//    int object_id = -1;
//
//    for (int y = 0; y < rows; ++y) {
//        for (int x = 0; x < cols; ++x) {
//            f.read((char*)&terrainType, sizeof(terrainType));
//            f.read((char*)&terrainTile.set, sizeof(terrainTile.set));
//            f.read((char*)&terrainTile.id, sizeof(terrainTile.id));
//            f.read((char*)&wallType, sizeof(terrainType));
//            f.read((char*)&wallTile.set, sizeof(terrainTile.set));
//            f.read((char*)&wallTile.id, sizeof(terrainTile.id));
//            f.read((char*)&object_id, sizeof(object_id));
//            cells.push_back(new LocalPlaceCell(terrainType, terrainTile, wallType, wallTile, object_id));
//        }
//    }
//    f.close();
//    return true;
//}
//const bool WorldStage::Save(const string& filename) {
//    ofstream f(filename.c_str(), ios_base::out | ios_base::trunc | ios_base::binary);
//
//    f.write((char*)&cols, sizeof(cols));
//    f.write((char*)&rows, sizeof(rows));
//
//    int terrain = -1;
//    int wall = -1;
//    int object_id = -1;
//
//    for (int y = 0; y < rows; ++y) {
//        for (int x = 0; x < cols; ++x) {
//            terrainType = cells[y*cols+x]->terrainType;
//            terrainTile = cells[y*cols+x]->terrainTile;
//            wallType = cells[y*cols+x]->wallType;
//            wallTile = cells[y*cols+x]->wallTile;
//            object_id = cells[y*cols+x]->object_id;
//            f.write((char*)&terrainType, sizeof(terrainType));
//            f.write((char*)&terrainTile.set, sizeof(terrainTile.set));
//            f.write((char*)&terrainTile.id, sizeof(terrainTile.id));
//            f.write((char*)&wallType, sizeof(wallType));
//            f.write((char*)&wallTile.set, sizeof(wallTile.set));
//            f.write((char*)&wallTile.id, sizeof(wallTile.id));
//            f.write((char*)&object_id, sizeof(object_id));
//        }
//    }
//    f.close();
//    return true;
//}

void WorldStage::DrawPlace() {
  // 기준점의 y축 좌표 가 짝수인지 저장하는 변수.
  // y축이 홀수냐 짝수냐에 따라 x축 헥사맵 출력 방법이 달라져야 함.
  int is_y_odd(camera_pos.y()%2);

  // 지도의 출력 시작 위치. 여기서 + 범위좌표(cols, rows)까지 출력한다.
  int xStart = camera_pos.x() - frame_place_world_cols/2;
  int yStart = camera_pos.y() - frame_place_world_rows/2;

  // 현재 처리중인 셀의 좌표
  Coord current_cell;

  // 배경을 칠한다.
  DrawPattern(frame_place_offset, frame_place_width, frame_place_height, 0);

  Coord offset;
  // 맵 출력 루프.
  for (int y = -4; y < frame_place_world_rows+4; ++y) {
    offset.set_y(y);
    current_cell.set_y(yStart + y);
    // 범위초과시 continue
    if (current_cell.y() < 0 || current_cell.y() >= place.GetRows())
      continue;
    for (int x = -4; x < frame_place_world_cols+4; ++x) {
      offset.set_x(x);
      current_cell.set_x(xStart + x);
      // 범위초과시 continue
      if (current_cell.x() < 0 || current_cell.x() >= place.GetCols())
        continue;
      // 밝혀진 지도 출력
      if (revealed_place.GetTerrain(current_cell) != WorldTerrainType::none) {
        DrawWorldTile(revealed_place.GetTerrainTile(current_cell), offset, is_y_odd);
        if (revealed_place.GetObject(current_cell) != WorldObjectType::none) {
          DrawWorldTile(revealed_place.GetObjectTile(current_cell), offset, is_y_odd);
        }
      }
    }
  }
}

void WorldStage::Prepare() {
  DrawBackground();
  place.RandomizeTerrain();
  quit = false;
  map_name = place.GetName();
  PlayMusic(14);
}

void WorldStage::ProcessUserInput() {
  bool end_turn = false;
  SDL_Event event;
  Uint8* key_state = NULL;
  Draw();
  while(!end_turn && !program_quit) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        program_quit = true;
      }
      if (event.type == SDL_KEYDOWN) {
        switch( event.key.keysym.sym ) {
        case SDLK_ESCAPE:
          program_quit = true;
          break;

        case SDLK_F1:
          RevealRevealedPlace();
          message << "지도를 밝힙니다.\n";
          Draw();
          break;

        case SDLK_F2:
          ConcealRevealedPlace();
          message << "지도를 숨깁니다.\n";
          Draw();
          break;

        case SDLK_F3:
          TestDialog();
          Draw();
          break;

        case SDLK_F4:
          Draw();
          break;

        case SDLK_F5:
          message << "현재 시각은 " << GetWorldTimeString() << " 입니다.\n";
          Draw();
          break;

        case SDLK_F6:
          break;

        case SDLK_F7:
          TestEventDialog();
          break;

        case SDLK_1:
          ChangeGrid();
          message << "격자를 " << GetGrid() << "번으로 설정합니다.\n";
          Draw();
          break;

        case SDLK_2:
          place.RandomizeTerrain();
          ConcealRevealedPlace();
          message << "<blue>지형<black>을 다시 생성합니다.\n";
          map_name = place.GetName();
          Draw();
          break;

        case SDLK_3:
          message << "현재 위치에 <blue>지형물<black>을 생성합니다.\n";
          place.SetObject(player_pos, (WorldObjectType) (Random()%7));
          Draw();
          break;

        case SDLK_4:
          break;

        case SDLK_5:
          break;

        case SDLK_6:
          break;

        case SDLK_7:
          break;

        case SDLK_8:
          break;

        case SDLK_9:
          message << "<blue><로드 안><default>이 말했다. “당신은 지적재산권이라는 개념에 대해 어떻게 생각하시오? 무릇 인간의 모든 지식이란 한 개인이 만들어낸 것은 없소. 바위산에 돌멩이 하나 올린다고해서 그 산을 내가 만들었다고 말할 수는 없는 것 아니겠소.”\n";
          Draw();
          break;

        case SDLK_0:
          message << "<red><레프트21><default>에 쓰여 있기를...\n“파업 닷새째인 오늘도 현대차 비정규직 노동자들은 흔들림 없이 투쟁하고 있다. \n오전에는 정규직 노조인 현대차지부가 소집한 긴급 대의원간담회가 열렸다. 이 자리에 참관한 비정규직지회 조합원들은 “원ㆍ하청 공동투쟁”을 호소했다. \n이경훈 지부장에게 더 적극적인 연대를 촉구하는 정규직 대의원들의 발언도 이어졌다. 비정규직의 헌신적인 투쟁과 정규직의 연대에 압박을 받고 있는 이경훈 지부장도 “다음 주부터는 직접 현장에 뛰어 들겠다”고 밝혔다.  \n또, “토요일ㆍ일요일 어떤 경우라도 1공장 비정규직들이 침탈당하지 않도록 책임지겠다”며 자신을 포함해 상무집행위원들을 공장 안에 비상대기시키겠다고 했다. 각 사업부 대의원 5명씩 순환농성도 결정했다. 다행스런 일이다.\n하지만, 이경훈 지부장은 불법파견 비정규직 정규직화 요구에 대해서는 “우리가 할 수 있는 것이 아무 것도 없다”며 정규직 대의원에게 “제발 라인 잡는 것은 하지 마라”고도 했다. \n정규직 연대의 수위를 적당한 수준에서 통제하려는 이경훈 지부장의 이런 태도는 유감스럽다. \n법원도 인정한 불법파견 비정규직 정규직화 요구를 지지못할 이유가 없다. 더구나 현대차에서 비정규직과 불안정 고용을 줄이는 것은 정규직의 고용 안정을 위해서도 필요한 일이다.\n이경훈 집행부는 차가운 1공장 맨바닥에서 쪽잠을 자는 비정규직 노동자들의 연대 호소에 귀를 기울이며 더 적극적인 연대 투쟁에 나서야 한다. \n오늘도 지지방문이 이어졌다. 민주노동당 이정희 대표, 진보신당 조승수 대표, 민주당 의원 홍영표가 방문했다. 이정희 대표는 “여론이 뜨겁고 좋다. 일요일에 당원들이 공장 앞을 가득 메울 것”이라며 연대 투쟁을 약속해 큰 박수를 받았다. \n한편, 사측은 오늘도 비정규직 파업을 불법으로 매도하는 유인물을 돌리며 정규직과 비정규직을 이간질하려고 했다. 현대차 부사장 강호돈이 직접 나와 선전물을 배포하기도 했다.\n<한국경제>도 “비정규직 문제[는] 파업으로 풀릴 사안 아니”라며 “서둘러 생산현장에 복귀”하라고 촉구했다. 또 비정규직을 “모두 정규직화한다고 가정할 경우 생존마저 힘든 회사가 속출할 게 불 보듯 뻔하다”고 했다. \n이런 반응은 현대차 비정규직 투쟁의 중요성을 보여 주는 사례다. 기업주와 주류언론 들은 이 투쟁이 승리해서 다른 작업장의 비정규직들도 자신감을 얻어 투쟁에 나서는 것을 두려워한다. \n\n아름다운 연대 \n지난해 영웅적인 점거 파업을 벌였던 쌍용차 해고자도 1공장 농성장에 지지 방문을 와서 큰 힘을 줬다. \n“법질서 확립한다며 쌍용차 노동자들을 짓밟은 자들이 대법원 판결조차 지키지 않고 있다. \n“자본가들은 정규직과 비정규직을 분열시킨다. 이것을 무력화하는 것이 중요하다.\n“사측은 손배가압류나 소송으로 압박할 것이다. 우리가 흔들리면 사측은 그렇게 할 것이고 우리가 완강하게 투쟁하면 철회할 수 있다.”\n6년 간 초인적 투쟁으로 최근 승리를 쟁취한 기륭전자 김소연 분회장도 1공장 농성장에 지지 방문을 왔다. \n“우리는 2년 이상 근무하지 않아 법에 기댈 수도 없었다. 오직 투쟁만이 살 길이었다.  \n“서울에서도 여러분의 투쟁에 연대하려는 활동을 시작했다. 저희는 열명이었지만 여러분은 숫자도 많고 아산과 전주에서 단결하면 충분히 이길 수 있다.” \n끈질긴 투쟁으로 정규직화를 쟁취한 김 분회장의 연설을 들은 노동자들은 “대단한 투쟁을 한 것 같다”며 큰 박수를 보냈다. \n전주와 아산 공장에서도 투쟁이 계속됐다. \n전주 노동자들은 ‘아름다운 연대’의 모범을 이어가고 있다. 비정규직의 잔업 거부 투쟁에 정규직도 동참해 함께 잔업을 거부한 것이다. \n사측은 원하청 공동투쟁이 계속되자 주말 특근을 없애서 정규직과 비정규직을 이간질하려 하고 있다. \n하지만 오늘 전주 공장 앞에서 금속노조 전북지부가 주최한 집회에 정규직도 3백 명 가까이 참가해 탄탄한 연대를 과시했다. \n아산 사내하청지회도 주ㆍ야간 4시간 파업에 돌입하며 투쟁을 이어갔다.”\n";
          Draw();
          break;

        case SDLK_a:
          break;

        case SDLK_z:
          break;

        case SDLK_m:
          message << PlayMusicRandom() << "번 음악을 재생합니다.\n";
          Draw();
          break;

        case SDLK_l:
          message << "당신은 지금 " << place.GetTerrainName(player_pos) << " 위에 서 있다.\n";
          Draw();
          break;

        case SDLK_KP_PLUS:
          local.Prepare();
          local.Run();
          break;

        case SDLK_KP_MINUS:
          break;

        case SDLK_LEFT:
          key_state = SDL_GetKeyState(NULL);
          if (key_state[SDLK_UP]) {
            PlayerActMove(HexDir::nwest);
            end_turn = true;
          } else if (key_state[SDLK_DOWN]) {
            PlayerActMove(HexDir::swest);
            end_turn = true;
          } else {
            PlayerActMove(HexDir::west);
            end_turn = true;
          }
          break;

        case SDLK_RIGHT:
          key_state = SDL_GetKeyState(NULL);
          if (key_state[SDLK_UP]) {
            PlayerActMove(HexDir::neast);
            end_turn = true;
          } else if (key_state[SDLK_DOWN]) {
            PlayerActMove(HexDir::seast);
            end_turn = true;
          } else {
            PlayerActMove(HexDir::east);
            end_turn = true;
          }
          break;

        case SDLK_KP4:
          PlayerActMove(HexDir::west);
          end_turn = true;
          break;

        case SDLK_KP6:
          PlayerActMove(HexDir::east);
          end_turn = true;
          break;

        case SDLK_KP7:
        case SDLK_HOME:
          PlayerActMove(HexDir::nwest);
          end_turn = true;
          break;

        case SDLK_KP9:
        case SDLK_PAGEUP:
          PlayerActMove(HexDir::neast);
          end_turn = true;
          break;

        case SDLK_KP1:
        case SDLK_END:
          PlayerActMove(HexDir::swest);
          end_turn = true;
          break;

        case SDLK_KP3:
        case SDLK_PAGEDOWN:
          PlayerActMove(HexDir::seast);
          end_turn = true;
          break;

        case SDLK_KP5:
          PlayerActWait();
          end_turn = true;
          break;

        case SDLK_KP_DIVIDE:
          if(music_number > 0) {
            --music_number;
          } else {
            music_number = number_of_musics - 1;
          }
          PlayMusic(music_number);
          message << music_number << "번 음악을 재생합니다.\n";
          Draw();
          break;

        case SDLK_KP_MULTIPLY:
          if(music_number < number_of_musics - 1) {
            ++music_number;
          } else {
            music_number = 0;
          }
          PlayMusic(music_number);
          message << music_number << "번 음악을 재생합니다.\n";
          Draw();
          break;

        default:
          break;
        }
      }
    }
  }
}

void WorldStage::SetCameraPosToPlayer() {
  SetCameraPos(player_pos);
}

void WorldStage::PlayerActMove(const HexDir& dir) {
  HexPos target_pos(player_pos);
  target_pos.MoveTo(dir);
  if (place.IsOutOfRange(target_pos)) {
    // 범위 초과
    ;
  } else {
    // 이동
    player_pos.MoveTo(dir);
    SetCameraPosToPlayer();
  }
}

void WorldStage::PlayerActWait() {
  ;
}

void WorldStage::TestEventDialog() {
  DrawPattern(frame_fullscreen_rect, 0);
  DrawBox(frame_dialog_rect, color_purple);
  DrawImage(frame_dialog_illust_rect, 3);
  dialog_script.Clear();
  dialog_script << " 오늘은 위대한 혁명의 날.\n 많은 이들이 궁으로 들어와, 례법의 의식을 거행한다.";
  dialog_script.Draw();
  Refresh();
  WaitForInputIdle();
  Draw();
}

void WorldStage::UpdateStatusFrame() {
  status.Clear();
//  status << "<" << crets[player_id].name() << "> "
//         << "생명: " << crets[player_id].hp_current() << "/"
//         << crets[player_id].hp_max() << " "
//         << "정상";
}

void WorldStage::Draw() {
  UpdateRevealedPlace();
  DrawPlace();
  DrawPattern(frame_info_rect, 1);
  map_name.Draw();
  UpdateStatusFrame();
//  DrawPlayerHPGraph(crets[player_id].hp_current(), crets[player_id].hp_max());
  status.Draw();
  DrawBox(frame_message_rect, color_ltgray);
  message.Draw();
  message.Clear();
  Refresh();
}

void WorldStage::Run() {
  while(1) {
    if(quit)
      return;
    if(program_quit)
      return;
    ProcessUserInput();
  }
}
