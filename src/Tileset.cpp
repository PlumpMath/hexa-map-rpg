#include "Tileset.h"

// ----------------------------------------------------------------------------
// 이름: Tileset 생성자
// 기능: 타일셋 이미지를 읽어들인 후, 개별 타일로 나누어 저장한다.
// 인수: filename   - 타일셋 이미지의 파일명
//       tile_width  - 개별 타일의 가로 크기
//       tile_height - 개별 타일의 세로 크기
//       column     - 타일셋 이미지에 들어있는 타일의 칸 수
//       row        - 타일셋 이미지에 들어있는 타일의 줄 수
// 반환: void
// ----------------------------------------------------------------------------
Tileset::Tileset(const TilesetType& tilesetType,
                 const int& tile_width,
                 const int& tile_height,
                 const int& cols,
                 const int& rows,
                 const int& dist_cols,
                 const int& dist_cols_ex,
                 const int& dist_rows,
                 const int& dist_height,
                 const int& x_mod,
                 const int& y_mod)
    : tile_width(tile_width),
      tile_height(tile_height),
      cols(cols),
      rows(rows),
      size(cols * rows),
      dist_cols(dist_cols),
      dist_cols_ex(dist_cols_ex),
      dist_rows(dist_rows),
      dist_height(dist_height),
      x_mod(x_mod),
      y_mod(y_mod) {
  SDL_Rect rect;
  rect.w = tile_width;
  rect.h = tile_height;
  // 타일 분리 루프
  for (int y = 0; y < rows; ++y) {
    rect.y = y * tile_height;
    for (int x = 0; x < cols; ++x) {
      rect.x = x * tile_width;
      rects.push_back(rect);
    }
  }
}

// ----------------------------------------------------------------------------
// 이름: Tileset 소멸자
// 기능: 힙에 들어간 자료 삭제
// 인수: void
// 반환: void
// ----------------------------------------------------------------------------
Tileset::~Tileset(void) {
}
