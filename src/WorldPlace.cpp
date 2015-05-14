#include "WorldPlace.h"

// 생성자 및 소멸자
WorldPlace::WorldPlace()
    : cols(0),
      rows(0),
      size(0) {
}
WorldPlace::WorldPlace(const int& cols, const int& rows)
    : cols(cols),
      rows(rows),
      size(cols*rows) {
  for (int i = 0; i < size; ++i) {
    cells.push_back(new WorldPlaceCell());
  }
}
WorldPlace::~WorldPlace() {
  Clear();
}

void WorldPlace::CreateNewPlace(const int& cols, const int& rows) {
  Clear();
  this->cols = cols;
  this->rows = rows;
  size = cols*rows;
  for (int i = 0; i < size; ++i) {
    cells.push_back(new WorldPlaceCell());
  }
}

void WorldPlace::Clear() {
  for (auto it = cells.begin(); it != cells.end(); ++it)
    delete *it;
  cells.clear();
  rows = 0;
  cols = 0;
  size = 0;
}

// 셀 데이터 검사 함수
const bool WorldPlace::IsOutOfRange(const Coord& pos) const {
  if (pos.x() < 0 || pos.x() >= cols) {
    return true;
  } else if (pos.y() < 0 || pos.y() >= rows) {
    return true;
  } else {
    return false;
  }
}
const bool WorldPlace::IsPassable(const Coord& mover_pos,
                                const Coord& target_pos,
                                const MoveType& move_type) const {
  if (GetTerrain(target_pos) == WorldTerrainType::ice) return false;
  if (GetTerrain(target_pos) == WorldTerrainType::ocean) return false;
  if (GetTerrain(target_pos) == WorldTerrainType::sea) return false;
  if (GetTerrain(target_pos) == WorldTerrainType::river) return false;
  if (GetTerrain(target_pos) == WorldTerrainType::mountain) return false;
  if (GetTerrain(target_pos) == WorldTerrainType::volcano) return false;
  if (GetTerrain(target_pos) == WorldTerrainType::lava) return false;
  return true;
}

const int& WorldPlace::GetCols() const {
  return cols;
}
const int& WorldPlace::GetRows() const {
  return rows;
}
const int& WorldPlace::GetSize() const {
  return size;
}

const WorldTerrainType& WorldPlace::GetTerrain(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->terrain;
}
const WorldObjectType& WorldPlace::GetObject(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->object;
}
const int& WorldPlace::GetHeight(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->height;
}
const int& WorldPlace::GetGrass(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->grass;
}
const string& WorldPlace::GetTerrainName(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->terrain_name;
}
const string& WorldPlace::GetObjectName(const Coord& pos) const {
  return cells[pos.y()*cols+pos.x()]->object_name;
}
const TileRef WorldPlace::GetTerrainTile(const Coord& pos) const {
  TileRef tile;
  tile.set = TilesetType::world;
  tile.id = (int)cells[pos.y()*cols+pos.x()]->terrain;
  return tile;
}
const TileRef WorldPlace::GetObjectTile(const Coord& pos) const {
  TileRef tile;
  tile.set = TilesetType::world;
  tile.id = 0x40 + (int)cells[pos.y()*cols+pos.x()]->object;
  return tile;
}
const string& WorldPlace::GetName() const {
  return name;
}

const bool WorldPlace::SetTerrain(const Coord& pos, const WorldTerrainType& terrain) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->terrain = terrain;
  return true;
}
const bool WorldPlace::SetObject(const Coord& pos, const WorldObjectType& object) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->object = object;
  return true;
}
const bool WorldPlace::SetHeight(const Coord& pos, const int& height) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->height = height;
  return true;
}
const bool WorldPlace::SetGrass(const Coord& pos, const int& grass) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->grass = grass;
  return true;
}
const bool WorldPlace::SetTerrainName(const Coord& pos, const string& name) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->terrain_name = name;
  return true;
}
const bool WorldPlace::SetObjectName(const Coord& pos, const string& name) {
  if (IsOutOfRange(pos)) return false;
  cells[pos.y()*cols+pos.x()]->object_name = name;
  return true;
}
void WorldPlace::SetName(const string& name) {
  this->name = name;
}

const bool WorldPlace::RemoveTerrain(const Coord& pos) {
  if (IsOutOfRange(pos)) return false;
  SetTerrain(pos, WorldTerrainType::none);
  return true;
}
const bool WorldPlace::RemoveObject(const Coord& pos) {
  if (IsOutOfRange(pos)) return false;
  SetObject(pos, WorldObjectType::none);
  return true;
}

void WorldPlace::ClearObject() {
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
HexPos WorldPlace::FindLowest(HexPos& pos) {
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

HexPos WorldPlace::FindGrassless(HexPos& pos) {
    HexPos neib, grassless;
    grassless = pos;
    neib = pos;
    neib.MoveTo(HexDir::nwest);
    if ((!IsOutOfRange(neib)) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::neast);
    if ((!IsOutOfRange(neib)) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::west);
    if ((!IsOutOfRange(neib)) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::east);
    if ((!IsOutOfRange(neib)) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::swest);
    if ((!IsOutOfRange(neib)) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;
    neib = pos;
    neib.MoveTo(HexDir::seast);
    if ((!IsOutOfRange(neib)) &&
        (GetGrass(neib) < GetGrass(grassless)))
      grassless = neib;

    if (pos == grassless) {
      return grassless;
    } else {
      return FindGrassless(grassless);
    }
}

void WorldPlace::PlainizeHeight(const int& start_x, const int& start_y,
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

void WorldPlace::PlainizeGrass(const int& start_x, const int& start_y,
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

void WorldPlace::RandomizeHeight(int max_increaser) {
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

void WorldPlace::RandomizeGrass(int max_increaser) {
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

void WorldPlace::CategorizeTerrain() {
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      if (200 < GetHeight(pos)) {
          SetTerrain(pos, WorldTerrainType::mountain);
      } else if (160 < GetHeight(pos) && GetHeight(pos) <= 200) {
        if (Random()%64) {
          SetTerrain(pos, WorldTerrainType::mountain);
        } else {
          SetTerrain(pos, WorldTerrainType::hill);
        }
      } else if (140 < GetHeight(pos) && GetHeight(pos) <= 160) {
        if (Random()%32) {
          SetTerrain(pos, WorldTerrainType::mountain);
        } else {
          SetTerrain(pos, WorldTerrainType::hill);
        }
      } else if (100 < GetHeight(pos) && GetHeight(pos) <= 140) {
        if (Random()%8) {
          SetTerrain(pos, WorldTerrainType::mountain);
        } else {
          SetTerrain(pos, WorldTerrainType::hill);
        }
      } else if (80 < GetHeight(pos) && GetHeight(pos) <= 100) {
        if (Random()%4) {
          SetTerrain(pos, WorldTerrainType::mountain);
        } else {
          SetTerrain(pos, WorldTerrainType::hill);
        }
      } else if (60 < GetHeight(pos) && GetHeight(pos) <= 80) {
        if (Random()%8) {
          SetTerrain(pos, WorldTerrainType::hill);
        } else {
          SetTerrain(pos, WorldTerrainType::dirt);
        }
      } else if (2 < GetHeight(pos) && GetHeight(pos) <= 60) {
        if (Random()%32) {
          SetTerrain(pos, WorldTerrainType::dirt);
        } else {
          SetTerrain(pos, WorldTerrainType::hill);
        }
      } else if (0 < GetHeight(pos) && GetHeight(pos) <= 2) {
        if (Random()%8) {
          SetTerrain(pos, WorldTerrainType::beach);
        } else {
          SetTerrain(pos, WorldTerrainType::dirt);
        }
      } else if (-20 < GetHeight(pos) && GetHeight(pos) <= 0) {
        SetTerrain(pos, WorldTerrainType::sea);
      } else {
        SetTerrain(pos, WorldTerrainType::ocean);
      }
      if ( GetTerrain(pos) == WorldTerrainType::dirt) {
        if (60 < GetGrass(pos)) {
          SetTerrain(pos, WorldTerrainType::jungle);
        } else if (50 < GetGrass(pos) && GetGrass(pos) <= 60) {
          if (Random()%8) {
            SetTerrain(pos, WorldTerrainType::jungle);
          } else {
            SetTerrain(pos, WorldTerrainType::forest);
          }
        } else if (40 < GetGrass(pos) && GetGrass(pos) <= 50) {
          if (Random()%8) {
            SetTerrain(pos, WorldTerrainType::forest);
          } else {
            SetTerrain(pos, WorldTerrainType::jungle);
          }
        } else if (30 < GetGrass(pos) && GetGrass(pos) <= 40) {
          if (Random()%8) {
            SetTerrain(pos, WorldTerrainType::forest);
          } else {
            SetTerrain(pos, WorldTerrainType::grass);
          }
        } else if (20 < GetGrass(pos) && GetGrass(pos) <= 30) {
          if (Random()%8) {
            if (Random()%8) {
              SetTerrain(pos, WorldTerrainType::grass);
            } else {
              SetTerrain(pos, WorldTerrainType::river);
            }
          } else {
            SetTerrain(pos, WorldTerrainType::forest);
          }
        } else if (3 < GetGrass(pos) && GetGrass(pos) <= 20) {
          if (Random()%8) {
            SetTerrain(pos, WorldTerrainType::dirt);
          } else {
            SetTerrain(pos, WorldTerrainType::grass);
          }
        } else {
          SetTerrain(pos, WorldTerrainType::sand);
        }
      }
    }
  }
}

void WorldPlace::AccumulateHeight(HexPos pos, const int& amount, int max_increaser) {
  HexPos lowest;
  if (max_increaser < 3) max_increaser = 3;
  for (int i = 0; i<amount; ++i) {
    SetHeight(pos, GetHeight(pos)+1);
    lowest = FindLowest(pos);
    SetHeight(pos, GetHeight(pos)-1);
    SetHeight(lowest, GetHeight(lowest)+Random()%max_increaser+1);
  }
}

void WorldPlace::AccumulateGrass(HexPos pos, const int& amount, int max_increaser) {
  HexPos grassless;
  if (max_increaser < 3) max_increaser = 3;
  for (int i = 0; i<amount; ++i) {
    SetGrass(pos, GetGrass(pos)+1);
    grassless = FindGrassless(pos);
    SetGrass(pos, GetGrass(pos)-1);
    SetGrass(grassless, GetGrass(grassless)+Random()%max_increaser+1);
  }
}

void WorldPlace::FinalizeHeight(const int& divider) {
  HexPos pos;
  for (int y = 0; y < GetRows(); ++y) {
    pos.set_y(y);
    for (int x = 0; x < GetCols(); ++x) {
      pos.set_x(x);
      SetHeight(pos, GetHeight(pos)/divider);
    }
  }
}

void WorldPlace::RandomizeTerrain() {
  HexPos pos;
  int cols = GetCols();
  int rows = GetRows();
  ClearObject();
  SetName("대륙");
  // 지형 평준화
  PlainizeHeight(0, 0, cols-1, rows-1, -64);
  PlainizeGrass(0, 0, cols-1, rows-1, -10);
  RandomizeHeight(6);
  RandomizeGrass(6);
  // 지형 생성
  for (int i = 0; i<Random()%20+40; ++i) {
    pos.set_x(Random()%cols);
    pos.set_y(Random()%rows);
    AccumulateHeight(pos, Random()%2000+2000, Random()%8+8);
  }
  for (int i = 0; i<Random()%20+40; ++i) {
    pos.set_x(Random()%(cols/2)+cols/4);
    pos.set_y(Random()%(rows/2)+rows/4);
    AccumulateHeight(pos, Random()%4000+5000, Random()%8+8);
  }
  // 수풀 생성
  for (int i = 0; i<Random()%80+100; ++i) {
    pos.set_x(Random()%cols);
    pos.set_y(Random()%rows);
    AccumulateGrass(pos, Random()%4000+2000, Random()%8+4);
  }
  CategorizeTerrain();
}

WorldPlace::WorldPlaceCell::WorldPlaceCell()
    : terrain(WorldTerrainType::none),
      terrain_name(""),
      object(WorldObjectType::none),
      object_name(""),
      height(0),
      grass(0) {
}
WorldPlace::WorldPlaceCell::WorldPlaceCell(const WorldTerrainType& terrain,
                                           const string& terrain_name,
                                           const WorldObjectType& object,
                                           const string& object_name,
                                           const int& height,
                                           const int& grass)
    : terrain(terrain),
      terrain_name(terrain_name),
      object(object),
      object_name(object_name),
      height(height),
      grass(grass) {
}
WorldPlace::WorldPlaceCell::~WorldPlaceCell() {
}
