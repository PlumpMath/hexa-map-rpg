#ifndef TERRAINTYPE_H
#define TERRAINTYPE_H

enum class TerrainType : int {
  none          =  -1,
  space         =   0,
  sky           =   1,
  shallow_water =   2,
  deep_water    =   3,
  shallow_sea   =   4,
  deep_sea      =   5,
  sand          =   6,
  desert        =   7,
  wasteland     =   8,
  dirt          =   9,
  grass         =  10,
  forest        =  11,
  swamp         =  12,
  lava          =  13,
  snow          =  14,
  paper         =  15,
  cyber         =  16,
};

#endif // TERRAINTYPE_H
