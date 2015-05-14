#ifndef WORLDPLACE_H
#define WORLDPLACE_H

#include "libs.h"
#include "types.h"
#include "Random.h"
#include "TileRef.h"
#include "WorldTerrainType.h"
#include "WorldObjectType.h"
#include "Coord.h"
#include "MoveType.h"
#include "HexPos.h"

using namespace std;

class WorldPlace {
protected:
  class WorldPlaceCell {
    friend class WorldPlace;
  protected:
    WorldTerrainType terrain;
    string terrain_name;
    WorldObjectType object;
    string object_name;
    int height;
    int grass;

  public:
    WorldPlaceCell();
    WorldPlaceCell(const WorldTerrainType& terrain, const string& terrain_name,
                   const WorldObjectType& object, const string& object_name,
                   const int& height, const int& grass);
    virtual ~WorldPlaceCell();
  };

protected:
  // 맵 이름
  string name;

  // 맵 크기
  int cols;
  int rows;
  int size;

  // 셀 배열
  vector<WorldPlaceCell*> cells;

public:
  // 생성자 및 소멸자
  WorldPlace();
  WorldPlace(const int& cols, const int& rows);
  virtual ~WorldPlace();

  // 연산자
//    virtual const LocalPlaceCell* operator[](const Coord& pos) const;

private:
  // 복사 금지
  WorldPlace& operator=(const WorldPlace& r_right_object);
  WorldPlace(const WorldPlace& r_source_object);

public:
  const int& GetCols() const;
  const int& GetRows() const;
  const int& GetSize() const;

  void CreateNewPlace(const int& cols, const int& rows);
  void Clear();

  // 셀 검사 함수
  const bool IsOutOfRange(const Coord& pos) const;
  const bool IsPassable(const Coord& mover_pos, const Coord& target_pos, const MoveType& move_type) const;

  const WorldTerrainType& GetTerrain(const Coord& pos) const;
  const WorldObjectType& GetObject(const Coord& pos) const;
  const string& GetTerrainName(const Coord& pos) const;
  const string& GetObjectName(const Coord& pos) const;
  const TileRef GetTerrainTile(const Coord& pos) const;
  const TileRef GetObjectTile(const Coord& pos) const;
  const int& GetHeight(const Coord& pos) const;
  const int& GetGrass(const Coord& pos) const;
  const string& GetName() const;

  const bool SetTerrain(const Coord& pos, const WorldTerrainType& terrain);
  const bool SetObject(const Coord& pos, const WorldObjectType& object);
  const bool SetTerrainName(const Coord& pos, const string& name);
  const bool SetObjectName(const Coord& pos, const string& name);
  const bool SetHeight(const Coord& pos, const int& height);
  const bool SetGrass(const Coord& pos, const int& grass);
  void SetName(const string&);

  const bool RemoveTerrain(const Coord& pos);
  const bool RemoveObject(const Coord& pos);
  void ClearObject();

  // 랜덤 맵 편집 관련 함수
  HexPos FindLowest(HexPos& pos);
  HexPos FindGrassless(HexPos& pos);
  void PlainizeHeight(const int& start_x, const int& start_y,
                    const int& end_x,   const int& end_y,
                    const int& base_height);
  void PlainizeGrass(const int& start_x, const int& start_y,
                     const int& end_x,   const int& end_y,
                     const int& base_grass);
  void RandomizeHeight(int max_increaser);
  void RandomizeGrass(int max_increaser);
  void AccumulateHeight(HexPos pos, const int& amount, int max_increaser);
  void AccumulateGrass(HexPos pos, const int& amount, int max_increaser);
  void FinalizeHeight(const int& divider);
  void CategorizeTerrain();
  void RandomizeTerrain();
  void ClearPlace();
};

#endif // WORLDPLACE_H
