#include "graph.h"

Graph::Graph() {
    numVertices = 0;
    adjLists = nullptr;
    visited = nullptr;
}

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices] {};
    visited = new bool[vertices] {};
}

void Graph::addEdge(int src, int dest) {
    adjLists[src].push_front(dest);
}
bool Graph::DFS(int startVertex, int board_size, FIELD_TYPE check_for, int to_ignore) {
    if (to_ignore != -1) {
        if (startVertex == to_ignore)
            return false;
        visited[to_ignore] = true;
    }

    std::queue<int> queue;
    queue.push(startVertex);



    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();

        if (!visited[currentVertex]) {
//            cout << currentVertex << " ";
            if (check_for == FIELD_TYPE::RED) {
                if (currentVertex % board_size == board_size - 1)
                    return true;
            }
            else if (check_for == FIELD_TYPE::BLUE) {
                if (currentVertex / board_size == board_size - 1)
                    return true;
            }

            visited[currentVertex] = true;
        }

        for (int adjacent : adjLists[currentVertex]) {
            if (!visited[adjacent]) {
                queue.push(adjacent);
            }
        }
    }

//    cout << endl;

    return false;
}

Graph::~Graph() {
    delete[] adjLists;
    delete[] visited;
}

void Graph::printEdges() {
    for (int i = 0; i < numVertices; i++) {
        if (adjLists[i].empty())
            continue;
        cout << i << ": ";
        for (int v: adjLists[i])
            cout << v << " ";
        cout << endl;
    }
}

