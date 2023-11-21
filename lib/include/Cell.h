#ifndef PREDORPREY_CELL_H
#define PREDORPREY_CELL_H
#include "Critter.h"
#include "Ant.h"
#include "Queen.h"
#include "Doodlebug.h"
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include "Coordinate.h"
using std::string, std::vector, std::unique_ptr, std::make_unique,
  std::shared_ptr, std::make_shared, std::stringstream;

enum CellType {
  HABITABLE,
  V_EDGE,
  H_EDGE,
  CORNER
};
using cell_t = CellType;

class Cell {
protected:
  coord_t pos;
  cell_t type;
  unique_ptr<Critter> occupant { nullptr };

public:
  vector<shared_ptr<Cell>> neighbors8  {};
  vector<shared_ptr<Cell>> neighbors16 {};

  Cell() = default;
  Cell(unsigned x, unsigned y, cell_t type) : pos {int(x), int(y)}, type {type} {};
  ~Cell() = default;
  Cell& operator=(const Cell&);
  unsigned takeCell(Cell& toTake);

  string toString() const;
  coord_t getPos() { return pos; }

  cell_t cellType() const { return type; }
  bool occupied()   const { return type == HABITABLE && occupant; }
  bool hasDoodle()  const { return occupied() && occupant->isDoodle(); }
  bool hasAnt()     const { return occupied() && occupant->isAnt(); }
  bool hasMating()  const { return occupied() && occupant->isMating(); }
  bool shouldDie()  const { return occupied() && occupant->shouldDie(); }
  bool canBreed()   const { return occupied() && occupant->canBreed(); }

  void spawnQueenAnt();
  void spawnMatingAnt();
  void spawnWorkerAnt();
  void spawnAnt();
  ant_t randomAntType();
  void spawnDoodle();

  unsigned tryMoveOccupant();
  unsigned tryKillOccupant();
  unsigned tryBreedOccupant();
};

#endif //PREDORPREY_CELL_H
