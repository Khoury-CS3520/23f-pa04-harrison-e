#ifndef PREDORPREY_GRID_H
#define PREDORPREY_GRID_H
#include "Cell.h"
#include <cmath>
using std::max, std::min;

class Grid {
protected:
  unsigned size {};
  vector<vector<shared_ptr<Cell>>> cells;

public:
  explicit Grid(unsigned size);
  ~Grid() = default;
  shared_ptr<Cell> at(coord_t pos);
  string print();

  unsigned moveDoodlebugs();  // return how many ants were killed by moving dbs
  unsigned breedDoodlebugs(); // return how many dbs were bred
  unsigned killDoodlebugs();  // return how many dbs were killed

  void moveAnts();
  unsigned breedAnts();       // return how many ants were bred
  unsigned killAnts();        // return how many ants were killed
};

#endif //PREDORPREY_GRID_H
