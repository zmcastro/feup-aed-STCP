//
// Created by zemar on 28/01/2022.
//

#ifndef AEDPROJ2_PATHMAP_H
#define AEDPROJ2_PATHMAP_H


#include <vector>
#include <unordered_map>
#include "Stop.h"
#include "Graph.h"

class PathMap {
private:
    std::vector<Stop> stops;
    std::vector<std::string> lines;

public:
    Graph makeGraph(int src);

    int getStopIndex(const Stop &stop);
    int getStopIndex(const std::string &code);
    Stop findStop(const int &idx);

};


#endif //AEDPROJ2_PATHMAP_H
