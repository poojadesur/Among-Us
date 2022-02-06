#include<bits/stdc++.h>
#include <vector>

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
    
// converting maze into an adjacency list
class Graph
{

    private:
        // visited vector
        // std::vector<bool> v;

    public:
        Graph() {}
        int V;    // No. of vertices

        Graph(int num_vertices);  // Constructor
    
        // function to add an edge to graph
        void addEdge(int u, int v, int direction);

        int bfs(int source,int dest);
    
        // returns direction imposter has to go for shortest path
        // TOP RIGHT BOTTOM LEFT
        int shortestPath(int source,int dest);

        // not initialized anywhere else - only need one instance of this class
        std::vector <pair<int,int>> *adj;

        // std::vector < vector <pair<int,int>> > adjlist;
};


#endif

  