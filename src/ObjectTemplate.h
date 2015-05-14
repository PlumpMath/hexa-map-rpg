#ifndef OBJECTTEMPLATE_H
#define OBJECTTEMPLATE_H

#include "libs.h"
#include "types.h"
#include "TileRef.h"
#include "ObjectType.h"

class ObjectTemplate {
public:
  ObjectType type;
  std::string name;
  TileRef tile;
  TileRef tile_fog;
  SDL_Color color;

  ObjectTemplate(
    const ObjectType& type,
    const std::string& name,
    const TileRef& tile,
    const TileRef& tile_fog,
    const SDL_Color& color
  );
};

#endif // OBJECTTEMPLATE_H
