#ifndef CREATURETEMPLATE_H
#define CREATURETEMPLATE_H

#include "libs.h"
#include "types.h"
#include "GenderType.h"
#include "AlignType.h"
#include "TileRef.h"
#include "Color.h"

using namespace std;

const int kNumberOfCretureTemplates = 3;
extern CreatureTemplate creature_template[kNumberOfCretureTemplates];

struct CreatureTemplate {
 public:
  CreatureTemplate(const string&      name,
                   const GenderType&  gender,
                   const int&         age,
                   const AlignType&   alignment,
                   const string&      race_id,
                   const string&      class_id,
                   const int&         level,
                   const int&         hp_base,
                   const int&         strength_base,
                   const int&         constitution_base,
                   const int&         dexterity_base,
                   const int&         intelligence_base,
                   const int&         wisdom_base,
                   const int&         charisma_base,
                   const int&         ac_base,
                   const int&         fortitude_base,
                   const int&         reflex_base,
                   const int&         will_base,
                   const TileRef&     tile,
                   const SDL_Color&   color);

  const string      name;
  const GenderType  gender;
  const int         age;
  const AlignType   alignment;

  const string      race_id;
  const string      class_id;
  const int         level;
  const int         hp_base;
  const int         strength_base;
  const int         constitution_base;
  const int         dexterity_base;
  const int         intelligence_base;
  const int         wisdom_base;
  const int         charisma_base;
  const int         ac_base;
  const int         fortitude_base;
  const int         reflex_base;
  const int         will_base;

  const TileRef     tile;
  const SDL_Color   color;
};


#endif // CREATURETEMPLATE_H
