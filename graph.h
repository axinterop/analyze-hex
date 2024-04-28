#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <iostream>
#include <list>
using namespace std;

class Graph {
    int numVertices;
    list<int> *adjLists;
    bool *visited;
public:
    Graph(int V);
    ~Graph();
    void addEdge(int src, int dest);
    void DFS(int vertex);
};



#endif //PROJECT2_GRAPH_H
