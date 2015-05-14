#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

const int number_of_object_types = 3;

enum class ObjectType : int {
  none         =     -1,
  object       =      0,
  wall         =      1,
  tree         =      2,
};

#endif // OBJECTTYPE_H
