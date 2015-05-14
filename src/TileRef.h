#ifndef TILEREF_H
#define TILEREF_H

#include "types.h"
#include "TilesetType.h"

class TileRef {
public:
  TilesetType set;
  int id;

public:
  TileRef() : set(TilesetType::terrain), id(0) {
  }
  TileRef(const TilesetType& set, const int& id) : set(set), id(id) {
  }
  TileRef(const TileRef& rh_obj) : set(rh_obj.set), id(rh_obj.id) {
  }
  virtual ~TileRef() {
  }
  const TileRef& operator = (const TileRef& rh_obj) {
    set = rh_obj.set;
    id = rh_obj.id;
    return *this;
  }
};

#endif // TILEREF_H
