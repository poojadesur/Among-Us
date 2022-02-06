#include "main.h"
#include "cell.h"
#include "maze.h"
#include "graph.h"
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>


Maze::Maze(int width, int height, color_t color) {
  this->width = width;
  this->height = height;
  this->color = color;
  createCells();
  current = &cells[0];
  current->walls[3] = false;
}

void Maze::createCells() {
  for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {
      cells.push_back(Cell(row, column));
    }
  }
}

void Maze::generateMaze() {
  while (true) {
    current->setVisited(true);
    Cell *next = findNextCell();

    if (next != NULL) {
      next->setVisited(true);
      backtrace.push(current);
      current->removeWalls(*next);
      current = next;
    } 
    else if (backtrace.size() > 0) {
      current = backtrace.top();
      backtrace.pop();
    }
    else if (backtrace.size() == 0) {
      break;
    }

  }

  render();

  // mapping to graph
  map_mazeTograph();

}

// create adjacency list
void Maze::map_mazeTograph()
{
  // calling constructor class
  graph = new Graph((int)cells.size());

  // std::cout << "calculating by adding edges adjacency list" << std::endl;

  for (int i = 0;i<(int)cells.size();i++) 
  {
    // std::cout << "calc cell " << i << std::endl;

    Cell *cell = &cells[i];

    int currentRow = cell->getRow();
    int currentColumn = cell->getColumn();

    int currentCellIdx = calculateIndex(currentRow, currentColumn);
    // std::cout << "cell index " << currentCellIdx << std::endl;


    std::vector< pair<int,int> > availableNeighbors = findAllNeighbors(&cells[i]);
    
    // directions - TOP = 1, BOTTOM = -1 , RIGHT = -2, LEFT = 2

    for(int j=0;j<4;j++)
    {
      if(j == 0){
        if(availableNeighbors[j].first != -1 && availableNeighbors[j].second != -1)
        {
          graph->addEdge(currentCellIdx,availableNeighbors[j].first,1);
        }
      }
      if(j == 1){

        if(availableNeighbors[j].first != -1 && availableNeighbors[j].second != -1)
        {
          graph->addEdge(currentCellIdx,availableNeighbors[j].first,-2);
        }
        
      }
      if(j == 2)
      {
        if(availableNeighbors[j].first != -1 && availableNeighbors[j].second != -1)
        {
          graph->addEdge(currentCellIdx,availableNeighbors[j].first,-1);
        }
      }
      if(j == 3)
      {
        if(availableNeighbors[j].first != -1 && availableNeighbors[j].second != -1)
        {
          graph->addEdge(currentCellIdx,availableNeighbors[j].first,2);
        }
      }
    }
  }

  // std::cout << "adjacency list" << std::endl;

  // for(int i=0;i<graph->V;i++)
  // {
  //   std::cout << "cell num " << i << std::endl;
    
  //   for(int j=0;j<(int)graph->adj[i].size();j++)
  //   {
  //     std::cout << "to cell " << graph->adj[i][j].first << " direction: " << graph->adj[i][j].second << std::endl;
  //   }

  //   std::cout << std::endl;
  // }

}

void Maze::render() {

    std::vector <float> vertex_buffer_data_vector;
    enum direction { TOP, RIGHT, BOTTOM, LEFT };

    for (int i = 0;i<(int)cells.size();i++) 
    {
        Cell c = cells[i];

        // std::cout << std::endl; 
        // std::cout << std::endl; 
        // // std::cout << "Cell " << i << std::endl;
        // for(int j=0;j<4;j++)
        //     std::cout << c.walls[j] << " ";
        // std::cout << std::endl;

        float x;
        float y;
        float z;

        // std::cout << "TOP " << std::endl; 

        if ( c.walls[TOP] == true )
        {
            // top point of top wall
            // y= float(c.getRow() / height);
            // x= c.getColumn() / width;
            y= c.getRow() + 1;
            x= c.getColumn();
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);

            // std::cout << x << " " << y << " " << z << std::endl; 

            // bottom point of top wall
            // y= c.getRow() / height;
            // x= c.getColumn() + 1 / width;
            y= c.getRow() + 1;
            x= c.getColumn() + 1;
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);
            // std::cout << x << " " << y << " " << z << std::endl; 

        }

        // std::cout << "RIGHT " << std::endl; 
        
        if ( c.walls[RIGHT] == true )
        {
            // top point of right wall
            // y= c.getRow() / height;
            // x= c.getColumn() + 1 / width;
            y= c.getRow();
            x= c.getColumn() + 1;
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);

            // std::cout << x << " " << y << " " << z << std::endl; 


            // bottom point of right wall
            // y= c.getRow() + 1 / height;
            // x= c.getColumn() + 1 / width;
            y= c.getRow() + 1;
            x= c.getColumn() + 1;
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);

            // std::cout << x << " " << y << " " << z << std::endl; 

        }

        // std::cout << "BOTTOM " << std::endl; 

        
        if ( c.walls[BOTTOM] == true )
        {
            // top point of bottom wall
            // y= c.getRow() + 1 / height;
            // x= c.getColumn() / width;
            y= c.getRow();
            x= c.getColumn();
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);

            // std::cout << x << " " << y << " " << z << std::endl; 


            // bottom point of bottom wall
            // y= c.getRow() + 1 / height;
            // x= c.getColumn() + 1 / width;
            y= c.getRow();
            x= c.getColumn() + 1;
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);

            // std::cout << x << " " << y << " " << z << std::endl; 

        }

        // std::cout << "LEFT " << std::endl; 

        if ( c.walls[LEFT] == true )
        {
            // top point of left wall
            // y= c.getRow() / height;
            // x = c.getColumn() / width;
            y= c.getRow();
            x = c.getColumn();
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);

            // std::cout << x << " " << y << " " << z << std::endl; 


            // bottom point of left wall
            // y= c.getRow() + 1 / height;
            // x = c.getColumn() / width;
            y= c.getRow() + 1;
            x = c.getColumn();
            z = 0;
            vertex_buffer_data_vector.push_back(x);
            vertex_buffer_data_vector.push_back(y);
            vertex_buffer_data_vector.push_back(z);

            // std::cout << x << " " << y << " " << z << std::endl; 

        }
        
    }
    
    int num_vertices = vertex_buffer_data_vector.size();

    // static const creates issue here????? static const GLfloat vertex_buffer_data - og
    float vertex_buffer_data[num_vertices];
    std::copy(vertex_buffer_data_vector.begin(), vertex_buffer_data_vector.end(), vertex_buffer_data);
    this->object = create3DObject(GL_LINES, num_vertices, vertex_buffer_data, this->color, GL_FILL);
}

// randomly picks possible neighbor
Cell *Maze::findNextCell() {
  std::vector<Cell *> availableNeighbors = getAvailableNeighbors();
  if (availableNeighbors.size() > 0) {
    int selected = rand() % availableNeighbors.size();
    // std::cout << "neighbour number picked: " << selected << std::endl;
    return availableNeighbors.at(selected);
  }

  // hits a deadend
  return NULL;
}

std::vector< pair<int,int> > Maze::findAllNeighbors(Cell *cell) {
    

  std::vector< pair<int,int> > neighbors;

  int currentRow = cell->getRow();
  int currentColumn = cell->getColumn();

  int currentCellIdx = calculateIndex(currentRow, currentColumn);

  // std::cout << "neighbours of cell " << currentCellIdx << std::endl;

//   std::cout << "neighbours: " << std::endl;

  // TOP RIGHT BOTTOM LEFT
  int neighborIndexes[4] = {
      calculateIndex(currentRow + 1, currentColumn),
      calculateIndex(currentRow, currentColumn + 1),
      calculateIndex(currentRow - 1, currentColumn),
      calculateIndex(currentRow, currentColumn - 1),
  };

  // for (int i : neighborIndexes) {
  //   if (i != -1 && cells[i].walls[neighborIndexes[i]]) {
  //     neighbors.push_back(&cells[i]);
  //   //   std::cout << i << " ";
  //   }
  // }


  for (int i=0;i<4;i++) {
    if (neighborIndexes[i] != -1 && !cells[currentCellIdx].walls[i]){
      neighbors.push_back(make_pair(neighborIndexes[i],i));
      // std::cout << "neighbour " << neighborIndexes[i] << "direction " << i << std::endl;

    }
    else
    {
      neighbors.push_back(make_pair(neighborIndexes[i],-1));
      // std::cout << "neighbour " << neighborIndexes[i] << "direction " << -1 << std::endl;
    }

  }

  // std::cout << std::endl;

  return neighbors;
}

std::vector<Cell *> Maze::getAvailableNeighbors() {

  std::vector<Cell *> neighbors;

  int currentRow = current->getRow();
  int currentColumn = current->getColumn();
  
//   std::cout << "neighbours: " << std::endl;

  int neighborIndexes[4] = {
      calculateIndex(currentRow - 1, currentColumn),
      calculateIndex(currentRow, currentColumn + 1),
      calculateIndex(currentRow + 1, currentColumn),
      calculateIndex(currentRow, currentColumn - 1),
  };

  for (int i : neighborIndexes) {
    if (i != -1 && !cells[i].isVisited()) {
      neighbors.push_back(&cells[i]);
    //   std::cout << i << " ";
    }
  }

//   std::cout << std::endl;

  return neighbors;
}

int Maze::calculateIndex(int row, int column) {
  if (row < 0 || column < 0 || column > width - 1 || row > height - 1)
    return -1;
  else
    return column + row * width;
}




void Maze::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    // glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}