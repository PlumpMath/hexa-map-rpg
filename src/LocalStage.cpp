#include "LocalStage.h"

using namespace draw;
using namespace sound;
using namespace rule;

// 생성자 및 소멸자
LocalStage::LocalStage()
    : place(128, 128),
      revealed_place(128, 128),
      camera_pos(0, 0),
      crets(),
      quit(false),
      player_id(0),
      ai_distance_limit(50),
      ai_distance_slow(35) {
}

LocalStage::~LocalStage() {
}

void LocalStage::UpdateRevealedPlace() {
  Coord player_pos(crets[player_id].pos());
  // 현재 처리중인 셀의 좌표
  Coord current_cell;
  // 시야범위 체크 시작지점. 여기서 + max_sight_range*2 까지 체크한다.
  int sight_start_x = player_pos.x() - max_sight_range;
  int sight_start_y = player_pos.y() - max_sight_range;
  // 맵의 y 축 루프
  for (int y = 0; y <= max_sight_range*2; ++y) {
    current_cell.set_y(sight_start_y + y);
    if (current_cell.y() < 0 || current_cell.y() >= place.GetRows())
      continue;
    if (current_cell.y() < player_pos.y()-max_sight_range ||
        current_cell.y() > player_pos.y()+max_sight_range)
      continue;
    for (int x = 0; x <= max_sight_range*2; ++x) {
      current_cell.set_x(sight_start_x + x);
      // 범위초과시 continue
      if (current_cell.x() < 0 || current_cell.x() >= place.GetCols())
        continue;
      if (current_cell.x() < player_pos.x()-max_sight_range ||
          current_cell.x() > player_pos.x()+max_sight_range)
        continue;
      // 시야선 검사
      if (crets[player_id].SightAt(Coord(current_cell.x()-sight_start_x,
                                         current_cell.y()-sight_start_y))) {
        // 밝혀진 지도 업데이트
        revealed_place.SetHeight(current_cell, place.GetHeight(current_cell));
        revealed_place.SetTerrain(current_cell, place.GetTerrain(current_cell));
        revealed_place.SetObject(current_cell, place.GetObject(current_cell));
      }
    }
  }
}

void LocalStage::RevealRevealedPlace() {
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

void LocalStage::ConcealRevealedPlace() {
  HexPos pos;
  for (int y = 0; y<place.GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x<place.GetCols(); ++x) {
      pos.set_x(x);
      revealed_place.SetHeight(pos, 0);
      revealed_place.SetTerrain(pos, -1);
      revealed_place.SetObject(pos, -1);
    }
  }
}

void LocalStage::SetCameraPos(const Coord& pos) {
  camera_pos = pos;
}


//const bool LocalStage::Load(const string& filename) {
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
//const bool LocalStage::Save(const string& filename) {
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

int LocalStage::GetSideLevel(Coord& pos) const {
  HexPos src(pos);
  HexPos tar(pos);
  const int def(0);
  int sw;
  int se;
  int level;
  tar.MoveTo(HexDir::swest);
  if (place.IsOutOfRange(tar))
    return def;
  sw = place.GetHeight(src) - place.GetHeight(tar);
  tar.MoveTo(HexDir::east);
  if (place.IsOutOfRange(tar))
    return sw+def;
  se = place.GetHeight(src) - place.GetHeight(tar);
  level = (sw>se) ? sw+def : se+def;
  if (level<def)
    level = def;
  return level;
}

void LocalStage::DrawPlace() {
  int player_id = 0;

  // 기준점의 y축 좌표 가 짝수인지 저장하는 변수.
  // y축이 홀수냐 짝수냐에 따라 x축 헥사맵 출력 방법이 달라져야 함.
  int is_y_odd(camera_pos.y()%2);
  int camera_height = place.GetHeight(camera_pos);

  // 지도의 출력 시작 위치. 여기서 + 범위좌표(cols, rows)까지 출력한다.
  int xStart = camera_pos.x() - frame_place_cols/2;
  int yStart = camera_pos.y() - frame_place_rows/2;

  // 현재 처리중인 셀의 좌표
  Coord current_cell;

  // 현재 셀의 오브젝트 ID
  int current_cell_obj;

  // 시야범위 체크 시작지점. 여기서 + max_sight_range*2 까지 체크한다.
  int sight_start_x = camera_pos.x() - max_sight_range;
  int sight_start_y = camera_pos.y() - max_sight_range;

  // 배경을 칠한다.
  DrawPattern(frame_place_offset, frame_place_width, frame_place_height, 0);

  Coord offset;
  // 맵 출력 루프.
  for (int y = -4; y < frame_place_rows+4; ++y) {
    offset.set_y(y);
    current_cell.set_y(yStart + y);
    // 범위초과시 continue
    if (current_cell.y() < 0 || current_cell.y() >= place.GetRows())
      continue;
    for (int x = -4; x < frame_place_cols+4; ++x) {
      offset.set_x(x);
      current_cell.set_x(xStart + x);
      // 범위초과시 continue
      if (current_cell.x() < 0 || current_cell.x() >= place.GetCols())
        continue;
      // 시야선 검사
      if (!(crets[player_id].sight_table()[current_cell.y()-sight_start_y][current_cell.x()-sight_start_x]) &&
          !(current_cell.y() < camera_pos.y()-max_sight_range ||
            current_cell.y() > camera_pos.y()+max_sight_range ||
            current_cell.x() < camera_pos.x()-max_sight_range ||
            current_cell.x() > camera_pos.x()+max_sight_range)) {
        // 지도 출력
        if (place.GetTerrain(current_cell) != -1) {
          DrawSide(place.GetSideTile(current_cell), offset,
            is_y_odd, place.GetHeight(current_cell) - camera_height,
            GetSideLevel(current_cell));
          DrawSide(TileRef(TilesetType::grid, 0x10+grid), offset,
            is_y_odd, place.GetHeight(current_cell) - camera_height,
            GetSideLevel(current_cell));
          if (revealed_place.GetTerrainTypeLiq(current_cell)) {
            DrawFloorLiq(place.GetFloorTile(current_cell), offset,
              is_y_odd, place.GetHeight(current_cell) - camera_height);
          } else {
            DrawFloor(place.GetFloorTile(current_cell), offset,
              is_y_odd, place.GetHeight(current_cell) - camera_height);
          }
          DrawTile(TileRef(TilesetType::grid, grid), offset,
            is_y_odd, place.GetHeight(current_cell) - camera_height);
          // 시야내 오브젝트 출력
          current_cell_obj = place.GetObject(current_cell);
          if (current_cell_obj != -1) {
            DrawTile(object_template[current_cell_obj].tile, offset, is_y_odd, place.GetHeight(current_cell) - camera_height);
          }
          current_cell_obj = place.GetCreatureId(current_cell);
          if (current_cell_obj != -1) {
            DrawTile(crets[current_cell_obj].tile(), offset, is_y_odd, place.GetHeight(current_cell) - camera_height, place.GetSink(current_cell));
            DrawHPGraph(crets[current_cell_obj].tile(), offset, is_y_odd, place.GetHeight(current_cell) - camera_height, place.GetSink(current_cell), crets[current_cell_obj].hp_current(), crets[current_cell_obj].hp_max());
          }
        }
      } else if (revealed_place.GetTerrain(current_cell) != -1) {
        // 밝혀진 지도 출력
        DrawSide(revealed_place.GetSideFogTile(current_cell), offset,
          is_y_odd, revealed_place.GetHeight(current_cell) - camera_height,
          GetSideLevel(current_cell));
        DrawSide(TileRef(TilesetType::grid, 0x10+grid), offset,
          is_y_odd, place.GetHeight(current_cell) - camera_height,
          GetSideLevel(current_cell));
        if (revealed_place.GetTerrainTypeLiq(current_cell)) {
          DrawFloorLiq(revealed_place.GetFloorFogTile(current_cell), offset,
            is_y_odd, revealed_place.GetHeight(current_cell) - camera_height);
        } else {
          DrawFloor(revealed_place.GetFloorFogTile(current_cell), offset,
            is_y_odd, revealed_place.GetHeight(current_cell) - camera_height);
        }
        DrawTile(TileRef(TilesetType::grid, grid), offset,
          is_y_odd, revealed_place.GetHeight(current_cell) - camera_height);
        current_cell_obj = revealed_place.GetObject(current_cell);
        if (current_cell_obj != -1) {
          DrawTile(object_template[current_cell_obj].tile_fog, offset,
          is_y_odd, revealed_place.GetHeight(current_cell) - camera_height);
        }
      }
    }
  }
}

void LocalStage::DrawMinimap() {
  // 기준점의 y축 좌표 가 짝수인지 저장하는 변수.
  // y축이 홀수냐 짝수냐에 따라 x축 헥사맵 출력 방법이 달라져야 함.
  int is_y_odd(camera_pos.y()%2);

  // 지도의 출력 시작 위치. 여기서 + 범위좌표(cols, rows)까지 출력한다.
  int xStart = camera_pos.x() - frame_minimap_cols/2;
  int yStart = camera_pos.y() - frame_minimap_rows/2;

  // 현재 처리중인 셀의 좌표
  Coord current_cell;

  // 현재 셀의 오브젝트 ID
  int current_cell_obj;

  SDL_Rect box;
  box.w = 2;
  box.h = 2;

  // 맵 출력 루프.
  for (int y = 0; y < frame_minimap_rows; ++y) {
    current_cell.set_y(yStart + y);
    // 범위초과시 continue
    if (current_cell.y() < 0 || current_cell.y() >= revealed_place.GetRows())
      continue;
    box.y = frame_minimap_offset.y() + y*2;
    for (int x = -1; x < frame_minimap_cols+1; ++x) {
      current_cell.set_x(xStart + x);
      // 범위초과시 continue
      if (current_cell.x() < 0 || current_cell.x() >= revealed_place.GetCols())
        continue;
      // 밝혀진 지도 출력
      if (revealed_place.GetTerrain(current_cell) != -1) {
        box.x = frame_minimap_offset.x() + x*2 - is_y_odd;
        if (y%2 == is_y_odd)
          ++box.x;
        DrawBox(box, revealed_place.GetTerrainColor(current_cell));
        current_cell_obj = revealed_place.GetObject(current_cell);
        if (current_cell_obj != -1) {
          DrawBox(box, object_template[current_cell_obj].color);
        }
      }
    }
  }
}

void LocalStage::DrawDialogMap() {
  // 기준점의 y축 좌표 가 짝수인지 저장하는 변수.
  // y축이 홀수냐 짝수냐에 따라 x축 헥사맵 출력 방법이 달라져야 함.
  int is_y_odd(1);

  // 지도의 출력 시작 위치. 여기서 + 범위좌표(cols, rows)까지 출력한다.
  int xStart = 0;
  int yStart = 0;

  // 현재 처리중인 셀의 좌표
  Coord current_cell;

  // 현재 셀의 오브젝트 ID
  int current_cell_obj;

  SDL_Rect box;
  box.w = 2;
  box.h = 2;

  // 배경을 칠한다.
  DrawPattern(frame_fullscreen_rect, 0);
  DrawBox(frame_dialog_rect, color_ltgray);
  DrawBox(frame_dialog_title_rect, color_dkgray);
  dialog_title.Clear();
  dialog_title << "탐험 지도 (" << place.GetName() << ")";
  dialog_title.Draw();
  // 맵 출력 루프.
  for (int y = 0; y < frame_dialog_map_rows; ++y) {
    current_cell.set_y(yStart + y);
    // 범위초과시 continue
    if (current_cell.y() < 0 || current_cell.y() >= revealed_place.GetRows())
      continue;
    box.y = frame_dialog_content_rect.y + y*2;
    for (int x = -1; x < frame_dialog_map_cols+1; ++x) {
      current_cell.set_x(xStart + x);
      // 범위초과시 continue
      if (current_cell.x() < 0 || current_cell.x() >= revealed_place.GetCols())
        continue;
      // 밝혀진 지도 출력
      if (revealed_place.GetTerrain(current_cell) != -1) {
        box.x = frame_dialog_content_rect.x + x*2;
        if (y%2 == is_y_odd)
          ++box.x;
        DrawBox(box, revealed_place.GetTerrainColor(current_cell));
        current_cell_obj = revealed_place.GetObject(current_cell);
        if (current_cell_obj != -1) {
          DrawBox(box, object_template[current_cell_obj].color);
        }
      }
    }
  }
}

void LocalStage::Prepare() {
  DrawBackground();
  place.RandomizeTerrain(LandType::island);
  crets.CreateCreature(place, Coord(20, 20), 0); // pc
  SetCameraPos(crets[player_id].pos());
  for (int i = 0; i < 40; ++i)
    crets.CreateCreature(place, Coord(Random()%place.GetCols(), Random()%place.GetRows()), Random()%2+1);
  quit = false;
  map_name = place.GetName();
  player_id = 0;
  PlayMusic(14);
  //TestDialog();
}

void LocalStage::TestStringScanner() {
  StringScanner sc;
  crets[player_id].set_name(sc.Scan(1, true, 60, message, "당신의 이름은 무엇입니까? : "));
  message << "이제부터 " << crets[player_id].name() << "{이} 당신의 이름입니다.\n";
}

void LocalStage::ProcessUserInput() {
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
          TestStringScanner();
          Draw();
          break;

        case SDLK_F5:
          message << "현재 시각은 " << GetWorldTimeString() << " 입니다.\n";
          Draw();
          break;

        case SDLK_F6:
          UserShowDialogMap();
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
          place.RandomizeWall();
          message << "<blue>벽<black>을 다시 생성합니다.\n";
          Draw();
          break;

        case SDLK_4:
          for (int i = 0; i < 10; ++i)
          crets.CreateCreature(place, Coord(Random()%place.GetCols(), Random()%place.GetRows()), Random()%2+1);
          message << "<blue>크리처<black>를 추가 생성합니다. " << "총 크리쳐 : " << crets.GetCount() << " 개\n";
          Draw();
          break;

        case SDLK_5:
            break;

        case SDLK_6:
          place.DrawObjectRectangleA(crets[player_id].pos(), Random()%12+1, Random()%12+1, Random()%0x10);
          UpdateRevealedPlace();
          message << "사각형 벽을 만듭니다 : Type A\n";
          Draw();
          break;

        case SDLK_7:
          place.DrawObjectRectangleB(crets[player_id].pos(), Random()%12+1, Random()%12+1, Random()%0x10);
          UpdateRevealedPlace();
          message << "사각형 벽을 만듭니다 : Type B\n";
          Draw();
          break;

        case SDLK_8:
          place.DrawPool(crets[player_id].pos(), 3, 3);
          UpdateRevealedPlace();
          message << "개울을 만듭니다\n";
          Draw();
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
          place.SetHeight(crets[player_id].pos(), place.GetHeight(crets[player_id].pos())+1);
          UpdateRevealedPlace();
          message << "지형의 높이를 높였습니다. 현재 높이 : " << place.GetHeight(crets[player_id].pos()) << '\n';
          Draw();
          break;

        case SDLK_z:
          place.SetHeight(crets[player_id].pos(), place.GetHeight(crets[player_id].pos())-1);
          UpdateRevealedPlace();
          message << "지형의 높이를 낮췄습니다. 현재 높이 : " << place.GetHeight(crets[player_id].pos()) << '\n';
          Draw();
          break;

        case SDLK_m:
          message << PlayMusicRandom() << "번 음악을 재생합니다.\n";
          Draw();
          break;

        case SDLK_l:
          message << "당신은 지금 " << place.GetTerrainName(crets[player_id].pos()) << " 위에 서 있다.\n";
          Draw();
          break;

        case SDLK_KP_PLUS:
          if (crets[player_id].IncSightRange()) {
              UpdateRevealedPlace();
              message << "시야를 늘렸습니다. 현재 시야 : " << crets[player_id].sight_range() << '\n';
          } else {
              message << "시야를 더 늘릴 수 없습니다.\n";
          }
          Draw();
          break;

        case SDLK_KP_MINUS:
          if (crets[player_id].DecSightRange()) {
              UpdateRevealedPlace();
              message << "시야를 줄였습니다. 현재 시야 : "
              << crets[player_id].sight_range() << "\n";
          } else {
              message << "시야를 더 줄일 수 없습니다.\n";
          }
          Draw();
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

void LocalStage::FlowTick() {
  world_tick++;
  for (int id = 0; id<crets.GetCount(); ++id) {
    crets[id].FlowTick();
  }
}

void LocalStage::ProcessCreatures() {
  for (int id = 0; id<crets.GetCount(); ++id) {
    if(crets[id].is_removed())
      continue;
    // AI 처리범위 밖이면 8분의 1 확률로 행동, 최대치 밖이면 AI 행동 않음
    if (crets[id].IsActiveTurn()) {
      if ((crets[id].GetDistanceWith(player_id) < ai_distance_limit) &&
          (crets[id].GetDistanceWith(player_id) < ai_distance_slow ||
           Random()%8 == 0)) {
        // 행동 전 시야 업데이트
        crets[id].UpdateSightTable();
        if (id == player_id) {
          // 플레이어 행동
          ProcessUserInput();
        } else {
          // NPC 행동
          ProcessCreatureAct(id);
        }
        // 행동 후 시야 업데이트
        crets[id].UpdateSightTable();
      }
      crets[id].ActWait();
    }
  }
}

void LocalStage::ProcessCreatureAct(const int& id) {
  crets[id].ActWalkTo((HexDir)(Random()%6));
}

void LocalStage::SetCameraPosToPlayer() {
  SetCameraPos(crets[player_id].pos());
}

void LocalStage::PlayerActMove(const HexDir& dir) {
  HexPos target_pos(crets[player_id].pos());
  target_pos.MoveTo(dir);
  if (place.IsOutOfRange(target_pos)) {
    // 범위 초과
    ;
  } else if (place.HasCreature(target_pos)) {
    // 기본 공격
    crets[player_id].ActBaseAttack(target_pos);
  } else {
    // 이동
    crets[player_id].ActWalkTo(dir);
    SetCameraPosToPlayer();
  }
}

void LocalStage::PlayerActWait() {
  crets[player_id].ActWait();
}

void LocalStage::UserShowDialogMap() {
  DrawDialogMap();
  Refresh();
  WaitForInputIdle();
  Draw();
}

void LocalStage::TestEventDialog() {
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

void LocalStage::UpdateStatusFrame() {
  status.Clear();
  status << "<" << crets[player_id].name() << "> "
         << "생명: " << crets[player_id].hp_current() << "/"
         << crets[player_id].hp_max() << " "
         << "정상";
}

void LocalStage::Draw() {
  crets[player_id].UpdateSightTable();
  UpdateRevealedPlace();
  DrawPlace();
  DrawPattern(frame_info_rect, 1);
  DrawMinimap();
  map_name.Draw();
  UpdateStatusFrame();
  DrawPlayerHPGraph(crets[player_id].hp_current(), crets[player_id].hp_max());
  status.Draw();
  DrawBox(frame_message_rect, color_ltgray);
  message.Draw();
  message.Clear();
  Refresh();
}

void LocalStage::Run() {
  while(1) {
    if(quit)
      return;
    if(program_quit)
      return;
    ProcessCreatures();
    FlowTick();
  }
}
