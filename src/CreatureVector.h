#ifndef CREATUREVECTOR_H
#define CREATUREVECTOR_H

#include "types.h"
#include <vector>
#include "Creature.h"

using namespace std;

class CreatureVector {
protected:
  vector<Creature*> crets_;
  int count_;

public:
  CreatureVector();
  ~CreatureVector();

private:
  // 복사 금지
  CreatureVector& operator=(const CreatureVector& r_right_object);
  CreatureVector(const CreatureVector& r_source_object);

public:
  // 연산자
  Creature& operator[](const int& id);

public:
  // 메쏘드
  void CreateCreature(LocalPlace& place, const Coord& pos, const int& template_id);
  void Clear();
  const int& GetCount() const;
};

#endif // CREATUREVECTOR_H
