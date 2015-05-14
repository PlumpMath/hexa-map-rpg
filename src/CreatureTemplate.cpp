#include "CreatureTemplate.h"

CreatureTemplate::CreatureTemplate(const string& name,
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
                                   const SDL_Color&   color)
    : name(name),
      gender(gender),
      age(age),
      alignment(alignment),
      race_id(race_id),
      class_id(class_id),
      level(level),
      hp_base(hp_base),
      strength_base(strength_base),
      constitution_base(constitution_base),
      dexterity_base(dexterity_base),
      intelligence_base(intelligence_base),
      wisdom_base(wisdom_base),
      charisma_base(charisma_base),
      ac_base(ac_base),
      fortitude_base(fortitude_base),
      reflex_base(reflex_base),
      will_base(will_base),
      tile(tile),
      color(color) {
}

CreatureTemplate creature_template[kNumberOfCretureTemplates] = {
  // template 0
  CreatureTemplate("레오나르도 다 빈치", // name
                   GenderType::male, // gender
                   23, // age
                   AlignType::unaligned, //alignment
                   "인간", // race_id
                   "투사", // class_id
                   1, // level
                   80, // hp_base
                   15, 14, 16, 13, 17, 14, // STR CON DEX INT WIS CHA
                   10, 1, 1, 1, // AC FOR REF WIL
                   TileRef(TilesetType::creature, 0x00), // tile
                   color_green), // color
  // template 1
  CreatureTemplate("NPC_TYPE1", // name
                   GenderType::male, // gender
                   22, // age
                   AlignType::unaligned, //alignment
                   "인간", // race_id
                   "투사", // class_id
                   1, // level
                   40, // hp_base
                   15, 14, 16, 13, 17, 14, // STR CON DEX INT WIS CHA
                   10, 1, 1, 1, // AC FOR REF WIL
                   TileRef(TilesetType::creature, 0x01), // tile
                   color_green), // color
  // template 2
  CreatureTemplate("NPC_TYPE2", // name
                   GenderType::male, // gender
                   22, // age
                   AlignType::unaligned, //alignment
                   "인간", // race_id
                   "투사", // class_id
                   1, // level
                   40, // hp_base
                   15, 14, 16, 13, 17, 14, // STR CON DEX INT WIS CHA
                   10, 1, 1, 1, // AC FOR REF WIL
                   TileRef(TilesetType::creature, 0x02), // tile
                   color_green), // color
};
