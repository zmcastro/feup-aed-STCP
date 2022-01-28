//
// Created by zemar on 27/01/2022.
//

#ifndef AEDPROJ2_GRAPH_H
#define AEDPROJ2_GRAPH_H

#include <string>
#include <vector>
#include <list>
#include <limits>
#include <set>
#include <unordered_map>
#include "Stop.h"

class Graph {
    struct Edge {
        int dest;   // Destination node (using stop code)
        double weight; // An integer weight
        std::string line; //
    };

    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;
        int pred;
        double dist;
        Stop stop;
        int stopIdx;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    void dijkstra(const int &index);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight = 1);

    void addNode(const Stop &stop);

    int findNode(const int &index);

    //Stop getNearest(const Stop &stop);

    // ----- Functions to implement in this class -----
    double dijkstra_distance(const int &index1, const int &index2);
    std::list<int> dijkstra_path(const int &index1, const int &index2);
};


#endif //AEDPROJ2_GRAPH_H
