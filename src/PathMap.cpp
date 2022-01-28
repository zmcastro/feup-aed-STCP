//
// Created by zemar on 28/01/2022.
//

#include "../headers/PathMap.h"

int PathMap::getStopIndex(const std::string &code) {
    for (int i = 0; i < stops.size(); i++) {
        if (stops[i].getCode() == code)
            return stopIdx[stops[i]];
    }
    return -1;
}
