#ifndef TERRAINTEMPLATE_H
#define TERRAINTEMPLATE_H

#include "libs.h"
#include "types.h"
#include "TerrainType.h"
#include "TileRef.h"
#include "Color.h"

using namespace std;

class TerrainTemplate {
public:
  TerrainType type;
  string name;
  TileRef floor;
  TileRef floor_fog;
  TileRef side;
  TileRef side_fog;
  SDL_Color color;
  bool is_liquid;

  TerrainTemplate(
    const TerrainType& type,
    const string& name,
    const TileRef& floor,
    const TileRef& floor_fog,
    const TileRef& side,
    const TileRef& side_fog,
    const SDL_Color& color,
    const bool& is_liquid
  );
};

#endif // TERRAINTEMPLATE_H
