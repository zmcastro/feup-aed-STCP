//
// Created by zemar on 27/01/2022.
//

#include "../headers/Stop.h"

Stop::Stop(const std::string &code, const std::string &name, const std::string &zone, const double &latitude, const double &longitude) : code(code), zone(zone), name(name), latitude(latitude), longitude(longitude) { }
Stop::Stop() : code(" "), name(" "), zone(""), latitude(0), longitude(0) { };

void Stop::setCode(const std::string &code) {
    this->code = code;
}
void Stop::setName(const std::string &name) {
    this->name = name;
}
void Stop::setZone(const std::string &zone) {
    this->zone = zone;
}
void Stop::setLatitude(const double &latitude) {
    this->latitude = latitude;
}
void Stop::setLongitude(const double &longitude) {
    this->longitude = longitude;
}
void Stop::setCoordinates(const double &longitude, const double &latitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

std::string Stop::getCode() const { return code; }
std::string Stop::getName() const { return name; }
std::string Stop::getZone() const { return zone; }
double Stop::getLatitude() const { return latitude; }
double Stop::getLongitude() const { return longitude; }
