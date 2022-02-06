#include "cell.h"
#include <stdlib.h>
#include <iostream>

Cell::Cell(int row, int column) {
  this->row = row;
  this->column = column;
  visited = false;
  setWalls();
}

void Cell::setWalls() {
  for (int i = 0; i < 4; i++) walls[i] = true;
}

void Cell::setVisited(bool b) { visited = b; }
bool Cell::isVisited() { return visited; }

int Cell::getRow() { return row; }
int Cell::getColumn() { return column; }

void Cell::removeWalls(Cell &next) {
  int x = next.column - column;
  int y = next.row - row;

  if (x == 1) {
    walls[RIGHT] = false;
    next.walls[LEFT] = false;
  } 
  else if (x == -1) {
    walls[LEFT] = false;
    next.walls[RIGHT] = false;
  } 
  else if (y == 1) {
    walls[TOP] = false;
    next.walls[BOTTOM] = false;
  } 
  else if (y == -1) {
    walls[BOTTOM] = false;
    next.walls[TOP] = false;
  }
}

