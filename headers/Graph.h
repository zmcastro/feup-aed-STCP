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
    /**
     * Constructor of the Graph class
     * @param nodes The Number of nodes in the graph
     * @param dir True if the graph is directed, false otherwise
     */
    Graph(int nodes, bool dir = false);
    /**
     * Breadth first search - Sets the graph in way that the distance from the given stop and each of the others is based on the smallest number of stops between them. Time complexity: O(|V| + |E|)
     * @param index The index of the stop provided
     * @param time Day or night
     */
    void bfs(const int &index,  const bool &time);
    /**
     * Sets the graph up in way that the distance from the given stop and each of the others is based on the smallest distance between them. Time complexity: O(|E|*log(|V|))
     * @param index The index of the stop provided
     * @param time Night or day
     */
    void dijkstraByDist(const int &index, const bool &time);
    /**
    * Sets the graph up in way that the distance from the given stop and each of the others is based on the smallest number of usage of lines not equal to the desired one. Time complexity: O(|E|*log(|V|))
    * @param index The index of the stop provided
    * @param time Night or day
     * @param lineCode The string code of the desired line
    */
    void dijkstraByLine(const int &index, const bool &time, const std::string &lineCode);
    /**
     * Sets the graph up in way that the distance from the given stop and each of the others is based on the smallest number of lines used to travel between them. Time complexity: O(|E|*log(|V|))
     * @param index The index of the stop provided
     * @param time Night or day
     */
    void dijkstraByLessLines(const int &index, const bool &time);
    /**
     * Sets the graph up in way that the distance from the given stop and each of the others is based on the smallest number of zones crossed going from one to the other. Time complexity: O(|E|*log(|V|))
     * @param index The index of the stop provided
     * @param time Night or day
     */
    void dijkstraByCost(const int &index, const bool &time);
     /**
     * Add edge from source to destination with a certain weight
      * @param src The index of the stop that will receive a new connection based on a bus line
      * @param dest The index of the stop that the source stop will connect to
      * @param lineCode the string code of the line that connects the two stops
     */
     void addEdge(int src, int dest, std::string lineCode);
    /**
     * Add a stop to the graph as a node by its index
     * @param stop The stop being added
     * @param idx The index of the stop in the vector of nodes
     */
    void addNode(const Stop &stop, const int &idx);
    /**
     * Given the number of the position in the vector of Nodes (idx) return the correspondent Stop
     * @param idx
     * @return Stop with the given idx
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
     * Find the stops with a given maximum distance from a provided stop. Time complexity: O(|V|)
     * @param src The stop provided by the client
     * @param maxDist The maximum distance between the coordinates of the stop provided by the client and the other stops
     * @return All the stops that are in a distance (km) smaller or equal to the distance provided from the stop given
     */
    std::vector<Stop> findNearestStops(const int &src, const double &maxDist);
    /**
     * Find the stops with a given maximum distance from provided coordinates. Time complexity: O(|V|)
     * @param latitude The latitude provided by the client
     * @param longitude The longitude provided by the client
     * @param maxDist The maximum distance between the coordinates provided by the client and the other stops
     * @return All the stops that are in a distance (km) smaller or equal to the distance provided from the given coordinates
     */
    std::vector<Stop> findNearestStops2(const double latitude, const double longitude, const double &maxDist);
    /**
     * Find the path with the smallest number of stops from a stop to another
     * @param idx1 The index of the starting stop
     * @param idx2 The index of the ending stop
     * @param time Day or night
     * @return The path with the least number of stops between the 2 stops
     */
    std::list<Stop> bfs_path(const int &idx1, const int &idx2, const int &time);
    /**
     * Returns the distance from the source stop to another through the sum of the edges' combined weight
     * @param index The index of the final desired stop
     * @return The distance between the 2 stops (-1, if there's no path between them)
     */
    double dijkstra_distance(const int &index);
    /**
     * Finds the best path according to the client choice (smallest distance, smallest number of lines or smallest number of zones)
     * @param index1 First stop
     * @param index2 Final stop
     * @param time Night or day
     * @param dijkstraType The privileged criteria of the client to find the best trip between 2 stops
     * @return The best path according to the criteria
     */
    std::list<Stop> dijkstra_path(const int &index1, const int &index2, const int &time, const int &dijkstraType);
};


#endif //AEDPROJ2_GRAPH_H
