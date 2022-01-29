//
// Created by zemar on 27/01/2022.
//

#ifndef AEDPROJ2_STOP_H
#define AEDPROJ2_STOP_H

#include <string>

class Stop {
private:
    std::string code, name, zone;
    double latitude, longitude;

public:
    /**
     * Constructor for a stop
     * @param code Code of the stop
     * @param name Name of the stop
     * @param zone Zone where the stop is located
     * @param latitude Latitude of the place where the stop is located
     * @param longitude  Longitude of the place where the stop is located
     */
    Stop(const std::string &code, const std::string &name, const std::string &zone, const double &latitude, const double &longitude);
    Stop();
    /**
     * Set the code of the stop
     * @param code Code of the stop
     */
    void setCode(const std::string &code);
    /**
     * Set the name of the stop
     * @param name Name of the stop
     */
    void setName(const std::string &name);
    /**
     * Set the zone where the stop is located
     * @param zone Zone where the stop is located
     */
    void setZone(const std::string &zone)
    /**
     * Sets the latitude of the place where the stop is located
     * @param latitude Latitude of the place where the stop is located
     */
    void setLatitude(const double &latitude);
    /**
     * Sets the longitude of the place where the stop is located
     * @param longitude Longitude of the place where the stop is located
     */
    void setLongitude(const double &longitude);
    /**
     * Sets the coordinates of the place where the stop is located
     * @param longitude Longitude of the place where the stop is located
     * @param latitude Latitude of the place where the stop is located
     */
    void setCoordinates(const double &longitude, const double &latitude);
    /**
     * Gets the code of the stop
     * @return Code of the stop
     */
    std::string getCode() const;
    /**
     * Gets the name of the stop
     * @return Name of the stop
     */
    std::string getName() const;
    /**
     * Gets the zone of the stop
     * @return Zone of the stop
     */
    std::string getZone() const;
    /**
     * Gets the latitude of the stop
     * @return Latitude of the stop
     */
    double getLatitude() const;
    /**
     * Gets the longitude of the stop
     * @return Longitude of the stop
     */
    double getLongitude() const;
    /**
     * Operator == overload so that it's possible to check if two stops are either the same or not (based on their code)
     * @param s Stop
     * @return True if the stops have the same code, false otherwise
     */
    bool operator==(const Stop& s) {
        return this->code == s.code;
    }
};


#endif //AEDPROJ2_STOP_H
