#include<bits/stdc++.h>
#include "graph.h"
#include <stdlib.h>
#include <iostream>

using namespace std;
  
// Allocates memory for adjacency list
Graph::Graph(int num_vertices)
{
    this->V = num_vertices;
    adj = new vector < pair<int,int> > [V];
    // vector < vector <pair<int,int>> > adjlist = new vector < vector <pair<int,int>> > adjlist;
}
  
void Graph::addEdge(int u, int v,int direction)
{
    // TOP = 1, BOTTOM = -1 , RIGHT = -2, LEFT = 2
    adj[u].push_back(make_pair(v,direction));
    // adj[v].push_back(make_pair(u,-direction));
}

int Graph::bfs(int u,int dest)
{
    std::queue<pair<int,int>> q;

    vector<bool> v;
    for(int i=0;i<V;i++) v.push_back(false);

    q.push(make_pair(u,0));
    
    v[u] = true;
    
    // in order to return direction of first child from source that gives sp
    int num_loop = 0;
  
    while (!q.empty()) {
        
        int f = q.front().first;
        int dir = q.front().second;
        q.pop();

        // for(int i=0;i<V;i++)
        // {
        //     cout << i << " : " << v[i] << endl;
        // }

        // v[f] = true;

        // cout << f << " " << endl;

        // cout << "children: " << endl;

        for (int i=0;i<(int)adj[f].size();i++) {
            
            int child = adj[f][i].first;

            // cout << child << " ";

            if (!v[child]) {
                
                // assign children direction of first child 
                if(num_loop == 0){
                    dir = adj[f][i].second;
                }

                q.push(make_pair(child,dir));
                v[child] = true;

                // cout << "child being pushed in queue: " << child << " " << endl;

                // crewmate position
                if( child == dest )
                {
                    // cout << "found crewmate " << endl;
                    // cout << " dir returned " << dir << endl;
                    return dir; 
                }
            }
        }

        // cout << endl;

        num_loop += 1;
    }

    // no path - EDGE CASE
    return 0;
}

int Graph::shortestPath(int source,int dest)
{
    bool foundCrewmate = 0;
    
    // crewmate and imposter are in same cell - could lead to some bugs
    if(source == dest)
    { 
        cout << "i hit you haha" << endl;
        return 5;
    }

    // std::cout << "source and dest " << source << " " << dest << std::endl;

    int direction = bfs(source,dest);

    return direction;
}
