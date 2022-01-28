//
// Created by zemar on 28/01/2022.
//

#include "../headers/PathMap.h"

Graph PathMap::makeGraph(int src) {
    for(int i = 0; i < stops.size(); i++)
    {

    }
}

int PathMap::getStopIndex(const std::string &code) {
    for (int i = 0; i < stops.size(); i++) {
        if (stops[i].getCode() == code)
            return i;
    }
    return -1;
}

Stop PathMap::findStop(const int &idx) {
    return stops.at(idx);
}


