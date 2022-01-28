//
// Created by mroch on 27/01/2022.
//
#include <map>
#include <vector>
#include <limits>
#include <zconf.h>
#include <fstream>
#include <sstream>
#include "../headers/STCP.h"
#include "Auxiliary.cpp"

STCP::STCP() {

    std::map<int, std::pair<std::string, std::string>> idStopZone;
    std::map<int, std::pair<double, double>> idCoor;
    std::map<std::string, int> codeID;
    std::map<std::string, std::string> codeName;
    std::vector<std::string> paths;
    std::string str;

    std::ifstream infileStops;
    infileStops.open("../files/dataset/stops.csv");
    if (infileStops.is_open()) {
        std::string line;
        int id = 1;

        std::getline(infileStops, str);//skip 1st line
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

            idStopZone.insert({id, {name, zone}});
            idCoor.insert({id, {latitude, longitude}});
            codeID.insert({code, id});

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


void STCP::Interface()
{
    bool requestChosen = false;
    int userR;
    do
    {
        cleanScreen();
        std::cout << "Bem Vind@ à interface digital não-oficial da STCP. O que pretende fazer? " << '\n' << "    1.) Ver Paragens perto de mim" << '\n' << "    2.) Melhor Percurso entre 2 locais" << '\n';
        std::cout << "    3.) Mudar de autocarro" << '\n' << " 4.) NÃO PEDIDO Ver as paragens de um autocarro " << '\n' << "    0.) Sair" << std::endl;
        if (inpCheck(userR)) {
            switch (userR) {
                case 1:
                    double latitude, longitude; //deviamos verificar se ficam no porto??
                    std::cout << "Por favor, diga-nos a sua localização. \n A sua latitude:";
                    std::cin >> latitude;
                    std::cout << "\nAgora insira a sua longitude: ";
                    std::cin >> longitude;
                    //funçao que devolve a mais próxima
                    break;
                case 2:
                    bestTripInterface();
                    break;
                case 3:
                    std::cout << "TO DO";
                    break;
                case 0:
                    exit(0);
                default:
                    std::cout << "Please enter a valid command. (1/2/3/4/5/6/0) " << std::flush;
                    sleep(3);
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else {
            std::cout << "Insira uma opçao valida. (1/2/3/0) " << std::flush;
            sleep(3);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!requestChosen);
}

void STCP::bestTripInterface() {
    bool requestChosen = false;
    int userR;
    do
    {
        std::cout << "    1.) Inserir as coordenadas dos locais." << '\n' << "    2.) Inserir as paragens dos locais" << '\n' << "    0.) Voltar ao menu" << '\n' << std::flush;
        if (inpCheck(userR)) {
            switch (userR) {
                case 1:
                    std::cout << "Por implementar. Obrigada pela preferencia.";
                    break;
                case 2:
                    std::cout << "Por implementar. Obrigada pela preferencia.";
                    break;
                case 0:
                    std::cout << "Aguarde, por favor.";
                    requestChosen = true;
                    break;
                default:
                    std::cout <<"Insira uma opçao valida. (1/2/0)" << std::flush;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else {
            std::cout << "Insira uma opçao valida. (1/2/0)" << std::flush;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!requestChosen);
}