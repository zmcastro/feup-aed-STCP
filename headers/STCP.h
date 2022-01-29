//
// Created by zemar on 28/01/2022.
//

#ifndef AEDPROJ2_STCP_H
#define AEDPROJ2_STCP_H

#include <vector>
#include <unordered_map>
#include "Stop.h"
#include "Graph.h"
#include "Line.h"

class STCP {
private:
    Graph stopGraph{2487, true};

    std::vector<Stop> stops;
    std::unordered_map<std::string, int> stopMap;
    std::vector<Line> lines;

public:
    STCP();

    void addStop(const Stop &stop);

    void testOutput();
    void Interface();
    void bestTripInterface();
};

#endif //AEDPROJ2_STCP_H
