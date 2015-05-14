#ifndef TILESET_H
#define TILESET_H

#include "libs.h"
#include "types.h"
#include "TilesetType.h"

using namespace std;

// ============================================================================
// 클래스 Tileset 정의
// - 타일셋 이미지와 Tile 객체정보를 보관하여 다른 객체에게 전달한다.
// ============================================================================
class Tileset {
private:
  // private 상수와 변수
  const int tile_width;     // 개별 타일의 가로 크기
  const int tile_height;    // 개별 타일의 세로 크기
  const int cols;           // 타일셋의 열 수
  const int rows;           // 타일셋의 행 수
  const int size;           // 타일의 총 개수
  const int dist_cols;      // 타일배치간격(가로)
  const int dist_cols_ex;   // 홀수y축타일배치간격(가로)
  const int dist_rows;      // 타일배치간격(세로)
  const int dist_height;    // 타일배치간격(높이)
  const int x_mod;          // x축 재배치 값
  const int y_mod;          // y축 재배치 값
  vector<SDL_Rect> rects;   // 개별 슬라이스 배열

private:
  // 사용 금지
  Tileset& operator=(Tileset& r_right_object);
  Tileset(Tileset& r_source_object);

public:
  // 생성자 및 소멸자
  explicit Tileset(const TilesetType& tilesetType,
                   const int& tile_width,     const int& tile_height,
                   const int& cols,           const int& rows,
                   const int& dist_cols,      const int& extra_dist_cols,
                   const int& dist_rows,      const int& height_dist,
                   const int& x_mod,          const int& y_mod);
  ~Tileset(void);

public:
  // 기타 인터페이스
  inline const int& GetTileWidth() const {
    return tile_width;
  }
  inline const int& GetTileHeight() const {
    return tile_height;
  }
  inline const int& GetCols() const {
    return cols;
  }
  inline const int& GetRows() const {
    return rows;
  }
  inline const int& GetSize() const {
    return size;
  }
  inline const int& GetDistCols() const {
    return dist_cols;
  }
  inline const int& GetDistColsEx() const {
    return dist_cols_ex;
  }
  inline const int& GetDistRows() const {
    return dist_rows;
  }
  inline const int& GetDistHeight() const {
    return dist_height;
  }
  inline const int& GetXMod() const {
    return x_mod;
  }
  inline const int& GetYMod() const {
    return y_mod;
  }
  inline SDL_Rect* GetRectPt(int index) {
    return &rects[index];
  }
};

#endif // TILESET_H
