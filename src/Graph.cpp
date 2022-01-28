//
// Created by zemar on 27/01/2022.
//

#define INF (std::numeric_limits<double>::max()/2)

#include "../headers/Graph.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight) {
    //wrong, check if graph already has stop;;; if (src<1 || src>n || dest<1 || dest>n) return;
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

void Graph::dijkstra(const int &index) {
    std::set<std::pair<int, int>> q;
    for (int v = 1; v <= n; v++) {
        nodes[v].pred = -1;
        nodes[v].dist = INF;
        q.insert({INF, v});
        nodes[v].visited = false;
    }

    nodes[index].dist = 0;
    q.erase({INF, index});
    q.insert({0, index});
    nodes[index].pred = index;
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

void Graph :: bfs(int v) {
// initialize all nodes as unvisited
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    std::queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        //std::cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].visited = true ;
                nodes[w].dist = nodes[u].dist + 1;
            }
        }
    }
}

std::list<int> Graph::dijkstra_path(const int &idx1, const int &idx2) {
    std::list<int> path;
    dijkstra(idx1);
    if (nodes[idx2].dist == INF) return path;
    path.push_back(idx2);
    int v = idx2;
    while (v != idx1) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

double Graph::dijkstra_distance(const int &idx1, const int &idx2) {
    dijkstra(idx1);
    if (nodes[idx2].dist == INF) return -1;
    return nodes[idx2].dist;
}

