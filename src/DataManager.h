#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "libs.h"
#include "ObjectTemplate.h"
#include "TerrainTemplate.h"

extern const string src_creature_template;
extern const string src_object_template;

extern vector<ObjectTemplate> object_template;
extern vector<TerrainTemplate> terrain_template;

void LoadObjectTemplate();
void LoadTerrainTemplate();


#endif // DATAMANAGER_H
