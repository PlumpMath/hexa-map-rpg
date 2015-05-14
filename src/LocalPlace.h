#ifndef LOCALPLACE_H
#define LOCALPLACE_H

#include "libs.h"
#include "types.h"
#include "Random.h"
#include "DataManager.h"
#include "TerrainTemplate.h"
#include "ObjectTemplate.h"
#include "LandType.h"
#include "Coord.h"
#include "MoveType.h"
#include "HexPos.h"

class LocalPlace {
protected:
  class LocalPlaceCell {
    friend class LocalPlace;
  protected:
    int terrain;
    int height;
    int grass;
    int object;
    int creature_id;

  public:
    LocalPlaceCell();
    LocalPlaceCell(const int& terrain, const int& height, const int& grass,
                   const int& object, const int& creature_id);
    virtual ~LocalPlaceCell();

  public:
    // 통행가능, 시야가능 함수 미완성
    const bool IsOccupied() const;
  };

protected:
  // 맵 이름
  string name;

  // 맵 크기
  int cols;
  int rows;
  int size;

  // 셀 배열
  vector<LocalPlaceCell*> cells;

public:
  // 생성자 및 소멸자
  LocalPlace();
  LocalPlace(const int& cols, const int& rows);
  virtual ~LocalPlace();

  // 연산자
//    virtual const LocalPlaceCell* operator[](const Coord& pos) const;

private:
  // 복사 금지
  LocalPlace& operator=(const LocalPlace& r_right_object);
  LocalPlace(const LocalPlace& r_source_object);

public:
  const int& GetCols() const;
  const int& GetRows() const;
  const int& GetSize() const;

  void CreateNewPlace(const int& cols, const int& rows);
  void Clear();

  // 셀 검사 함수
  const bool IsOutOfRange(const Coord& pos) const;
  const bool IsOccupied(const Coord& pos) const;
  const bool IsPassable(const Coord& mover_pos, const Coord& target_pos, const MoveType& move_type) const;
  const bool IsSeeable(const Coord& seer_pos, const Coord& target_pos) const;

  // 셀 데이터 접근 함수
  const bool HasTerrain(const Coord& pos) const;
  const bool HasObject(const Coord& pos) const;
  const bool HasCreature(const Coord& pos) const;

  const int& GetTerrain(const Coord& pos) const;
  const int& GetHeight(const Coord& pos) const;
  const int& GetGrass(const Coord& pos) const;
  const int& GetObject(const Coord& pos) const;
  const int& GetCreatureId(const Coord& pos) const;
  bool GetTerrainTypeLiq(const Coord& pos) const;

  const bool SetTerrain(const Coord& pos, const int& terrain);
  const bool SetHeight(const Coord& pos, const int& height);
  const bool SetGrass(const Coord& pos, const int& grass);
  const bool SetObject(const Coord& pos, const int& object);
  const bool SetCreatureId(const Coord& pos, const int& creature_id);
  void SetName(const string&);

  const TerrainType& GetTerrainType(const Coord& pos) const;
  const string& GetTerrainName(const Coord& pos) const;
  const TileRef& GetFloorTile(const Coord& pos) const;
  const TileRef& GetFloorFogTile(const Coord& pos) const;
  const TileRef& GetSideTile(const Coord& pos) const;
  const TileRef& GetSideFogTile(const Coord& pos) const;
  const SDL_Color& GetTerrainColor(const Coord& pos) const;
  const bool& GetSink(const Coord& pos) const;
  const string& GetName() const;

// 랜덤 맵 편집 관련 함수
  const bool CreateObject(const Coord& pos, const int& object);
  const bool CreateCreature(const Coord& pos, const int& template_id);
  const bool RemoveTerrain(const Coord& pos);
  const bool RemoveObject(const Coord& pos);
  const bool RemoveCreature(const Coord& pos);

  void ClearObject();
  void ClearCreature();
  const bool CreateWall(const Coord& pos);
  const bool CreateGreenTree(const Coord& pos);
  const bool CreateYellowTree(const Coord& pos);
  const bool CreatePinkTree(const Coord& pos);
  const bool CreateWhiteTree(const Coord& pos);
  void DrawPool(const Coord& pos, const int& w, const int& h);
  void DrawObjectRectangleA(const Coord& pos, const int& w, const int& h, const int& object);
  void DrawObjectRectangleB(const Coord& pos, const int& w, const int& h, const int& object);
  void DrawObjectRectangleC(const Coord& pos, const int& w, const int& h, const int& object);
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
  void CategorizeTerrainByHeight();
  void CategorizeTerrainByGrass();
  void PlantTreesByTerrainType();
  void RandomizeTerrain();
  void RandomizeTerrain(const LandType& type);
  void RandomizeWall();
  void ClearPlace();
};

#endif // LOCALPLACE_H
