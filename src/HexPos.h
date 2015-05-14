#ifndef HEXPOS_H
#define HEXPOS_H

#include "libs.h"
#include "types.h"
#include "Coord.h"
#include "HexDir.h"

class HexPos : public Coord {
public:
  HexPos() : Coord() {
  }
  HexPos(const Coord& pos) : Coord(pos) {
  }
  HexPos(const int& x, const int& y) : Coord(x, y) {
  }
  virtual ~HexPos() {
  }

  inline void MoveTo(HexDir dir) {
    switch(dir) {
    case HexDir::west:
      x_--;
      break;
    case HexDir::east:
      x_++;
      break;
    case HexDir::nwest:
      x_--;
      x_+=y_%2;
      y_--;
      break;
    case HexDir::neast:
      x_+=y_%2;
      y_--;
      break;
    case HexDir::swest:
      x_--;
      x_+=y_%2;
      y_++;
      break;
    case HexDir::seast:
      x_+=y_%2;
      y_++;
      break;
    default:
      break;
    }
  }

  inline const int GetDistance(const HexPos& target_pos) const {
    int dist_x = x_ - target_pos.x_;
    int dist_y = y_ - target_pos.y_;
    if (dist_x<0) dist_x = 0 - dist_x;
    if (dist_y<0) dist_y = 0 - dist_y;
    return dist_x+dist_y;
  }
};

#endif // HEXPOS_H
