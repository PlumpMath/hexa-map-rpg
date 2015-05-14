#include "TerrainTemplate.h"

TerrainTemplate::TerrainTemplate(const TerrainType& type,
                                 const string& name,
                                 const TileRef& floor,
                                 const TileRef& floor_fog,
                                 const TileRef& side,
                                 const TileRef& side_fog,
                                 const SDL_Color& color,
                                 const bool& is_liquid)
    : type(type),
      name(name),
      floor(floor),
      floor_fog(floor_fog),
      side(side),
      side_fog(side_fog),
      color(color),
      is_liquid(is_liquid) {
}

