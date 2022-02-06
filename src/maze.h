#include <stack>
#include <vector>
#include "main.h"
#include "cell.h"
#include "graph.h"

#ifndef MAZE_H
#define MAZE_H

class Maze {
 private:

  // cells

  std::stack<Cell *> backtrace;
  Cell *current;

  void createCells();
  std::vector<Cell *> getAvailableNeighbors();
  Cell *findNextCell();

  std::vector <pair<int,int>> findAllNeighbors(Cell *cell);

  // void map_graph();
 
  void render();

  VAO *object;


 public:

  Maze() {}
  int width;
  int height;
  color_t color;
  std::vector<Cell> cells;
  Maze(int width, int height, color_t color);
  int calculateIndex(int i, int j);
  void generateMaze();
  void draw(glm::mat4 VP);

  // maze maps to graph
  Graph *graph;
  void map_mazeTograph();

};

#endif