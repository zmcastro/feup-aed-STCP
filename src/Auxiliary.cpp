//
// Created by zemar on 28/01/2022.
//

#include <cmath>

#include "../headers/Auxiliary.h"

double haversine(double lat1, double lon1, double lat2, double lon2)
{
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void cleanScreen() {
    std::cout << std::string(10, '\n');
}

bool inpCheck(int& x) {
    int n;
    if (std::cin >> n && std::cin.peek() == '\n') {
        x = n;
        std::cin.ignore(10000, '\n');
        return true;
    }

    else if (std::cin.fail() && std::cin.eof()){
        exit(0);
    }
    else {
        std::cin.ignore(10000, '\n');
        std::cin.clear();
        return false;
    }
}

