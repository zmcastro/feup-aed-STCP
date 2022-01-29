//
// Created by zemar on 28/01/2022.
//

#define INFstream (std::numeric_limits<std::streamsize>::max()/2)

#include <map>
#include <limits>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include "../headers/STCP.h"
#include "../headers/Auxiliary.h"

STCP::STCP() {

    std::string auxStr;
    std::ifstream infileStops;
    infileStops.open("../files/dataset/stops.csv");
    if (infileStops.is_open()) {
        std::string line;

        std::getline(infileStops, auxStr);//skip 1st line
        while (std::getline(infileStops, line)) {

            std::stringstream ls(line);
            std::string code, name, zone, strLat, strLong;
            double latitude, longitude;

            std::getline(ls, code, ',');
            std::getline(ls, name, ',');
            std::getline(ls, zone, ',');
            std::getline(ls, strLat, ',');
            std::getline(ls, strLong, '\r');

            latitude = std::stod(strLat);
            longitude = std::stod(strLong);

            Stop newStop = Stop(code, name, zone, latitude, longitude);
            int newIdx = stopMap.size();
            stopMap.insert(std::pair<std::string, int>(code, newIdx));
            stopGraph.addNode(newStop, newIdx);
        }
    } else {
        throw "NoStopsFound!";
    }
    infileStops.close();

    std::ifstream infileLines;
    infileLines.open("../files/dataset/lines.csv");
    if (infileLines.is_open()) {
        std::string line;

        std::getline(infileLines, auxStr);
        while (std::getline(infileLines, line)) {

            std::stringstream ls(line);
            std::string code, name;
            std::vector<std::string> linePath0;
            std::vector<std::string> linePath1;

            std::getline(ls, code, ',');
            std::getline(ls, name);

            std::ifstream infilePathLine0;
            infilePathLine0.open("../files/dataset/line_" + code + "_0.csv");
            if (infilePathLine0.is_open()) {
                std::string lastStop, currentStop, nStops;

                std::getline(infilePathLine0, nStops); //get nstops
                std::stringstream auxLs(nStops);

                for (int i = 0; i < stoi(auxLs.str()); i++) {
                    std::getline(infilePathLine0, currentStop);

                    if (i > 0) {
                        stopGraph.addEdge(stopMap[lastStop], stopMap[currentStop], code);
                        linePath0.push_back(lastStop);
                        linePath0.push_back(currentStop);
                    }

                    lastStop = currentStop;
                }
            } else
                throw "NoLinePathFound!";

            infilePathLine0.close();

            std::ifstream infilePathLine1;
            infilePathLine1.open("../files/dataset/line_" + code + "_1.csv");
            if (infilePathLine1.is_open()) {
                std::string lastStop, currentStop, nStops;

                std::getline(infilePathLine1, nStops); //get nstops
                std::stringstream auxLs(nStops);

                for (int i = 0; i < stoi(auxLs.str()); i++) {
                    std::getline(infilePathLine1, currentStop );

                    if (i > 0) {
                        stopGraph.addEdge(stopMap[lastStop], stopMap[currentStop], code);
                        linePath1.push_back(lastStop);
                        linePath1.push_back(currentStop);
                    }

                    lastStop = currentStop;
                }
            } else
                throw "NoLinePathFound!";

            infilePathLine1.close();

            Line newLine = Line(code, name, linePath0, linePath1, code.back() != 'M');
            lines.push_back(newLine);
        }
    } else {
        throw "NoLinesFound!";
    }
    infileLines.close();
}

void STCP::addStop(const Stop &stop) {
    stopMap[stop.getCode()] = stops.size() - 1;
    this->stops.push_back(stop);
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
                    std::cout << "Insira uma opçao valida. (1/2/3/0) " << std::flush;
                    sleep(3);
                    std::cin.clear();
                    std::cin.ignore(INFstream, '\n');
            }
        }
        else {
            std::cout << "Insira uma opçao valida. (1/2/3/0) " << std::flush;
            sleep(3);
            std::cin.clear();
            std::cin.ignore(INFstream, '\n');
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
                    std::cin.ignore(INFstream, '\n');
            }
        }
        else {
            std::cout << "Insira uma opçao valida. (1/2/0)" << std::flush;
            std::cin.clear();
            std::cin.ignore(INFstream, '\n');
        }
    } while (!requestChosen);
}

void STCP::testOutput() {
    std::cout << stopGraph.findStop(0).getName();
}


