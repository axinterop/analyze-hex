#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <iostream>
#include <list>
#include <queue>

typedef enum {
    EMPTY,
    RED,
    BLUE,
} FIELD_TYPE;


using namespace std;

class Graph {
public:
    int numVertices;
    list<int> *adjLists;
    bool *visited;

    Graph();
    Graph(int V);
    ~Graph();
    void addEdge(int src, int dest);
    bool DFS(int vertex, int board_size, FIELD_TYPE check_for, int to_ignore = -1);
    void printEdges();
};



#endif //PROJECT2_GRAPH_H
