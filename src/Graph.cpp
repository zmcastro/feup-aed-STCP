//
// Created by zemar on 27/01/2022.
//

#define INF (std::numeric_limits<double>::max()/2)

#include "../headers/Graph.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

int Graph::findNode(const std::string &code) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].stop.getCode() == code)
            return i;
    }
    return -1;
}

void Graph::dijkstra(const std::string &code) {
    int s = findNode(code);
    if (s == -1)
        return;

    std::set<std::pair<int, int>> q;
    for (int v = 1; v <= n; v++) {
        nodes[v].pred = -1;
        nodes[v].dist = INF;
        q.insert({INF, v});
        nodes[v].visited = false;
    }

    nodes[s].dist = 0;
    q.erase({INF, s});
    q.insert({0, s});
    nodes[s].pred = s;
    while (q.size() > 0) {
        int u = q.begin()->second;
        q.erase(q.begin());
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e: nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                q.erase({nodes[v].dist, v});
                nodes[v].dist = nodes[u].dist + w;
                nodes[v].pred = u;
                q.insert({nodes[v].dist, v});
            }
        }
    }
}


std::list<int> Graph::dijkstra_path(const std::string &code1, const std::string &code2) {
    std::list<int> path;

    int idx1 = findNode(code1);
    int idx2 = findNode(code2);
    if (idx1 == -1 || idx2 == -1)
        return path;

    dijkstra(code1);
    if (nodes[idx2].dist == INF) return path;
    path.push_back(idx2);
    int v = idx2;
    while (v != idx1) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

double Graph::dijkstra_distance(const std::string &code1, const std::string &code2) {
    int idx1 = findNode(code1);
    int idx2 = findNode(code2);
    if (idx1 == -1 || idx2 == -1)
        return -1;

    dijkstra(code1);
    if (nodes[idx2].dist == INF) return -1;
    return nodes[idx2].dist;
}
