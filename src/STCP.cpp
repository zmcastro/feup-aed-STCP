//
// Created by mroch on 27/01/2022.
//
#include <map>
#include <vector>
STCP::STCP() {

    std::map<int, std::string, std::string> idStopZone;
    std::map<int, double, double> idCoor;
    std::map<std::string, int> codeID;
    std::map<std::string, std::string> codeName;
    std::vector<std::string>paths;

    std::ifstream infileStops;
    infileStops.open("../files/dataset/stops.csv");
    if (infileStops.is_open()) {
        std::string line;
        int id = 1;

        std::getline(header); //skip 1st line
        while (std::getline(infileStops, line)) {

            std::stringstream ls(line);
            std::string code, name, zone, strLat, strLong;
            double latitude, longitude;

            std::getline(ls, code, ',');
            std::getline(ls, name, ',');
            std::getline(ls, zone, ',');
            std::getline(ls, strLat, ',');
            std::getline(ls, strLong);

            latitude = std::stod(strLat);
            longitude = std::stod(strLong);

            idStopZone.insert(id, name, zone);
            idCoor(id, latitude, longitude);
            codeID(id, code);

            id++;
        }
    } else {
        throw "NoStopsFound!";
    }
    infileStops.close();


    std::ifstream infileLines;
    infileLines.open("../files/dataset/lines.csv");
    if (infileLines.is_open()) {
        std::string line;

        while (std::getline(infileLines, line)) {

            std::stringstream ls(line);
            std::string code, name;

            std::getline(ls, code, ',');
            std::getline(ls, name);

            codeName.insert(code, name);

            paths.push_back("dataset/lines_" + code + "_0.csv");
            paths.push_back("dataset/lines_" + code + "_1.csv");
        }
    } else {
        throw "NoLinesFound!";
    }
    infileLines.close();


}