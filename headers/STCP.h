//
// Created by zemar on 28/01/2022.
//

#ifndef AEDPROJ2_STCP_H
#define AEDPROJ2_STCP_H

class STCP {

public:
    /**
     * Constructor of the STCP class - reads the stops and the lines and organizes them
     */
    STCP();
    /**
     * Text based interface of the program to help the client finding what they are looking for
     */
    void mainInterface();
    /**
     * Text based interface to help the client find the best trip according to their preferences
     */
    void bestTripInterface();
};

#endif //AEDPROJ2_STCP_H
