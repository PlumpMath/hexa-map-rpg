#include "DataManager.h"

const string src_creature_template("./data/creature_template.dat");
const string src_object_template("./data/object_template.dat");
const string src_terrain_template("./data/terrain_template.dat");

vector<ObjectTemplate> object_template;
vector<TerrainTemplate> terrain_template;

void LoadObjectTemplate() {
  ifstream src(src_object_template, ios_base::in | ios_base::binary);
  if (!src.is_open()) {
    cerr << src_object_template << "파일을 읽을 수 없습니다." << endl;
  }
  int    table_size;
  int    object_type;
  int    name_str_size;
  char   name_str_cont[0x1000];
  int    tileset_0;
  int    tileid_0;
  int    tileset_1;
  int    tileid_1;
  char   color_r;
  char   color_g;
  char   color_b;

  src.read((char*)&table_size, sizeof(int));
  for (int i = 0; i<table_size; ++i) {
    src.read((char*)&object_type, sizeof(int));
    src.read((char*)&name_str_size, sizeof(int));
    src.read((char*)name_str_cont, name_str_size);
    name_str_cont[name_str_size] = '\0';
    src.read((char*)&tileset_0, sizeof(int));
    src.read((char*)&tileid_0, sizeof(int));
    src.read((char*)&tileset_1, sizeof(int));
    src.read((char*)&tileid_1, sizeof(int));
    src.read((char*)&color_r, sizeof(char));
    src.read((char*)&color_g, sizeof(char));
    src.read((char*)&color_b, sizeof(char));
    SDL_Color color = {color_r, color_g, color_b};
    object_template.push_back(ObjectTemplate((ObjectType)object_type,
                                   name_str_cont,
                                   TileRef((TilesetType)tileset_0, tileid_0),
                                   TileRef((TilesetType)tileset_1, tileid_1),
                                   color));
  }
}

void LoadTerrainTemplate() {
  ifstream src(src_terrain_template, ios_base::in | ios_base::binary);
  if (!src.is_open()) {
    cerr << src_terrain_template << "파일을 읽을 수 없습니다." << endl;
  }
  int    table_size;
  int    terrain_type;
  int    name_str_size;
  char   name_str_cont[0x1000];
  int    tileset_0;
  int    tileid_0;
  int    tileset_1;
  int    tileid_1;
  int    tileset_2;
  int    tileid_2;
  int    tileset_3;
  int    tileid_3;
  char   color_r;
  char   color_g;
  char   color_b;
  bool   is_liquid;

  src.read((char*)&table_size, sizeof(int));
  for (int i = 0; i<table_size; ++i) {
    src.read((char*)&terrain_type, sizeof(int));
    src.read((char*)&name_str_size, sizeof(int));
    src.read((char*)name_str_cont, name_str_size);
    name_str_cont[name_str_size] = '\0';
    src.read((char*)&tileset_0, sizeof(int));
    src.read((char*)&tileid_0, sizeof(int));
    src.read((char*)&tileset_1, sizeof(int));
    src.read((char*)&tileid_1, sizeof(int));
    src.read((char*)&tileset_2, sizeof(int));
    src.read((char*)&tileid_2, sizeof(int));
    src.read((char*)&tileset_3, sizeof(int));
    src.read((char*)&tileid_3, sizeof(int));
    src.read((char*)&color_r, sizeof(char));
    src.read((char*)&color_g, sizeof(char));
    src.read((char*)&color_b, sizeof(char));
    src.read((char*)&is_liquid, sizeof(bool));
    SDL_Color color = {color_r, color_g, color_b};
    terrain_template.push_back(TerrainTemplate(
                                   (TerrainType)terrain_type,
                                   name_str_cont,
                                   TileRef((TilesetType)tileset_0, tileid_0),
                                   TileRef((TilesetType)tileset_1, tileid_1),
                                   TileRef((TilesetType)tileset_2, tileid_2),
                                   TileRef((TilesetType)tileset_3, tileid_3),
                                   color,
                                   is_liquid));
  }
}
