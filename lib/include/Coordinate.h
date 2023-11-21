#ifndef PREDORPREY_COORDINATE_H
#define PREDORPREY_COORDINATE_H

struct coordinate {
  int x;
  int y;
};
using coord_t = coordinate;

inline bool operator==(coordinate a, coordinate b) {
  return a.x == b.x && a.y == b.y;
}

inline coordinate operator-(coordinate a, coordinate b) {
  return {a.x - b.x, a.y - b.y};
}

inline coordinate operator+(coordinate a, coordinate b) {
  return {a.x + b.x, a.y + b.y};
}

#endif //PREDORPREY_COORDINATE_H
