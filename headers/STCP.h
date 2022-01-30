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

    std::unordered_map<std::string, int> stopMap;
    std::unordered_map<std::string, int> stopLineMap;
    std::vector<Line> lines;

public:
    /**
     * Constructor of the STCP class - reads the stops and the lines and organizes them
     */
    STCP();
    void addStop(const Stop &stop);
    /**
     * Shows the path between 2 stops
     * @param stops List of stops (1st one is the departure stop and the last one is the final stop)
     */
    void showPath(const std::list<Stop> &stops);

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
    /**
     * Shows the stops near a certain place that can be either given by coordinates or a stop code
     * @param result The stops near a given place
     */
    static void showStopsNear(std::vector<Stop> result);
    /**
     * Text based interface where the client will give a stop and a distance in order to receive the stops near that stop
     */
    void nearMeByStopHandler();
    /**
     * Text based interface where the client will give coordinates and a distance in order to receive the stops near that place
     */
    void nearMeByCoorHandler();
};

#endif //AEDPROJ2_STCP_H
