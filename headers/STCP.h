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
    /**
     * Constructor of the STCP class - reads the stops and the lines and organizes them
     */
    STCP();

    void addStop(const Stop &stop);

    void testOutput();
    /**
     * Text based interface of the program to help the client finding what they are looking for
     */
    void mainInterface();
    /**
     * Text based interface of the program to help the client find stops near them
     */
     void stopsNearInterface();
    /**
     * Text based interface to help the client find the best trip according to their preferences
     */
    void bestTripInterface();

    static void showStopsNear(std::vector<Stop> result);

    void nearMeByStop();

    void nearMeByCoor();
};

#endif //AEDPROJ2_STCP_H
