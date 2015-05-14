#include "CreatureVector.h"

CreatureVector::CreatureVector()
    : count_(0) {
}

CreatureVector::~CreatureVector() {
  Clear();
}

Creature& CreatureVector::operator[](const int& id) {
  return *crets_[id];
}

void CreatureVector::Clear() {
  for (auto it = crets_.begin(); it != crets_.end(); ++it)
      delete *it;
  crets_.clear();
  count_ = 0;
}
void CreatureVector::CreateCreature(LocalPlace& place, const Coord& pos, const int& template_id) {
  crets_.push_back(new Creature(place, *this, count_, pos, template_id));
  place.SetCreatureId(pos, count_);
  count_++;
}
const int& CreatureVector::GetCount() const {
  return count_;
}
