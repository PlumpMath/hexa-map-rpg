#include "Sight.h"

SightTable sight_array_even[sight_table_cols][sight_table_cols] = {{{{0,},},},};
SightTable sight_array_odd[sight_table_cols][sight_table_cols] = {{{{0,},},},};
SightTable sight_mask_array_even[max_sight_range+1] = {{{0,},},};
SightTable sight_mask_array_odd[max_sight_range+1] = {{{0,},},};

void ApplySightMask(SightTable& sight_table, const Coord& pos, const int& sight_range, const LocalPlace& place) {
  // 시야선 테이블 초기화
  for (int y = 0; y < sight_table_cols; ++y)
    for (int x = 0; x < sight_table_cols; ++x)
        sight_table[y][x] = 0;

  // 현재 처리중인 셀의 좌표
  HexPos current_cell;

  // 시야범위 체크 시작지점.
  HexPos sight_start(pos.x() - max_sight_range, pos.y() - max_sight_range);

  // 기준점의 y축 좌표 가 짝수인지 저장하는 변수.
  // y축이 홀수냐 짝수냐에 따라 x축 헥사맵 출력 방법이 달라져야 함.
  bool yOdd = pos.y()%2 == 1;

  // 우선 시야선 테이블에 마스크를 적용한다.
  for (int y = 0; y < sight_table_cols; ++y)
    for (int x = 0; x < sight_table_cols; ++x)
        sight_table[y][x] = yOdd ? sight_mask_array_odd[sight_range][y][x] : sight_mask_array_even[sight_range][y][x];

  // 시야선 검사 루프.
  // y, x는 시야선 테이블의 인덱스로 사용
  // current_cell은 지도에서 현재 체크할 위치의 좌표이다.
  // 그 좌표는 sight_start부터 시작해 y, x를 더해나간다.
  // 맵의 범위를 초과할 때는 검사하지 않는다.
  // current_cell의 좌표에서 장애물이 발견되었으면 시야 테이블에 마스크를 더한다.
  // (n < sight_in_min || sight_in_max < n) x 또는 y가 n일 때는 시야범위 밖이므로 계산 생략
  int sight_in_min = max_sight_range-sight_range;
  int sight_in_max = max_sight_range+sight_range;

  for (int _y = 0; _y < sight_table_cols; ++_y) {
    if (_y < sight_in_min || sight_in_max < _y)
      continue;
    current_cell.set_y(_y + sight_start.y());
    if (current_cell.y() < 0 || current_cell.y() >= place.GetRows())
      continue;
    for (int _x = 0; _x < sight_table_cols; ++_x) {
      if (_x < sight_in_min || sight_in_max < _x)
        continue;
      current_cell.set_x(_x + sight_start.x());
      if (current_cell.x() < 0 || current_cell.x() >= place.GetCols())
        continue;
      // 현재 좌표 장애물 확인
      if (!(place.IsSeeable(pos, current_cell))) {
        // 테이블 갱신
        for (int y = 0; y<sight_table_cols; ++y) {
          for (int x = 0; x<sight_table_cols; ++x) {
            sight_table[y][x] += yOdd ? sight_array_odd[_y][_x][y][x] : sight_array_even[_y][_x][y][x];
          }
        }
      }
    }
  }
}

void LoadSightMask() {
  // 바이트 파일에서 입력받는 루틴
  char array_buffer[sight_table_cols][sight_table_cols][sight_table_cols][sight_table_cols] = {{{{0,},},},};
  char mask_buffer[max_sight_range+1][sight_table_cols][sight_table_cols] = {{{0,},},};
  ifstream file0("./data/sight_r16_even.dat", ios_base::in | ios_base::binary);
  if (!file0.is_open()) {
    cerr << "./data/sight_r16_even.dat 파일을 읽을 수 없습니다." << endl;
  }
  file0.read((char*)array_buffer, (sight_table_cols*sight_table_cols)*(sight_table_cols*sight_table_cols));
  for (int _y = 0; _y<sight_table_cols; ++_y) {
    for (int _x = 0; _x<sight_table_cols; ++_x) {
      for (int y = 0; y<sight_table_cols; ++y) {
        for (int x = 0; x<sight_table_cols; ++x) {
          sight_array_even[_y][_x][y][x] = (int)array_buffer[_y][_x][y][x];
        }
      }
    }
  }

  ifstream file1("./data/sight_r16_odd.dat", ios_base::in | ios_base::binary);
  if (!file1.is_open()) {
      cerr << "./data/sight_r16_odd.dat 파일을 읽을 수 없습니다." << endl;
  }
  file1.read((char*)array_buffer, (sight_table_cols*sight_table_cols)*(sight_table_cols*sight_table_cols));
  for (int _y = 0; _y<sight_table_cols; ++_y) {
    for (int _x = 0; _x<sight_table_cols; ++_x) {
      for (int y = 0; y<sight_table_cols; ++y) {
        for (int x = 0; x<sight_table_cols; ++x) {
          sight_array_odd[_y][_x][y][x] = (int)array_buffer[_y][_x][y][x];
        }
      }
    }
  }

  ifstream file2("./data/mask_r16_even.dat", ios_base::in | ios_base::binary);
  if (!file2.is_open()) {
      cerr << "./data/mask_r16_even.dat 파일을 읽을 수 없습니다." << endl;
  }
  file2.read((char*)mask_buffer, (max_sight_range+1)*(sight_table_cols*sight_table_cols));
  for (int n = 0; n<max_sight_range+1; ++n) {
    for (int y = 0; y<sight_table_cols; ++y) {
      for (int x = 0; x<sight_table_cols; ++x) {
        sight_mask_array_even[n][y][x] = (int)mask_buffer[n][y][x];
      }
    }
  }

  ifstream file3("./data/mask_r16_odd.dat", ios_base::in | ios_base::binary);
  if (!file3.is_open()) {
    cerr << "./data/mask_r16_odd.dat 파일을 읽을 수 없습니다." << endl;
  }
  file3.read((char*)mask_buffer, (max_sight_range+1)*(sight_table_cols*sight_table_cols));
  for (int n = 0; n<max_sight_range+1; ++n) {
    for (int y = 0; y<sight_table_cols; ++y) {
      for (int x = 0; x<sight_table_cols; ++x) {
        sight_mask_array_odd[n][y][x] = (int)mask_buffer[n][y][x];
      }
    }
  }
}
