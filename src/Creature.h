#ifndef CREATURE_H
#define CREATURE_H

#include "libs.h"
#include "types.h"
#include "Random.h"
#include "Sight.h"
#include "CreatureTemplate.h"
#include "CreatureVector.h"
#include "Draw.h"
#include "Time.h"

using namespace std;

class Creature {
  friend class CreatureVector;
public:
  explicit Creature(LocalPlace& place, CreatureVector& crets,
                    const int& id, const Coord& pos, const int& template_id);
  ~Creature();

  const int& id() const;
  const Coord& pos() const;
  const string& name() const;
  const TileRef& tile() const;
  const SDL_Color& color() const;
  void set_name(const string& name);
  void set_tile(const TileRef& tile);

  const int& hp_current() const;
  void set_hp_current(const int& hp);
  void GetHealed(const int& mod);
  void GetDamaged(const int& mod);
  const int& hp_max() const;

  const bool MoveTo(const HexDir& dir);

  const bool IncSightRange();
  const bool DecSightRange();
  const int& sight_range() const;
  void set_sight_range(const int& sight_range);
  SightTable& sight_table();
  const bool SightAt(const Coord& loc) const;
  void UpdateSightTable();

  void set_tick(const int& tick);
  void FlowTick();
  void IncTick(const int& inc);
  void DecTick(const int& dec);
  const int& tick() const;
  const bool IsActiveTurn() const;

  const bool is_removed() const;
  void Remove();

  const int GetDistanceFrom(const HexPos& target_pos) const;
  const int GetDistanceWith(const int& creature_id) const;
  const bool CheckDie();
  void ActBaseAttack(const HexPos& target_pos);
  void ActWalkTo(const HexDir& dir);
  void ActWait();


protected:
  LocalPlace&     place_;
  CreatureVector& crets_;

  int         id_;
  HexPos      pos_;

  string      name_;
  GenderType  gender_;
  int         age_;
  AlignType   alignment_;

  string      race_id_;
  string      class_id_;
  int         level_;
  int         exp_;
  int         hp_current_;
  int         hp_base_;
  int         hp_max_;

  int         strength_current_;
  int         strength_base_;
  int         constitution_current_;
  int         constitution_base_;
  int         dexterity_current_;
  int         dexterity_base_;
  int         intelligence_current_;
  int         intelligence_base_;
  int         wisdom_current_;
  int         wisdom_base_;
  int         charisma_current_;
  int         charisma_base_;

  int         ac_current_;
  int         ac_base_;
  int         fortitude_current_;
  int         fortitude_base_;
  int         reflex_current_;
  int         reflex_base_;
  int         will_current_;
  int         will_base_;

  TileRef     tile_;
  SDL_Color   color_;

  int         sight_range_;
  SightTable  sight_table_;

  int         tick_;
  bool        is_removed_;

//  int         height;
//  int         weight;
//  string deity;
//  string affiliation;
//
//  deities
//  abilities
//  skills
//  feats
//  powers
//  calcs
//  equipments
//  items
//  effects
};

#endif // CREATURE_H

