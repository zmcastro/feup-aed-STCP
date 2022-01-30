//
// Created by zemar on 27/01/2022.
//

#ifndef AEDPROJ2_GRAPH_H
#define AEDPROJ2_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <set>
#include <unordered_map>
#include<algorithm>
#include "Stop.h"
#include "Auxiliary.h"

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
        std::string line; //linecode
    };

    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;
        int pred;
        double dist;

        Stop stop;

        Node() { };
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    void bfs(const int &index,  const bool &time);
    void dijkstraByDist(const int &index, const bool &time);
    void dijkstraByCost(const int &index, const bool &time);

     /**
     * Add edge from source to destination with a certain weight
     */
     void addEdge(int src, int dest, std::string lineCode);

    /**
     * Add node from
     * @param stop
     */
    void addNode(const Stop &stop, const int &idx);

    Stop getStop(const int &idx);

    int findNearest(const int &src);
    int findNearest(const int &src, const std::string &line);
    std::vector<Stop> findNearestStops(const int &src, const double &maxDist);
    std::vector<Stop> findNearestLineStops(const int &src, const double &maxDist);

    std::list<Stop> bfs_path(const int &idx1, const int &idx2, const int &time);
    double dijkstra_distance(const int &index1, const int &index2, const int &dijkstraType);
    std::list<Stop> dijkstra_path(const int &index1, const int &index2, const int &time, const int &dijkstraType);

    std::vector<Stop> findNearestStops2(const double latitude, const double longitude, const double &maxDist);

    void showPath(const std::list<Stop> &stops);
};


#endif //AEDPROJ2_GRAPH_H
