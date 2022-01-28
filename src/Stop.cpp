//
// Created by zemar on 27/01/2022.
//

#include "../headers/Stop.h"

void Stop::setID(const int &id) {
    this->id = id;
}
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
int Stop::getID() const { return id;}
std::string Stop::getCode() const { return code; }
std::string Stop::getName() const { return name; }
std::string Stop::getZone() const { return zone; }
double Stop::getLatitude() const { return latitude; }
double Stop::getLongitude() const { return longitude; }

Stop::Stop(const std::string &code, const std::string &name, const std::string &zone, double latitude, double longitude)
        : id(id), code(code), name(name), zone(zone), latitude(latitude), longitude(longitude) {

}