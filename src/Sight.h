#ifndef SIGHT_H
#define SIGHT_H

#include "libs.h"
#include "types.h"
#include "HexPos.h"
#include "LocalPlace.h"

// 최대 시야. 반드시 짝수여야 한다.
// 최대 시야 변경시 LINE-OF-SIGHT 기준 테이블을 새로 만들어야 한다.
const int max_sight_range = 16;
const int sight_table_cols = max_sight_range * 2 + 1;
typedef int SightTable[sight_table_cols][sight_table_cols];

void ApplySightMask(SightTable& sight_table, const Coord& pos, const int& sight_range, const LocalPlace& place);
void LoadSightMask();

#endif // SIGHT_H
