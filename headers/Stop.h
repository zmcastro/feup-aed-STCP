//
// Created by zemar on 27/01/2022.
//

#ifndef AEDPROJ2_STOP_H
#define AEDPROJ2_STOP_H


#include <string>

class Stop {
public:
    Stop(const std::string &code, const std::string &name, const std::string &zone, double latitude, double longitude);

private:
    std::string code, name, zone;
    double latitude, longitude;
    int id;

public:
    void setID(const int &id);
    void setCode(const std::string &code);
    void setName(const std::string &name);
    void setZone(const std::string &zone);
    void setLatitude(const double &latitude);
    void setLongitude(const double &longitude);
    void setCoordinates(const double &longitude, const double &latitude);

    int getID() const;
    std::string getCode() const;
    std::string getName() const;
    std::string getZone() const;
    double getLatitude() const;
    double getLongitude() const;

    bool operator==(const Stop& s) {
        return this->code == s.code;
    }
};


#endif //AEDPROJ2_STOP_H
