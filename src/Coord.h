#ifndef COORD_H
#define COORD_H

#include "types.h"

class Coord {
 public:
  const int& x() const {
    return x_;
  }
  const int& y() const {
    return y_;
  }
  void set_x(const int& value) {
    x_ = value;
  }
  void set_y(const int& value) {
    y_ = value;
  }

  Coord() : x_(0), y_(0) {}
  Coord(const int& x, const int& y) : x_(x), y_(y) {}
  virtual ~Coord() {}
  const bool operator==(const Coord& r_obj) const {
    if ((x_ == r_obj.x_) && (y_ == r_obj.y_)) {
      return true;
    } else {
      return false;
    }
  }
  const bool operator<(const Coord& r_obj) const {
    if (x_ < r_obj.x_) {
      return true;
    } else if (x_ == r_obj.x_) {
      return (y_ < r_obj.y_);
    } else {
      return false;
    }
  }

 protected:
  int x_;
  int y_;
};

#endif // COORI_H
