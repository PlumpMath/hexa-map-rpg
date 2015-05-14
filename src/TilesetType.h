#ifndef TILESETTYPE_H
#define TILESETTYPE_H

const int number_of_tileset_types = 9;

enum class TilesetType : int {
  none          = -1,
  terrain       =  0, //  지형 타일셋
  terrain_fog   =  1,
  wall          =  2,
  wall_fog      =  3,
  tree          =  4,
  tree_fog      =  5,
  world         =  6,
  creature      =  7, //  캐릭터 타일셋
  grid          =  8,
};


#endif // TILESETTYPE_H
