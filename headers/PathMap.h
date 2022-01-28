//
// Created by zemar on 28/01/2022.
//

#ifndef AEDPROJ2_PATHMAP_H
#define AEDPROJ2_PATHMAP_H


#include <vector>
#include <unordered_map>
#include "Stop.h"

class PathMap {
private:
    std::vector<Stop> stops;
    std::vector<std::string> lines;
    std::unordered_map<Stop, int> stopIdx;

    //usar no construtor
    void mapStops() {
        for (int i = 0; i < stops.size(); i++)
        {
            stopIdx[stops.at(i)] = i;
        }
    }

public:
    int getStopIndex(const Stop &stop);
    int getStopIndex(const std::string &code);
    Stop getStop(const int &idx);


};


#endif //AEDPROJ2_PATHMAP_H
