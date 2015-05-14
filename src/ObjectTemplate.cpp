#include "ObjectTemplate.h"

ObjectTemplate::ObjectTemplate(const ObjectType& type,
                               const std::string& name,
                               const TileRef& tile,
                               const TileRef& tile_fog,
                               const SDL_Color& color)
    : type(type),
      name(name),
      tile(tile),
      tile_fog(tile_fog),
      color(color) {
};
