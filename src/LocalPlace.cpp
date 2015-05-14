#include "LocalPlace.h"

// 생성자 및 소멸자
LocalPlace::LocalPlace()
    : cols(0),
      rows(0),
      size(0) {
}
LocalPlace::LocalPlace(const int& cols, const int& rows)
    : cols(cols),
      rows(rows),
      size(cols*rows) {
  for (int i = 0; i < size; ++i) {
    cells.push_back(new LocalPlaceCell());
  }
}
LocalPlace::~LocalPlace() {
  Clear();
}

void LocalPlace::CreateNewPlace(const int& cols, const int& rows) {
  Clear();
  this->cols = cols;
  this->rows = rows;
  size = cols*rows;
  for (int i = 0; i < size; ++i) {
    cells.push_back(new LocalPlaceCell());
  }
}

void LocalPlace::Clear() {
  for (auto it = cells.begin(); it != cells.end(); ++it)
    delete *it;
  cells.clear();
  rows = 0;
  cols = 0;
  size = 0;
}

// 셀 데이터 검사 함수
const bool LocalPlace::IsOutOfRange(const Coord& pos) const {
  if (pos.x() < 0 || pos.x() >= cols) {
    return true;
  } else if (pos.y() < 0 || pos.y() >= rows) {
    return true;
  } else {
    return false;
  }
}
const bool LocalPlace::IsOccupied(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->IsOccupied();
}
const bool LocalPlace::IsPassable(const Coord& mover_pos,
                                const Coord& target_pos,
                                const MoveType& move_type) const {
  if (IsOutOfRange(target_pos)) return false;
  if (HasObject(target_pos)) return false;
  if (HasCreature(target_pos)) return false;
  if (GetHeight(target_pos) - GetHeight(mover_pos) >= 2) return false;
  return true;
}
const bool LocalPlace::IsSeeable(const Coord& seer_pos,
                               const Coord& target_pos) const {
  if (IsOutOfRange(target_pos)) return false;
  if (HasObject(target_pos)) return false;
  if (GetHeight(target_pos) - GetHeight(seer_pos) >= 2) return false;
  return true;
}

// 셀 데이터 접근 함수
const bool LocalPlace::HasTerrain(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->terrain != -1;
}
const bool LocalPlace::HasObject(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->object != -1;
}
const bool LocalPlace::HasCreature(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->creature_id != -1;
}

const int& LocalPlace::GetCols() const {
  return cols;
}
const int& LocalPlace::GetRows() const {
  return rows;
}
const int& LocalPlace::GetSize() const {
  return size;
}

const int& LocalPlace::GetTerrain(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->terrain;
}
const int& LocalPlace::GetObject(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->object;
}
const int& LocalPlace::GetCreatureId(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->creature_id;
}
const int& LocalPlace::GetHeight(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->height;
}
const int& LocalPlace::GetGrass(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->grass;
}
const TerrainType& LocalPlace::GetTerrainType(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].type;
}
const string& LocalPlace::GetTerrainName(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].name;
}
const TileRef& LocalPlace::GetFloorTile(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].floor;
}
const TileRef& LocalPlace::GetFloorFogTile(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].floor_fog;
}
const TileRef& LocalPlace::GetSideTile(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].side;
}
const TileRef& LocalPlace::GetSideFogTile(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].side_fog;
}
const SDL_Color& LocalPlace::GetTerrainColor(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].color;
}
bool LocalPlace::GetTerrainTypeLiq(const Coord& pos) const {
  TerrainType type(GetTerrainType(pos));
  if (type == TerrainType::shallow_water)
    return true;
  if (type == TerrainType::deep_water)
    return true;
  if (type == TerrainType::shallow_sea)
    return true;
  if (type == TerrainType::deep_sea)
    return true;
  if (type == TerrainType::lava)
    return true;
  return false;
}
const bool& LocalPlace::GetSink(const Coord& pos) const {
  return terrain_template[cells[pos.y()*cols+pos.x()]->terrain].is_liquid;
}
const string& LocalPlace::GetName() const {
  return name;
}

const bool LocalPlace::SetTerrain(const Coord& pos, const int& terrain) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->terrain = terrain;
  return true;
}
const bool LocalPlace::SetObject(const Coord& pos, const int& object) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->object = object;
  return true;
}
const bool LocalPlace::SetCreatureId(const Coord& pos, const int& creature_id) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->creature_id = creature_id;
  return true;
}
const bool LocalPlace::SetHeight(const Coord& pos, const int& height) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->height = height;
  return true;
}
const bool LocalPlace::SetGrass(const Coord& pos, const int& grass) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->grass = grass;
  return true;
}
void LocalPlace::SetName(const string& name) {
  this->name = name;
}

const bool LocalPlace::CreateObject(const Coord& pos, const int& object) {
  if (IsOutOfRange(pos)) return false;
  if (IsOccupied(pos)) return false;
  SetObject(pos, object);
  return true;
}

const bool LocalPlace::RemoveTerrain(const Coord& pos) {
  if (IsOutOfRange(pos)) return false;
  if (!HasTerrain(pos)) return false;
  SetTerrain(pos, -1);
  return true;
}
const bool LocalPlace::RemoveObject(const Coord& pos) {
  if (IsOutOfRange(pos)) return false;
  if (!HasObject(pos)) return false;
  SetObject(pos, -1);
  return true;
}

void LocalPlace::ClearObject() {
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      RemoveObject(pos);
    }
  }
}

// 맵 편집 함수

const bool LocalPlace::CreateWall(const Coord& pos) {
  return CreateObject(pos, 0x00);
}
const bool LocalPlace::CreateGreenTree(const Coord& pos) {
  return CreateObject(pos, 0x10*0+Random()%0x10);
}
const bool LocalPlace::CreateYellowTree(const Coord& pos) {
  return CreateObject(pos, 0x10*1+Random()%0x10);
}
const bool LocalPlace::CreatePinkTree(const Coord& pos) {
  return CreateObject(pos, 0x10*2+Random()%0x10);
}
const bool LocalPlace::CreateWhiteTree(const Coord& pos){
  return CreateObject(pos, 0x10*3+Random()%0x10);
}

void LocalPlace::DrawPool(const Coord& pos, const int& w, const int& h) {
  HexPos hex_pos(pos);
  for (int y = 0; y<h; ++y) {
    for (int x = 0; x<w; ++x) {
      if (IsOutOfRange(hex_pos))
        continue;
      SetTerrain(hex_pos, (int)TerrainType::shallow_water*0x10+Random()%0x10);
      hex_pos.MoveTo(HexDir::east);
    }
    for (int x = 0; x<w; ++x) hex_pos.MoveTo(HexDir::west);
    hex_pos.MoveTo(HexDir::seast);
  }
}

void LocalPlace::DrawObjectRectangleA(const Coord& pos, const int& w, const int& h, const int& object) {
  HexPos hex_pos(pos);
  for (int y = 0; y<h; ++y) {
    for (int x = 0; x<w; ++x) {
      CreateObject(hex_pos, object);
      hex_pos.MoveTo(HexDir::east);
    }
    for (int x = 0; x<w; ++x) hex_pos.MoveTo(HexDir::west);
    hex_pos.MoveTo(HexDir::seast);
  }
}

void LocalPlace::DrawObjectRectangleB(const Coord& pos, const int& w, const int& h, const int& object) {
  HexPos hex_pos(pos);
  for (int y = 0; y<h; ++y) {
    for (int x = 0; x<w; ++x) {
      CreateObject(hex_pos, object);
      hex_pos.MoveTo(HexDir::east);
    }
    for (int x = 0; x<w; ++x) hex_pos.MoveTo(HexDir::west);
    hex_pos.MoveTo(HexDir::swest);
  }
}

void LocalPlace::DrawObjectRectangleC(const Coord& pos, const int& w, const int& h, const int& object) {
  HexPos hex_pos(pos);
  for (int y = 0; y<h; ++y) {
    for (int x = 0; x<w; ++x) {
      CreateObject(hex_pos, object);
      hex_pos.MoveTo(HexDir::east);
    }
    for (int x = 0; x<w; ++x) hex_pos.MoveTo(HexDir::west);
    (y%2==0) ? hex_pos.MoveTo(HexDir::seast) : hex_pos.MoveTo(HexDir::swest);
  }
}

HexPos LocalPlace::FindLowest(HexPos& pos) {
  HexPos neib, lowest;
  lowest = pos;
  neib = pos;
  neib.MoveTo(HexDir::nwest);
  if ((!IsOutOfRange(neib)) && GetHeight(neib) < GetHeight(lowest))
    lowest = neib;
  neib = pos;
  neib.MoveTo(HexDir::neast);
  if ((!IsOutOfRange(neib)) && GetHeight(neib) < GetHeight(lowest))
    lowest = neib;
  neib = pos;
  neib.MoveTo(HexDir::west);
  if ((!IsOutOfRange(neib)) && GetHeight(neib) < GetHeight(lowest))
    lowest = neib;
  neib = pos;
  neib.MoveTo(HexDir::east);
  if ((!IsOutOfRange(neib)) && GetHeight(neib) < GetHeight(lowest))
    lowest = neib;
  neib = pos;
  neib.MoveTo(HexDir::swest);
  if ((!IsOutOfRange(neib)) && GetHeight(neib) < GetHeight(lowest))
    lowest = neib;
  neib = pos;
  neib.MoveTo(HexDir::seast);
  if ((!IsOutOfRange(neib)) && GetHeight(neib) < GetHeight(lowest))
    lowest = neib;

  if (pos == lowest) {
    return lowest;
  } else {
    return FindLowest(lowest);
  }
}

HexPos LocalPlace::FindGrassless(HexPos& pos) {
    HexPos neib, grassless;
    grassless = pos;
    neib = pos;
    neib.MoveTo(HexDir::nwest);
    if ((!IsOutOfRange(neib)) &&
        (GetTerrainType(neib) == TerrainType::dirt) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::neast);
    if ((!IsOutOfRange(neib)) &&
        (GetTerrainType(neib) == TerrainType::dirt) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::west);
    if ((!IsOutOfRange(neib)) &&
        (GetTerrainType(neib) == TerrainType::dirt) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::east);
    if ((!IsOutOfRange(neib)) &&
        (GetTerrainType(neib) == TerrainType::dirt) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::swest);
    if ((!IsOutOfRange(neib)) &&
        (GetTerrainType(neib) == TerrainType::dirt) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::seast);
    if ((!IsOutOfRange(neib)) &&
        (GetTerrainType(neib) == TerrainType::dirt) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;

    if (pos == grassless) {
      return grassless;
    } else {
      return FindGrassless(grassless);
    }
}

void LocalPlace::PlainizeHeight(const int& start_x, const int& start_y,
                                const int& end_x,   const int& end_y,
                                const int& base_height) {
  HexPos pos;
  for (int y = start_y; y <= end_y; ++y) {
    pos.set_y(y);
    for (int x = start_x; x <= end_x; ++x) {
      pos.set_x(x);
      SetHeight(pos, base_height);
    }
  }
}

void LocalPlace::PlainizeGrass(const int& start_x, const int& start_y,
                               const int& end_x,   const int& end_y,
                               const int& base_grass) {
  HexPos pos;
  for (int y = start_y; y <= end_y; ++y) {
    pos.set_y(y);
    for (int x = start_x; x <= end_x; ++x) {
      pos.set_x(x);
      SetGrass(pos, base_grass);
    }
  }
}

void LocalPlace::RandomizeHeight(int max_increaser) {
  if (max_increaser <= 1) max_increaser = 2;
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      SetHeight(pos, GetHeight(pos) + Random()%max_increaser);
    }
  }
}

void LocalPlace::RandomizeGrass(int max_increaser) {
  if (max_increaser <= 1) max_increaser = 2;
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      SetGrass(pos, GetGrass(pos) + Random()%max_increaser);
    }
  }
}

void LocalPlace::CategorizeTerrainByHeight() {
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      if (512 < GetHeight(pos)) {
        SetTerrain(pos, (int)TerrainType::snow*0x10 + Random()%0x10);
      } else if (20 < GetHeight(pos)) {
        SetTerrain(pos, (int)TerrainType::dirt*0x10 + Random()%0x10);
      } else if (0 < GetHeight(pos)) {
        SetTerrain(pos, (int)TerrainType::sand*0x10 + Random()%0x10);
      } else if (-32 < GetHeight(pos)) {
        SetTerrain(pos, (int)TerrainType::shallow_sea*0x10 - ((GetHeight(pos)/2)%0x10));
        SetHeight(pos, -1);
      } else if (-58 < GetHeight(pos)) {
        SetTerrain(pos, (int)TerrainType::deep_sea*0x10 - ((GetHeight(pos)/2)%0x10));
        SetHeight(pos, -1);
      } else {
        SetTerrain(pos, (int)TerrainType::deep_sea*0x10 + 0x0c);
        SetHeight(pos, -1);
      }
    }
  }
}

void LocalPlace::CategorizeTerrainByGrass() {
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      if (GetTerrainType(pos) == TerrainType::dirt) {
        if (48 < GetGrass(pos)) {
          if (Random()%32)
            SetTerrain(pos, (int)TerrainType::forest*0x10 + Random()%0x08+0x08);
        } else if (32 < GetGrass(pos) && GetGrass(pos) <= 48) {
          if (Random()%16)
            SetTerrain(pos, (int)TerrainType::forest*0x10 + Random()%0x08);
        } else if (16 < GetGrass(pos) && GetGrass(pos) <= 32) {
          if (Random()%8)
            SetTerrain(pos, (int)TerrainType::grass*0x10 + Random()%0x08+0x08);
        } else if (8 < GetGrass(pos) && GetGrass(pos) <= 16) {
          if (Random()%4)
            SetTerrain(pos, (int)TerrainType::grass*0x10 + Random()%0x08);
        } else if (2 < GetGrass(pos) && GetGrass(pos) <= 8) {
          if (!(Random()%32))
            SetTerrain(pos, (int)TerrainType::grass*0x10 + Random()%0x08);
        } else if (GetGrass(pos) == 0) {
          if (Random()%2 * Random()%2) {
            if (Random()%2) {
              SetTerrain(pos, (int)TerrainType::wasteland*0x10 + Random()%0x08);
            } else {
              SetTerrain(pos, (int)TerrainType::sand*0x10 + Random()%0x08);
            }
          }
        }
      }
    }
  }
}

void LocalPlace::FinalizeHeight(const int& divider) {
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      SetHeight(pos, GetHeight(pos)/divider);
    }
  }
}

void LocalPlace::PlantTreesByTerrainType() {
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      if (GetTerrainType(pos) == TerrainType::forest) {
        if (!(IsOccupied(pos)) && (!(Random()%8))) {
          if (!(Random()%8192)) {
            CreatePinkTree(pos);
          } else if (Random()%8) {
            CreateGreenTree(pos);
          } else {
            CreateYellowTree(pos);
          }
        }
      } else if (GetTerrainType(pos) == TerrainType::grass) {
        if (!(IsOccupied(pos)) && (!(Random()%32))) {
          if (!(Random()%1024)) {
            CreatePinkTree(pos);
          } else if (Random()%8) {
            CreateYellowTree(pos);
          } else {
            CreateGreenTree(pos);
          }
        }
      } else if (GetTerrainType(pos) == TerrainType::dirt) {
        if (!(IsOccupied(pos)) && (!(Random()%128))) {
          CreateYellowTree(pos);
        }
      } else if (GetTerrainType(pos) == TerrainType::snow) {
        if (!(IsOccupied(pos)) && (!(Random()%128))) {
          if (!(Random()%512)) {
            CreatePinkTree(pos);
          } else {
            CreateWhiteTree(pos);
          }
        }
      }
    }
  }
}

void LocalPlace::AccumulateHeight(HexPos pos, const int& amount, int max_increaser) {
  HexPos lowest;
  if (max_increaser < 3) max_increaser = 3;
  for (int i = 0; i<amount; ++i) {
    SetHeight(pos, GetHeight(pos)+1);
    lowest = FindLowest(pos);
    SetHeight(pos, GetHeight(pos)-1);
    SetHeight(lowest, GetHeight(lowest)+Random()%max_increaser+1);
  }
}

void LocalPlace::AccumulateGrass(HexPos pos, const int& amount, int max_increaser) {
  HexPos grassless;
  if (max_increaser < 3) max_increaser = 3;
  for (int i = 0; i<amount; ++i) {
    if (GetTerrainType(pos) == TerrainType::dirt) {
      SetGrass(pos, GetGrass(pos)+1);
      grassless = FindGrassless(pos);
      SetGrass(pos, GetGrass(pos)-1);
      SetGrass(grassless, GetGrass(grassless)+Random()%max_increaser+1);
    }
  }
}

void LocalPlace::RandomizeTerrain() {
  RandomizeTerrain((LandType)(Random()%number_of_land_types));
}

void LocalPlace::RandomizeTerrain(const LandType& type) {
  HexPos pos;
  int cols = GetCols();
  int rows = GetRows();
  ClearObject();
  if (type == LandType::space) {
    // 우주 지형
    PlainizeHeight(0, 0, cols-1, rows-1, 0);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    SetName("우주");
    for (int y = 0; y < GetRows(); ++y) {
      pos.set_y(y);
      for (int x = 0; x < GetCols(); ++x) {
        pos.set_x(x);
        if (!(Random()%1024)) {
          SetTerrain(pos, (int)TerrainType::space*0x10 + Random()%4);
        } else if (Random()%32) {
          SetTerrain(pos, (int)TerrainType::space*0x10 + 12 + Random()%4);
        } else if (Random()%8) {
          SetTerrain(pos, (int)TerrainType::space*0x10 + 8 + Random()%4);
        } else {
          SetTerrain(pos, (int)TerrainType::space*0x10 + 4 + Random()%4);
        }
      }
    }
  } else if (type == LandType::sky) {
    // 하늘 지형
    SetName("하늘");
    PlainizeHeight(0, 0, cols-1, rows-1, 0);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    for (int y = 0; y < GetRows(); ++y) {
      pos.set_y(y);
      for (int x = 0; x < GetCols(); ++x) {
        pos.set_x(x);
        if (!(Random()%1024)) {
          SetTerrain(pos, (int)TerrainType::sky*0x10 + Random()%4);
        } else if (Random()%32) {
          SetTerrain(pos, (int)TerrainType::sky*0x10 + 12 + Random()%4);
        } else if (Random()%8) {
          SetTerrain(pos, (int)TerrainType::sky*0x10 + 8 + Random()%4);
        } else {
          SetTerrain(pos, (int)TerrainType::sky*0x10 + 4 + Random()%4);
        }
      }
    }
  } else if (type == LandType::island) {
    // 섬 지형
    SetName("섬");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, -64);
    PlainizeGrass(0, 0, cols-1, rows-1, 4);
    RandomizeHeight(6);
    RandomizeGrass(4);
    // 지형 생성
    for (int i = 0; i<Random()%4+1; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateHeight(pos, Random()%2400+2000, Random()%8+4);
    }
    for (int i = 0; i<Random()%10+24; ++i) {
      pos.set_x(Random()%(cols/2)+cols/4);
      pos.set_y(Random()%(rows/2)+rows/4);
      AccumulateHeight(pos, Random()%4500+7000, Random()%8+4);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%20+20; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%5000+1200, Random()%4);
    }
    CategorizeTerrainByGrass();
    FinalizeHeight(0x10);
    PlantTreesByTerrainType();
  } else if (type == LandType::coast_west) {
    // 서쪽 해안 지형
    SetName("서쪽 해안");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, -64);
    PlainizeHeight(cols-1-Random()%20+6, 0, cols-1, rows-1, 0);
    PlainizeGrass(0, 0, cols-1, rows-1, 4);
    RandomizeHeight(6);
    RandomizeGrass(4);
    // 지형 생성
    for (int i = 0; i<Random()%10+30; ++i) {
      pos.set_x(cols-1-Random()%(cols/4));
      pos.set_y(Random()%rows);
      AccumulateHeight(pos, Random()%4000+8000, Random()%4+2);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%10+40; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%4000+1000, Random()%4);
    }
    CategorizeTerrainByGrass();
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else if (type == LandType::coast_east) {
    // 동쪽 해안 지형
    SetName("동쪽 해안");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, -64);
    PlainizeHeight(0, 0, Random()%20, rows-1, 1);
    PlainizeGrass(0, 0, cols-1, rows-1, 4);
    RandomizeHeight(6);
    RandomizeGrass(4);
    // 지형 생성
    for (int i = 0; i<Random()%10+30; ++i) {
      pos.set_x(Random()%(cols/4));
      pos.set_y(Random()%rows);
      AccumulateHeight(pos, Random()%4000+8000, Random()%4+2);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%10+40; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%4000+1000, Random()%4);
    }
    CategorizeTerrainByGrass();
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else if (type == LandType::coast_north) {
    // 북쪽 해안 지형
    SetName("북쪽 해안");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, -64);
    PlainizeHeight(0, rows-1-Random()%20+6, cols-1, rows-1, 0);
    PlainizeGrass(0, 0, cols-1, rows-1, 4);
    RandomizeHeight(6);
    RandomizeGrass(4);
    // 지형 생성
    for (int i = 0; i<Random()%10+30; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(rows - 1 - Random()%(rows/4));
      AccumulateHeight(pos, Random()%4000+8000, Random()%4+2);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%10+40; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%4000+1000, Random()%4);
    }
    CategorizeTerrainByGrass();
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else if (type == LandType::coast_south) {
    // 남쪽 해안 지형
    SetName("남쪽 해안");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, -64);
    PlainizeHeight(0, 0, cols-1, Random()%20+6, 0);
    PlainizeGrass(0, 0, cols-1, rows-1, 4);
    RandomizeHeight(6);
    RandomizeGrass(4);
    // 지형 생성
    for (int i = 0; i<Random()%10+30; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%(cols/4));
      AccumulateHeight(pos, Random()%4000+8000, Random()%4+2);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%10+40; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%4000+1000, Random()%4);
    }
    CategorizeTerrainByGrass();
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else if (type == LandType::ocean) {
    // 바다 지형
    SetName("바다");
    PlainizeHeight(0, 0, cols-1, rows-1, 0);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    for (int y = 0; y < GetRows(); ++y) {
      pos.set_y(y);
      for (int x = 0; x < GetCols(); ++x) {
        pos.set_x(x);
        SetTerrain(pos, (int)TerrainType::deep_sea*0x10 + 12 + Random()%4);
      }
    }
  } else if (type == LandType::volcano) {
    // 화산 지형
    SetName("화산");
    int lava_count = 0;
    while(lava_count < 128) {
      // 지형 평준화
      PlainizeHeight(0, 0, cols-1, rows-1, 32);
      PlainizeGrass(0, 0, cols-1, rows-1, 4);
      RandomizeHeight(20);
      RandomizeGrass(4);
      // 지형 생성
      for (int i = 0; i<Random()%4+2; ++i) {
        pos.set_x(Random()%cols);
        pos.set_y(Random()%rows);
        AccumulateHeight(pos, Random()%1000+200, Random()%4+4);
      }
      for (int i = 0; i<Random()%16+16; ++i) {
        pos.set_x(Random()%(cols/2)+cols/4);
        pos.set_y(Random()%(rows/2)+rows/4);
        AccumulateHeight(pos, Random()%3000+6000, Random()%8+12);
      }
      CategorizeTerrainByHeight();
      // 수풀 생성
      for (int i = 0; i<Random()%16+8; ++i) {
        pos.set_x(Random()%cols);
        pos.set_y(Random()%rows);
        AccumulateGrass(pos, Random()%2000+2000, Random()%4);
      }
      CategorizeTerrainByGrass();
      // 분화구 생성
      lava_count = 0;
      for (int y = 0; y < rows; ++y) {
        pos.set_y(y);
        for (int x = 0; x < cols; ++x) {
          pos.set_x(x);
          if (150 < GetHeight(pos)) {
            SetTerrain(pos, (int)TerrainType::lava*0x10 + Random()%0x10);
            SetHeight(pos, 80 - (GetHeight(pos) - 80));
            ++lava_count;
          }
        }
      }
    }
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else if (type == LandType::mountain) {
    // 산 지형
    SetName("산");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, 40);
    PlainizeGrass(0, 0, cols-1, rows-1, 6);
    RandomizeHeight(12);
    RandomizeGrass(3);
    // 지형 생성
    for (int i = 0; i<Random()%16+32; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateHeight(pos, Random()%4000+6000, Random()%8+8);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%8+30; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%4000+4000, Random()%4);
    }
    CategorizeTerrainByGrass();
    PlantTreesByTerrainType();
    FinalizeHeight(0x08);
  } else if (type == LandType::wasteland) {
    // 폐허 지형
    SetName("폐허");
    PlainizeHeight(0, 0, cols-1, rows-1, 0);
    RandomizeHeight(3);
    RandomizeGrass(5);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    for (int y = 0; y < GetRows(); ++y) {
      pos.set_y(y);
      for (int x = 0; x < GetCols(); ++x) {
        pos.set_x(x);
        SetTerrain(pos, (int)TerrainType::wasteland*0x10 + Random()%0x10);
      }
    }
    FinalizeHeight(0x10);
  } else if (type == LandType::forest) {
    // 숲 지형
    SetName("숲");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, 40);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    RandomizeHeight(7);
    RandomizeGrass(16);
    // 지형 생성
    for (int i = 0; i<Random()%10+10; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateHeight(pos, Random()%1000+1000, Random()%4);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%8+32; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%4000+10000, Random()%8+4);
    }
    CategorizeTerrainByGrass();
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else if (type == LandType::desert) {
    // 사막 지형
    SetName("사막");
    PlainizeHeight(0, 0, cols-1, rows-1, 8);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    RandomizeHeight(2);
    RandomizeGrass(5);
    for (int y = 0; y < GetRows(); ++y) {
      pos.set_y(y);
      for (int x = 0; x < GetCols(); ++x) {
        pos.set_x(x);
        SetTerrain(pos, (int)TerrainType::desert*0x10 + Random()%0x10);
      }
    }
    FinalizeHeight(0x10);
  } else if (type == LandType::snowland) {
    // 설원 지형
    SetName("설원");
    PlainizeHeight(0, 0, cols-1, rows-1, 8);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    RandomizeHeight(2);
    RandomizeGrass(5);
    for (int y = 0; y < GetRows(); ++y) {
      pos.set_y(y);
      for (int x = 0; x < GetCols(); ++x) {
        pos.set_x(x);
        SetTerrain(pos, (int)TerrainType::snow*0x10 + Random()%0x10);
      }
    }
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else if (type == LandType::swamp) {
    // 늪 지형
    SetName("늪");
    // 지형 평준화
    PlainizeHeight(0, 0, cols-1, rows-1, 40);
    PlainizeGrass(0, 0, cols-1, rows-1, 0);
    RandomizeHeight(7);
    RandomizeGrass(16);
    // 지형 생성
    for (int i = 0; i<Random()%10+10; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateHeight(pos, Random()%1000+1000, Random()%4);
    }
    CategorizeTerrainByHeight();
    // 수풀 생성
    for (int i = 0; i<Random()%8+32; ++i) {
      pos.set_x(Random()%cols);
      pos.set_y(Random()%rows);
      AccumulateGrass(pos, Random()%8000+20000, Random()%8+4);
    }
    CategorizeTerrainByGrass();
    // 늪지 생성
    for (int y = 0; y < rows; ++y) {
      pos.set_y(y);
      for (int x = 0; x < cols; ++x) {
        pos.set_x(x);
        if (GetTerrainType(pos) == TerrainType::grass) {
          if (!(Random()%8)) SetTerrain(pos, (int)TerrainType::swamp*0x10 + Random()%0x10);
          SetHeight(pos, GetHeight(pos) - 4);
        } else if (GetTerrainType(Coord(x,y)) == TerrainType::forest) {
          if (!(Random()%4)) SetTerrain(pos, (int)TerrainType::swamp*0x10 + Random()%0x10);
          SetHeight(pos, GetHeight(pos) - 4);
        }
      }
    }
    PlantTreesByTerrainType();
    FinalizeHeight(0x10);
  } else {
    ;
  }
}

void LocalPlace::RandomizeWall() {
    int density = Random()%20 - 2;
    HexPos pos;
    for (int y = 0; y < GetRows(); ++y) {
        pos.set_y(y);
        for (int x = 0; x < GetCols(); ++x) {
            pos.set_x(x);
            if (Random()%20 < density && !(IsOccupied(pos))) {
                CreateWall(pos);
            } else {
                RemoveObject(pos);
            }
        }
    }
}




















































LocalPlace::LocalPlaceCell::LocalPlaceCell()
    : terrain(-1),
      height(0),
      grass(0),
      object(-1),
      creature_id(-1) {
}
LocalPlace::LocalPlaceCell::LocalPlaceCell(const int& terrain,
                                     const int& height,
                                     const int& grass,
                                     const int& object,
                                     const int& creature_id)
    : terrain(terrain),
      height(height),
      grass(grass),
      object(object),
      creature_id(creature_id) {
}
LocalPlace::LocalPlaceCell::~LocalPlaceCell() {
}

const bool LocalPlace::LocalPlaceCell::IsOccupied() const {
  if (object != -1) return true;
  if (creature_id != -1) return true;
  return false;
}
