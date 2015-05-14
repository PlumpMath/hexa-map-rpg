#include "draw.h"

using namespace video;

namespace draw {
SDL_Color bg_color = color_white;

int frame_place_width     = screen_width;
int frame_place_height    = screen_height;
int frame_place_cols      = 28;
int frame_place_rows      = 24;
Coord frame_place_offset  = Coord(0, 0);
int frame_place_world_cols;
int frame_place_world_rows;

int frame_minimap_width;
int frame_minimap_height;
int frame_minimap_cols;
int frame_minimap_rows;
Coord frame_minimap_offset;

SDL_Rect frame_info_rect;
SDL_Rect frame_message_rect;
SDL_Rect frame_map_name_rect;
SDL_Rect frame_status_rect;
SDL_Rect frame_hp_rect;
SDL_Rect hp_graph_rect;

int      frame_fullscreen_width;
int      frame_fullscreen_height;
Coord    frame_fullscreen_offset;
SDL_Rect frame_fullscreen_rect;
int      frame_dialog_width;
int      frame_dialog_height;
Coord    frame_dialog_offset;
SDL_Rect frame_dialog_rect;
SDL_Rect frame_dialog_title_rect;
SDL_Rect frame_dialog_content_rect;
SDL_Rect frame_dialog_illust_rect;
SDL_Rect frame_dialog_script_rect;
int      frame_dialog_map_cols;
int      frame_dialog_map_rows;

int base_tile_dist_cols;
int base_tile_dist_rows;
int base_tile_dist_cols_ex;
int base_tile_dist_height;
int base_tile_x_mod;
int base_tile_y_mod;

int grid = 0;

TextFrame map_name;
TextFrame status;
TextFrame message;
TextFrame dialog_title;
TextFrame dialog_content;
TextFrame dialog_script;

void InitializeFrames() {
  ifstream f;
  string   config_item_key;
  int      config_item_value;
  cout << "Loading frame config data..." << endl;
  f.open(config_frame_path.c_str());
  f >> config_item_key >> frame_place_width;
  f >> config_item_key >> frame_place_height;
  f >> config_item_key >> frame_place_cols;
  f >> config_item_key >> frame_place_rows;
  f >> config_item_key >> config_item_value;
  frame_place_offset.set_x(config_item_value);
  f >> config_item_key >> config_item_value;
  frame_place_offset.set_y(config_item_value);
  f >> config_item_key >> frame_place_world_cols;
  f >> config_item_key >> frame_place_world_rows;
  f >> config_item_key >> frame_info_rect.w;
  f >> config_item_key >> frame_info_rect.h;
  f >> config_item_key >> frame_info_rect.x;
  f >> config_item_key >> frame_info_rect.y;
  f >> config_item_key >> frame_minimap_width;
  f >> config_item_key >> frame_minimap_height;
  f >> config_item_key >> frame_minimap_cols;
  f >> config_item_key >> frame_minimap_rows;
  f >> config_item_key >> config_item_value;
  frame_minimap_offset.set_x(config_item_value);
  f >> config_item_key >> config_item_value;
  frame_minimap_offset.set_y(config_item_value);
  f >> config_item_key >> frame_message_rect.w;
  f >> config_item_key >> frame_message_rect.h;
  f >> config_item_key >> frame_message_rect.x;
  f >> config_item_key >> frame_message_rect.y;
  f >> config_item_key >> frame_map_name_rect.w;
  f >> config_item_key >> frame_map_name_rect.h;
  f >> config_item_key >> frame_map_name_rect.x;
  f >> config_item_key >> frame_map_name_rect.y;
  f >> config_item_key >> frame_status_rect.w;
  f >> config_item_key >> frame_status_rect.h;
  f >> config_item_key >> frame_status_rect.x;
  f >> config_item_key >> frame_status_rect.y;
  f >> config_item_key >> frame_hp_rect.w;
  f >> config_item_key >> frame_hp_rect.h;
  f >> config_item_key >> frame_hp_rect.x;
  f >> config_item_key >> frame_hp_rect.y;
  f.close();

  frame_fullscreen_rect.w = screen_width;
  frame_fullscreen_rect.h = screen_height;
  frame_fullscreen_rect.x = 0;
  frame_fullscreen_rect.y = 0;
  frame_fullscreen_width  = frame_fullscreen_rect.w;
  frame_fullscreen_height = frame_fullscreen_rect.h;
  frame_fullscreen_offset.set_x(frame_fullscreen_rect.x);
  frame_fullscreen_offset.set_y(frame_fullscreen_rect.y);
  frame_dialog_rect.w = 800;
  frame_dialog_rect.h = 600;
  frame_dialog_rect.x = (frame_fullscreen_rect.w-frame_dialog_rect.w)/2;
  frame_dialog_rect.y = (frame_fullscreen_rect.h-frame_dialog_rect.h)/2;
  frame_dialog_width  = frame_dialog_rect.w;
  frame_dialog_height = frame_dialog_rect.h;
  frame_dialog_offset.set_x(frame_dialog_rect.x);
  frame_dialog_offset.set_y(frame_dialog_rect.y);
  frame_dialog_title_rect.w = frame_dialog_rect.w;
  frame_dialog_title_rect.h = 20;
  frame_dialog_title_rect.x = frame_dialog_rect.x;
  frame_dialog_title_rect.y = frame_dialog_rect.y;
  frame_dialog_content_rect.w = frame_dialog_rect.w;
  frame_dialog_content_rect.h = frame_dialog_rect.h-frame_dialog_title_rect.h;
  frame_dialog_content_rect.x = frame_dialog_rect.x;
  frame_dialog_content_rect.y = frame_dialog_rect.y+frame_dialog_title_rect.h;
  frame_dialog_illust_rect.w = 300;
  frame_dialog_illust_rect.h = frame_dialog_rect.h;
  frame_dialog_illust_rect.x = frame_dialog_rect.x;
  frame_dialog_illust_rect.y = frame_dialog_rect.y;
  frame_dialog_script_rect.w = frame_dialog_rect.w - frame_dialog_illust_rect.w;
  frame_dialog_script_rect.h = frame_dialog_rect.h;
  frame_dialog_script_rect.x = frame_dialog_rect.x + frame_dialog_illust_rect.w;
  frame_dialog_script_rect.y = frame_dialog_rect.y;
  frame_dialog_map_cols = frame_dialog_content_rect.w/2;
  frame_dialog_map_rows = frame_dialog_content_rect.h/2;

  map_name.SetOffset(frame_map_name_rect);
  map_name.SetRowDist(0);
  map_name.SetDefaultFontColor(color_black);
  map_name.SetBgColor(color_white);
  map_name.SetShade(true);

  status.SetOffset(frame_status_rect);
  status.SetRowDist(0);
  status.SetDefaultFontColor(color_white);
  status.SetBgColor(color_white);
  status.SetShade(false);

  message.SetOffset(frame_message_rect);
  message.SetRowDist(20);
  message.SetDefaultFontColor(color_black);
  message.SetBgColor(color_white);
  message.SetShade(false);

  dialog_title.SetOffset(frame_dialog_title_rect);
  dialog_title.SetRowDist(0);
  dialog_title.SetDefaultFontColor(color_white);
  dialog_title.SetBgColor(color_black);
  dialog_title.SetShade(false);

  dialog_content.SetOffset(frame_dialog_content_rect);
  dialog_content.SetRowDist(20);
  dialog_content.SetDefaultFontColor(color_black);
  dialog_content.SetBgColor(color_white);
  dialog_content.SetShade(false);

  dialog_script.SetOffset(frame_dialog_script_rect);
  dialog_script.SetRowDist(20);
  dialog_script.SetDefaultFontColor(color_black);
  dialog_script.SetBgColor(color_white);
  dialog_script.SetShade(false);

  hp_graph_rect.x = 10;
  hp_graph_rect.y = 8;
  hp_graph_rect.w = 16;
  hp_graph_rect.h = 2;

  base_tile_dist_cols = tilesets[0]->GetDistCols();
  base_tile_dist_rows = tilesets[0]->GetDistRows();
  base_tile_dist_cols_ex = tilesets[0]->GetDistColsEx();
  base_tile_dist_height = tilesets[0]->GetDistHeight();
  base_tile_x_mod = tilesets[0]->GetXMod();
  base_tile_y_mod = tilesets[0]->GetYMod();
}

void DrawSide(const TileRef& tile, const HexPos& pos,
                       const int& is_y_odd, const int& height, const int& level) {
  SDL_Rect tile_rect;
  SDL_Rect offset;
  for (int i = 0; i<=level; ++i) {
    tile_rect = *tilesets[(int)tile.set]->GetRectPt(tile.id);
    offset.x = pos.x() * base_tile_dist_cols + frame_place_offset.x() - 20;
    offset.y = pos.y() * base_tile_dist_rows + frame_place_offset.y() - 20 - height * base_tile_dist_height + base_tile_dist_rows;
    if ((pos.y()+128)%2 != is_y_odd)
      offset.x += base_tile_dist_cols_ex;
    if (is_y_odd)
      offset.x -= base_tile_dist_cols_ex;
    offset.y += i * base_tile_dist_height;
    SDL_BlitSurface(tileset_surfaces[(int)tile.set], &tile_rect, screen, &offset);
  }
}

void DrawFloor(const TileRef& tile, const HexPos& pos,
                        const int& is_y_odd, const int& height) {
  SDL_Rect tile_rect;
  SDL_Rect offset;
  tile_rect = *tilesets[(int)tile.set]->GetRectPt(tile.id);
  offset.x = pos.x() * base_tile_dist_cols + frame_place_offset.x() - 20;
  offset.y = pos.y() * base_tile_dist_rows + frame_place_offset.y() - 20 - height * base_tile_dist_height;
    if ((pos.y()+128)%2 != is_y_odd)
    offset.x += base_tile_dist_cols_ex;
  if (is_y_odd)
    offset.x -= base_tile_dist_cols_ex;
  SDL_BlitSurface(tileset_surfaces[(int)tile.set], &tile_rect, screen, &offset);
}

void DrawFloorLiq(const TileRef& tile, const HexPos& pos,
                           const int& is_y_odd, const int& height) {
  SDL_Rect tile_rect;
  SDL_Rect offset;
  tile_rect = *tilesets[(int)tile.set]->GetRectPt(tile.id);
  int r = SDL_GetTicks() / 256 % 14;
  r = (r < 7) ? r - 3: 10 - r;
  r += Random()%3-1;
  tile_rect.x += r * tile_rect.w;
  if (tile_rect.x < 0)
    tile_rect.x = 0;
  if (tile_rect.x >= tile_rect.w * 0x10)
    tile_rect.x = tile_rect.w * 0x0f;
  offset.x = pos.x() * base_tile_dist_cols + frame_place_offset.x() - 20;
  offset.y = pos.y() * base_tile_dist_rows + frame_place_offset.y() - 20 - height * base_tile_dist_height;
    if ((pos.y()+128)%2 != is_y_odd)
    offset.x += base_tile_dist_cols_ex;
  if (is_y_odd)
    offset.x -= base_tile_dist_cols_ex;
  SDL_BlitSurface(tileset_surfaces[(int)tile.set], &tile_rect, screen, &offset);
}

void DrawTile(const TileRef& tile, const HexPos& pos,
              const int& is_y_odd, const int& height, const bool& is_sunken) {
  SDL_Rect tile_rect;
  SDL_Rect offset;
  tile_rect = *tilesets[(int)tile.set]->GetRectPt(tile.id);
  offset.x = pos.x() * base_tile_dist_cols + frame_place_offset.x() - 20;
  offset.y = pos.y() * base_tile_dist_rows + frame_place_offset.y() - 20 - height * base_tile_dist_height;
    if ((pos.y()+128)%2 != is_y_odd)
    offset.x += base_tile_dist_cols_ex;
  if (is_y_odd)
    offset.x -= base_tile_dist_cols_ex;
  offset.x += tilesets[(int)tile.set]->GetXMod();
  offset.y += tilesets[(int)tile.set]->GetYMod();

  if (is_sunken) {
    offset.y += 15;
    tile_rect.h -= 20;
  }

  SDL_BlitSurface(tileset_surfaces[(int)tile.set], &tile_rect, screen, &offset);
}

void DrawWorldTile(const TileRef& tile, const HexPos& pos, const int& is_y_odd) {
  SDL_Rect tile_rect;
  SDL_Rect offset;
  tile_rect = *tilesets[(int)tile.set]->GetRectPt(tile.id);
  offset.x = pos.x() * tilesets[(int)tile.set]->GetDistCols() + frame_place_offset.x() - 20;
  offset.y = pos.y() * tilesets[(int)tile.set]->GetDistRows() + frame_place_offset.y() - 20;
    if ((pos.y()+128)%2 != is_y_odd)
    offset.x += tilesets[(int)tile.set]->GetDistColsEx();
  if (is_y_odd)
    offset.x -= tilesets[(int)tile.set]->GetDistColsEx();
  offset.x += tilesets[(int)tile.set]->GetXMod();
  offset.y += tilesets[(int)tile.set]->GetYMod();
  SDL_BlitSurface(tileset_surfaces[(int)tile.set], &tile_rect, screen, &offset);
}

void DrawBackground() {
  //SDL_BlitSurface(background, NULL, screen, NULL);
}

const int& GetGrid() {
  return grid;
}
void SetGrid(const int& id) {
  grid = id;
}
void ChangeGrid() {
  grid < 1 ? grid++ : grid = 0;
}

void DrawPlayerHPGraph(const int& hp, const int& max_hp) {
  DrawGraph(frame_hp_rect, color_dkred, color_black, hp, max_hp);
}

void DrawHPGraph(const TileRef& tile, const HexPos& pos, const int& is_y_odd,
                 const int& height, const bool& is_sunken,
                 const int& hp, const int& max_hp) {
  SDL_Rect offset = hp_graph_rect;
  offset.x += pos.x() * base_tile_dist_cols + frame_place_offset.x() - 20;
  offset.y += pos.y() * base_tile_dist_rows + frame_place_offset.y() - 20 - height * base_tile_dist_height;
    if ((pos.y()+128)%2 != is_y_odd)
    offset.x += base_tile_dist_cols_ex;
  if (is_y_odd)
    offset.x -= base_tile_dist_cols_ex;
  offset.x += tilesets[(int)tile.set]->GetXMod();
  offset.y += tilesets[(int)tile.set]->GetYMod();
  if (is_sunken) {
    offset.y += 15;
  }
  DrawGraph(offset, color_red, color_black, hp, max_hp);
}

void WaitForInputIdle() {
  // 입력 대기
  SDL_Event event;
  while(1) {
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN) {
      break;
    }
  }
}

void TestDialog() {
  SDL_Rect dial_rect;
  dial_rect.x = 0;
  dial_rect.y = 0;
  dial_rect.w = screen_width;
  dial_rect.h = screen_height;
  Dialog dial(dial_rect, 20);
  dial.set_title("다이얼로그 테스트");
  dial.set_content("<red>RPG엔진 데모입니다. 이 도움말 화면은 [F3]키로 다시 보실 수 있습니다.\n<default>이 엔진에 구현된 기능은\n- 6각형 타일을 이용한 지형 랜덤 생성\n-장애물에 따른 시야 막힘 처리\n- 한국어 입출력\n- 도스 음원 재생\n입니다.\n\n플레이어를 이리저리 이동하며 지형을 밝혀보시고, 숫자키 [2]를 이용해 다른 지형도 생성해 보세요.\n\n<blue>* 키 설명<black>\n<이동> : 키패드 또는 방향키 조합을 이용합니다.\n\n<휴식> : [키패드5]\n\n<지도 생성> : 숫자키\n[2]         랜덤 맵 생성 (지형 랜덤 선택, 시간 1초 정도 걸림)\n[3]         벽 랜덤 생성\n[4]         크리처 랜덤 생성\n[6]         사각형 벽 생성 (Type A)\n[7]         사각형 벽 생성 (Type B)\n[8]         개울 생성\n[a]         현재 서 있는 곳의 높이를 높인다\n[z]         현재 서 있는 곳의 높이를 낮춘다\n\n<기타>\n[F4]         이름 바꾸기 (입력 테스트)\n[l]             현재 서 있는 곳의 정보\n[F5]         현재 시간을 확인한다\n[F1]         지도를 공개한다.\n[F2]         지도를 숨긴다.\n[F3]         다이얼로그 출력화면 테스트 (엔터 키로 빠져나옴)\n[키패드+]   플레이어의 시야 늘리기\n[키패드-]   플레이어의 시야 줄이기\n[1]            타일 사이의 격자를 변경한다.\n[키패드/]   이전 음악 재생\n[키패드*]    다음 음악 재생\n[m]           랜덤 음악 재생\n[ESC]         프로그램 종료\n\n<red>이 화면은 [F3]키로 다시 보실 수 있습니다. <blue>화면을 닫으려면 [엔터]키를 입력하세요.<black>");
  dial.Draw();
}

} // namespace draw
