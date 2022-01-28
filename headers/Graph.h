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
#include "Stop.h"

class Graph {
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        std::string line; //
    };

    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;
        int pred;
        double dist;
        Stop stop;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

    void dijkstra(const std::string &code);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);

    int findNode(const std::string &code);
    //Stop getNearest(const Stop &stop);

    // ----- Functions to implement in this class -----
    double dijkstra_distance(const std::string &code1, const std::string &code2);
    std::list<int> dijkstra_path(const std::string &code1, const std::string &code2);
};


#endif //AEDPROJ2_GRAPH_H
