#include "graph.h"

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices];
    visited = new bool[vertices];
}

void Graph::addEdge(int src, int dest) {
    adjLists[src].push_front(dest);
}

void Graph::DFS(int vertex) {
    visited[vertex] = true;
    list<int> adjList = adjLists[vertex];

    cout << vertex << " ";

    list<int>::iterator i;
    for (i = adjList.begin(); i != adjList.end(); ++i)
        if (!visited[*i])
            DFS(*i);
}

Graph::~Graph() {
    delete[] adjLists;
    delete[] visited;
}

