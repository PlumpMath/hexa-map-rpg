#include "Creature.h"

using namespace std;
using namespace draw;
using namespace rule;

Creature::Creature(LocalPlace& place, CreatureVector& crets,
                   const int& id, const Coord& pos, const int& template_id)
    : place_(place),
      crets_(crets),
      id_(id),
      pos_(pos),
      name_(creature_template[template_id].name),
      gender_(creature_template[template_id].gender),
      age_(creature_template[template_id].age),
      alignment_(creature_template[template_id].alignment),
      race_id_(creature_template[template_id].race_id),
      class_id_(creature_template[template_id].class_id),
      level_(creature_template[template_id].level),
      exp_(0),
      hp_current_(0),
      hp_base_(creature_template[template_id].hp_base),
      hp_max_(0),
      strength_current_(0),
      strength_base_(creature_template[template_id].strength_base),
      constitution_current_(0),
      constitution_base_(creature_template[template_id].constitution_base),
      dexterity_current_(0),
      dexterity_base_(creature_template[template_id].dexterity_base),
      intelligence_current_(0),
      intelligence_base_(creature_template[template_id].intelligence_base),
      wisdom_current_(0),
      wisdom_base_(creature_template[template_id].wisdom_base),
      charisma_current_(0),
      charisma_base_(creature_template[template_id].charisma_base),
      ac_current_(0),
      ac_base_(0),
      fortitude_current_(0),
      fortitude_base_(0),
      reflex_current_(0),
      reflex_base_(0),
      will_current_(0),
      will_base_(0),
      tile_(creature_template[template_id].tile),
      color_(creature_template[template_id].color),
      sight_range_(12),
      tick_(10),
      is_removed_(false) {
  hp_max_               = hp_base_;
  hp_current_           = hp_max_;
  strength_current_     = strength_base_;
  constitution_current_ = constitution_base_;
  dexterity_current_    = dexterity_base_;
  intelligence_current_ = intelligence_base_;
  wisdom_current_       = wisdom_base_;
  charisma_current_     = charisma_base_;
  ac_current_           = ac_base_;
  fortitude_current_    = fortitude_base_;
  reflex_current_       = reflex_base_;
  will_current_         = will_base_;
}

Creature::~Creature() {
}

const int& Creature::id() const {
  return id_;
}
const Coord& Creature::pos() const {
  return pos_;
}
const string& Creature::name() const {
  return name_;
}
const TileRef& Creature::tile() const {
  return tile_;
}
const SDL_Color& Creature::color() const {
  return color_;
}
void Creature::set_tile(const TileRef& tile) {
  this->tile_ = tile;
}
void Creature::set_name(const string& name) {
  this->name_ = name;
}

const int& Creature::hp_current() const {
  return hp_current_;
}
void Creature::set_hp_current(const int& hp) {
  this->hp_current_ = hp;
}
void Creature::GetHealed(const int& mod) {
  hp_current_ += mod;
  if(hp_current_ > hp_max_)
    hp_current_ = hp_max_;
}
void Creature::GetDamaged(const int& mod) {
  hp_current_ -= mod;
}
const int& Creature::hp_max() const {
  return hp_max_;
}

const bool Creature::MoveTo(const HexDir& dir) {
  HexPos try_pos(pos_);
  try_pos.MoveTo(dir);
  if (place_.IsPassable(pos_, try_pos, MoveType::walk)) {
    place_.SetCreatureId(pos_, -1);
    pos_ = try_pos;
    place_.SetCreatureId(pos_, id_);
    return true;
  } else {
    return false;
  }
}

const int& Creature::sight_range() const {
  return sight_range_;
}
void Creature::set_sight_range(const int& sight_range) {
  sight_range_ = sight_range;
}
const bool Creature::IncSightRange() {
  if (!(sight_range_ >= max_sight_range)) {
    sight_range_++;
    return true;
  } else {
    return false;
  }
}
const bool Creature::DecSightRange() {
  if (!(sight_range_ <= 0)) {
    sight_range_--;
    return true;
  } else {
    return false;
  }
}
SightTable& Creature::sight_table() {
  return sight_table_;
}
void Creature::UpdateSightTable() {
  ApplySightMask(sight_table_, pos_, sight_range_, place_);
}
const bool Creature::SightAt(const Coord& loc) const {
  return !(sight_table_[loc.y()][loc.x()]);
}

void Creature::set_tick(const int& tick) {
  tick_ = tick;
}
void Creature::FlowTick() {
  tick_--;
}
void Creature::IncTick(const int& inc) {
  tick_ += inc;
}
void Creature::DecTick(const int& dec) {
  tick_ -= dec;
}
const int& Creature::tick() const {
  return tick_;
}
const bool Creature::IsActiveTurn() const {
  return tick_ <= 0;
}
const bool Creature::is_removed() const {
  return is_removed_;
}
void Creature::Remove() {
  place_.SetCreatureId(pos(), -1);
  is_removed_ = true;
}

const int Creature::GetDistanceFrom(const HexPos& target_pos) const {
  return pos_.GetDistance(target_pos);
}

const int Creature::GetDistanceWith(const int& creature_id) const {
  return pos_.GetDistance(crets_[creature_id].pos());
}

const bool Creature::CheckDie() {
  if (hp_current_ <= 0) {
    message << name() << "{은} 죽는다.\n";
    Remove();
    return true;
  } else {
    return false;
  }
}

void Creature::ActBaseAttack(const HexPos& target_pos) {
  if (place_.HasCreature(target_pos)) {
    int target_id = place_.GetCreatureId(target_pos);
    int damage = Random()%30;
    int damage_self = Random()%3;
    crets_[target_id].GetDamaged(damage);
    message << name() << "{은} "
            << crets_[target_id].name() << "{을} 공격해 <red>" << damage << "<black>의 피해를 입힌다. ";
    if (!crets_[target_id].CheckDie()) {
      GetDamaged(damage_self);
      message << crets_[target_id].name() << "{은} 반격해 "
            << name() << "에게 <red>" << damage_self << "<black>의 피해를 입힌다.\n";
    }
  } else {
    message << crets_[id_].name() << "{은} 허공을 공격한다.\n";
  }
  crets_[id_].IncTick(tick_standard_act);
}

void Creature::ActWalkTo(const HexDir& dir) {
  crets_[id_].MoveTo(dir);
  crets_[id_].IncTick(tick_move_act);
}

void Creature::ActWait() {
  crets_[id_].IncTick(tick_wait_act);
}

