//
// Created by zemar on 29/01/2022.
//

#ifndef AEDPROJ2_AUXILIARY_H
#define AEDPROJ2_AUXILIARY_H

#include <iostream>
#include <iomanip>
#include <string>
/**
 * Returns the distance in km of 2 places given the coordinates of those 2 places
 * @param lat1 Latitude of the 1st place
 * @param lon1 Longitude of the 1st place
 * @param lat2 Latitude of the 2nd place
 * @param lon2 Longitude of the 2nd place
 * @return
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

/**
 * Returns True if parameter x is of type int and isolated (only integers allowed, no chars p.e.)
 * @param x input to be checked
 */
bool inpCheck(int &x);

/** Simple function to clear screen, outputs 10 new lines
 */
void cleanScreen();


#endif //AEDPROJ2_AUXILIARY_H
