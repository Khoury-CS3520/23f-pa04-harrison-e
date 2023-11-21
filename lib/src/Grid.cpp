#include "Grid.h"
#include <iostream>

////// constructors
Grid::Grid(unsigned int size) : size {size} {
  cells = vector<vector<shared_ptr<Cell>>> (size);
  for (int y = 0; y < size; y++) {
    cells[y] = vector<shared_ptr<Cell>> (size);
    for (int x = 0; x < size; x++) {
      if (x == 0 || x == size - 1) {
        if (y == 0 || y == size - 1)
          cells[y][x] = make_shared<Cell>(x, y, CORNER);
        else
          cells[y][x] = make_shared<Cell>(x, y, V_EDGE);
      } else {
        if (y == 0 || y == size - 1)
          cells[y][x] = make_shared<Cell>(x, y, H_EDGE);
        else
          cells[y][x] = make_shared<Cell>(x, y, HABITABLE);
      }
    }
  }
  for (int c = 0; c < size * size; c++) {
    int x {c % int(size)};
    int y {c / int(size)};
    shared_ptr<Cell> cur = at({x, y});
    cur->neighbors16.reserve(16);
    cur->neighbors8.reserve(8);
    for (int i = max(0, y-2); i < min(int(size), y+2); i++) {
      for (int j = max(0, x-2); j < min(int(size), x+2); j++) {
        cur->neighbors16.push_back(at({j, i}));
        if (abs(x-j) < 2 && abs(y-i) < 2)
          cur->neighbors8.push_back(at({j, i}));
      }
    }
  }
}


////// at
shared_ptr<Cell> Grid::at(coord_t pos) {
  if (pos.x < size && pos.y < size)
    return cells[pos.y][pos.x];
  else
    return nullptr;
}


////// move critter fns
unsigned Grid::moveDoodlebugs() {
  unsigned antsKilled = 0;
  for (const auto &row : cells) {
    for (const auto &cell : row) {
      if (cell->hasDoodle())
        antsKilled += cell->tryMoveOccupant();
    }
  }
  return antsKilled;
}

void Grid::moveAnts() {
  for (const auto &row : cells) {
    for (const auto &cell : row) {
      if (cell->hasAnt())
        cell->tryMoveOccupant();
    }
  }
}


////// breed critter fns
unsigned Grid::breedDoodlebugs() {
  unsigned doodlebugsBred {};
  for (const auto &row : cells) {
    for (const auto &cell : row) {
      if (cell->hasDoodle())
        doodlebugsBred += cell->tryBreedOccupant();
    }
  }
  return doodlebugsBred;
}

unsigned Grid::breedAnts() {
  unsigned antsBred {};
  for (const auto &row : cells) {
    for (const auto &cell : row) {
      if (cell->hasAnt())
        antsBred += cell->tryBreedOccupant();
    }
  }
  return antsBred;
}


////// kill critter fns
unsigned Grid::killDoodlebugs() {
  unsigned doodlesKilled {};
  for (const auto &row : cells) {
    for (const auto &cell : row) {
      if (cell->hasDoodle())
        doodlesKilled += cell->tryKillOccupant();
    }
  }
  return doodlesKilled;
}

unsigned Grid::killAnts() {
  unsigned antsKilled {};
  for (const auto &row : cells) {
    for (const auto &cell : row) {
      if (cell->hasAnt())
        antsKilled += cell->tryKillOccupant();
    }
  }
  return antsKilled;
}


////// print
string Grid::print() {
  stringstream g;
  for (const auto &row : cells) {
    for (const auto &cell : row) {
      g << cell->toString() <<
        ((cell->cellType() == CORNER && cell->getPos().x == 0) || cell->cellType() == H_EDGE ? "──" : "  ");
    }
    g << "\n";
  }
  return g.str();
}
