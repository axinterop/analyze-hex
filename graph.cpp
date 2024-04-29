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
bool Graph::DFS(int v, int b_size, FIELD_TYPE check_for, int to_ignore, vector<int> *v_path) {
    if (to_ignore != -1) {
        if (v == to_ignore)
            return false;
        visited[to_ignore] = true;
    }

    std::queue<int> queue;
    queue.push(v);

    bool found_path = false;

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();

        if (!visited[currentVertex]) {
            if (v_path != nullptr)
                v_path->push_back(currentVertex);
            if (check_for == FIELD_TYPE::RED) {
                if (currentVertex % b_size == b_size - 1)
                    found_path = true;
            }
            else if (check_for == FIELD_TYPE::BLUE) {
                if (currentVertex / b_size == b_size - 1)
                    found_path = true;
            }

            visited[currentVertex] = true;
        }

        for (int adjacent : adjLists[currentVertex]) {
            if (!visited[adjacent]) {
                queue.push(adjacent);
            }
        }
    }

    return found_path;
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

void Graph::forget_visited() {
    std::fill(visited, visited + numVertices, false);
}

