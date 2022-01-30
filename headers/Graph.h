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
    std::vector<Node> nodes; // The vector of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);
    /**
     *
     * @param index
     * @param time
     */
    void bfs(const int &index,  const bool &time);
    /**
     * Find the path with the smallest distance possible from a stop to another
     * @param index The index of the stop provided
     * @param time Night or day
     */
    void dijkstraByDist(const int &index, const bool &time);
    /**
     * Find the path that passes throughout the smallest number of lines from a stop to another
     * @param index The index of the stop provided
     * @param time Night or day
     */
    void dijkstraByLine(const int &index, const bool &time);
    /**
     * Find the path that passes throughout the smallest number of zones from a stop to another
     * @param index The index of the stop provided
     * @param time Night or day
     */
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
    /**
     * Given the number of the position in the vector of Nodes (idx) return the correspondent Stop
     * @param idx
     * @return
     */
    Stop getStop(const int &idx);
    /**
     * Find the nearest stop to one stop provided
     * @param src The index in the vector of Nodes of the stop provided
     * @return The nearest stop to the one provided
     */
    int findNearest(const int &src);
    /**
     * Find the nearest stop to one provided that is also on the same line
     * @param src The index in the vector of Nodes of the stop provided
     * @param line Line of the stop provided
     * @return The nearest stop to the one provided
     */
    int findNearest(const int &src, const std::string &line);
    /**
     * Find the stops with a given maximum distance from a provided stop
     * @param src The stop provided by the client
     * @param maxDist The maximum distance between the coordinates of the stop provided by the client and the other stops
     * @return All the stops that are in a distance (km) smaller or equal to the distance provided from the stop given
     */
    std::vector<Stop> findNearestStops(const int &src, const double &maxDist);
    /**
     * Find the stops with a given maximum distance from provided coordinates
     * @param latitude The latitude provided by the client
     * @param longitude The longitude provided by the client
     * @param maxDist The maximum distance between the coordinates provided by the client and the other stops
     * @return All the stops that are in a distance (km) smaller or equal to the distance provided from the given coordinates
     */
    std::vector<Stop> findNearestStops2(const double latitude, const double longitude, const double &maxDist);
    /**
     * TO DO
     * @param idx1
     * @param idx2
     * @param time
     * @return
     */
    std::list<Stop> bfs_path(const int &idx1, const int &idx2, const int &time);
    double dijkstra_distance(const int &index1, const int &index2, const int &dijkstraType);
    /**
     * Finds the best path according to the client choice
     * @param index1 First stop
     * @param index2 Final stop
     * @param time Night or day
     * @param dijkstraType The privileged criteria of the client to find the best trip between 2 stops
     * @return The best path according to the criteria
     */
    std::list<Stop> dijkstra_path(const int &index1, const int &index2, const int &time, const int &dijkstraType);
    /**
     * Shows the stops that make the path from a stop to another
     * @param stops List of the stops that make the path from a stop to another (depends on the chosen criteria)
     */
    void showPath(const std::list<Stop> &stops);
};


#endif //AEDPROJ2_GRAPH_H
