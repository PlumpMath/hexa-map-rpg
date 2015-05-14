// draw.h -- 게임중 프레임 속에 출력하기 위한 활용 함수(전역) 모음
// 기본적인 출력은 video.h / video.cpp 가 담당함.

#ifndef DRAW_H
#define DRAW_H

#include "libs.h"
#include "types.h"
#include "Random.h"
#include "Color.h"
#include "video.h"
#include "TextFrame.h"
#include "Dialog.h"
#include "StringScanner.h"

using namespace video;

namespace draw {
extern int frame_place_width;
extern int frame_place_height;
extern int frame_place_cols;
extern int frame_place_rows;
extern Coord frame_place_offset;
extern int frame_place_world_cols;
extern int frame_place_world_rows;

extern int frame_minimap_width;
extern int frame_minimap_height;
extern int frame_minimap_cols;
extern int frame_minimap_rows;
extern Coord frame_minimap_offset;

extern SDL_Rect frame_info_rect;
extern SDL_Rect frame_message_rect;
extern SDL_Rect frame_map_name_rect;
extern SDL_Rect frame_status_rect;
extern SDL_Rect frame_hp_rect;
extern SDL_Rect hp_graph_rect;

extern int      frame_fullscreen_width;
extern int      frame_fullscreen_height;
extern Coord    frame_fullscreen_offset;
extern SDL_Rect frame_fullscreen_rect;

extern int      frame_dialog_width;
extern int      frame_dialog_height;
extern Coord    frame_dialog_offset;
extern SDL_Rect frame_dialog_rect;
extern SDL_Rect frame_dialog_title_rect;
extern SDL_Rect frame_dialog_content_rect;
extern SDL_Rect frame_dialog_illust_rect;
extern SDL_Rect frame_dialog_script_rect;
extern int      frame_dialog_map_cols;
extern int      frame_dialog_map_rows;

extern int base_tile_dist_cols;
extern int base_tile_dist_rows;
extern int base_tile_dist_cols_ex;
extern int base_tile_dist_height;
extern int base_tile_x_mod;
extern int base_tile_y_mod;

extern SDL_Color bg_color;
extern int grid;

extern TextFrame map_name;
extern TextFrame status;
extern TextFrame message;
extern TextFrame dialog_title;
extern TextFrame dialog_content;
extern TextFrame dialog_script;

void InitializeFrames();

void DrawBackground();
void DrawMiniplace(LocalPlace& revealed_place, const Coord& camera_pos);
void DrawFloor(const TileRef& tile, const HexPos& pos, const int& is_y_odd, const int& height);
void DrawFloorLiq(const TileRef& tile, const HexPos& pos, const int& is_y_odd, const int& height);
void DrawSide(const TileRef& tile, const HexPos& pos, const int& is_y_odd, const int& height, const int& level);
void DrawTile(const TileRef& tile, const HexPos& pos, const int& is_y_odd, const int& height, const bool& is_sunken = false);
void DrawWorldTile(const TileRef& tile, const HexPos& pos, const int& is_y_odd);
const int& GetGrid();
void SetGrid(const int& id);
void ChangeGrid();

void DrawHPGraph(const TileRef& tile, const HexPos& pos, const int& is_y_odd,
                 const int& height, const bool& is_sunken,
                 const int& hp, const int& max_hp);
void DrawPlayerHPGraph(const int& hp, const int& max_hp);

void WaitForInputIdle();
void TestDialog();

} // namespace draw

#endif // DRAW_H
