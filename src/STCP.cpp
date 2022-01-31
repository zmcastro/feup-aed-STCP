//
// Created by zemar on 28/01/2022.
//

#define INFstream (std::numeric_limits<std::streamsize>::max()/2)

#include <map>
#include <limits>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <regex>
#include "../headers/STCP.h"

STCP::STCP() {

    std::string auxStr;
    std::ifstream infileStops;
    infileStops.open("../files/dataset/stops.csv");
    if (infileStops.is_open()) {
        std::string line;

        std::getline(infileStops, auxStr); //skip 1st line
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
            int idx = stopMap.size();
            stopMap.insert(std::pair<std::string, int>(code, idx));
            stopGraph.addNode(newStop, idx);
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

                for (int i = 0; i < stoi(auxLs.str()); ++i) {
                    std::getline(infilePathLine0, currentStop, '\r');
                    std::stringstream auxCLs(currentStop);
                    std::regex newlines_re("\n+");
                    currentStop = std::regex_replace(currentStop, newlines_re, "");

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
                    std::getline(infilePathLine1, currentStop, '\r');
                    std::stringstream auxCLs(currentStop);
                    std::regex newlines_re("\n+");
                    currentStop = std::regex_replace(currentStop, newlines_re, "");

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

        }
    } else {
        throw "NoLinesFound!";
    }
    infileLines.close();
}


void STCP::mainInterface()
{
    bool requestChosen = false;
    int userR;
    do
    {
        cleanScreen();
        std::cout << "    Bem Vind@ a interface digital nao-oficial da STCP. O que pretende fazer? " << '\n' <<
        "    1.) Ver Paragens perto de mim" << '\n' <<
        "    2.) Melhor Percurso entre 2 locais" << '\n' <<
        "    3.) Organizar stops" << '\n' <<
        "    0.) Sair" << std::endl;

        if (inpCheck(userR)) {
            switch (userR) {
                case 1:
                    stopsNearInterface();
                    break;
                case 2:
                    bestTripInterface();
                    break;
                case 3:
                    stopManagementHandler();
                    break;
                case 0:
                    std::cout << "Obrigado pela sua preferencia! Esperamos encontra-l@ em breve novamente :)";
                    exit(0);
                default:
                    std::cout << "Insira uma opcao valida. (1/2/3/0) " << std::flush;
                    sleep(3);
                    std::cin.clear();
                    std::cin.ignore(INFstream, '\n');
            }
        }
        else {
            std::cout << "Insira uma opcao valida. (1/2/3/0) " << std::flush;
            sleep(3);
            std::cin.clear();
            std::cin.ignore(INFstream, '\n');
        }
    } while (!requestChosen);
}

void STCP::showStopsNear(std::vector<Stop> result){
    for (auto & i : result)
        std::cout << "Nome: " << i.getName() << "\tCodigo: " << i.getCode() << "\tZona: " << i.getZone() << '\n';
    if (result.empty())
        std::cout << "Nao ha paragens nas redondezas.\n";
}
void STCP::nearMeByStopHandler(){
    std::string nameStop;
    double maxDistance;
    std::cout << "    Por favor, diga-nos a sua localizacao. \n"
                 "    A paragem perto de si: ";             std::cin >> nameStop;
    std::cout << "\n    A distancia maxima (km): ";        std::cin >> maxDistance;

    showStopsNear(stopGraph.findNearestStops(stopMap[nameStop], maxDistance));
}
void STCP::nearMeByCoorHandler(){
    double latitude, longitude, maxDistance;
    std::cout << "    Por favor, diga-nos a sua localizacao. \n"
                 "    A sua latitude: ";                    std::cin >> latitude;
    std::cout << "\n    Agora insira a sua longitude: ";   std::cin >> longitude;
    std::cout << "\n    A distancia maxima (km): ";        std::cin >> maxDistance;
    showStopsNear(stopGraph.findNearestStops2(latitude,longitude, maxDistance));
}
void STCP::stopsNearInterface() {
    bool requestChosen = false;
    int userR;
    do
    {
        std::cout << "    Prefere inserir: \n"
                     "    1.) A paragem na qual se encontra \n"
                     "    2.) As suas coordenadas \n"
                     "    0.) Voltar ao menu\n" << std::flush;
        if (inpCheck(userR)) {
            double maxDistance;
            switch (userR) {
                case 1:
                    nearMeByStopHandler();
                    break;
                case 2:
                    nearMeByCoorHandler();
                    break;
                case 0:
                    std::cout << "Aguarde, por favor.\n";
                    requestChosen = true;
                    break;
                default:
                    std::cout <<"Insira uma opcao valida. (1/2/0)\n" << std::flush;
                    std::cin.clear();
                    std::cin.ignore(INFstream, '\n');
            }
        }
        else {
            std::cout << "Insira uma opcao valida. (1/2/0)" << std::flush;
            std::cin.clear();
            std::cin.ignore(INFstream, '\n');
        }
    } while (!requestChosen);
}

void STCP::stopManagementHandler() {
    bool requestChosen = false;
    int userR;
    std::string stopCode;

    do
    {
        std::cout << "    O que pretende fazer? \n"
                     "    1.) Ativar uma paragem \n"
                     "    2.) Desativar uma paragem  \n"
                     "    0.) Voltar ao menu\n" << std::flush;
        if (inpCheck(userR)) {
            switch (userR) {
                case 1:
                    std::cout << "Qual é o código da paragem que pretende ativar? " << std::endl;
                    std::cin >> stopCode;
                    stopGraph.enableStop(stopMap[stopCode]);
                    std::cout << "Paragem ativada. " << std::endl;
                    break;
                case 2:
                    std::cout << "Qual é o código da paragem que pretende desativar? " << std::endl;
                    std::cin >> stopCode;
                    stopGraph.disableStop(stopMap[stopCode]);
                    std::cout << "Paragem desativada. " << std::endl;
                    break;
                case 0:
                    std::cout << "Aguarde, por favor.\n";
                    requestChosen = true;
                    break;
                default:
                    std::cout <<"Insira uma opcao valida. (1/2/0)\n" << std::flush;
                    std::cin.clear();
                    std::cin.ignore(INFstream, '\n');
            }
        }
        else {
            std::cout << "Insira uma opcao valida. (1/2/0)" << std::flush;
            std::cin.clear();
            std::cin.ignore(INFstream, '\n');
        }
    } while (!requestChosen);
}

void STCP::showPath(const std::list<Stop> &stops) {
    for (auto it = stops.begin(); it != stops.end(); it++) {
        std::cout << it->getName() << " " << it->getCode();
        auto auxIt = it;
        auxIt++;
        if (auxIt == stops.end()) {
            std::cout << std::endl;
            break;
        }
        it++;
        std::cout << " -> Linha " << it->getLine() << std::endl;
        it--;
    }

}
void STCP::bestTripInterface() {
    bool requestChosen = false;
    int userR;

    int time;
    std::string stop1, stop2;

    std::cout << "Percurso feito de dia ou de noite? " << '\n'
              << "    0.) Dia" << '\n' << "    1.) Noite" << std::endl;
    std::cin >> time;
    std::cout << "Qual é o código da paragem inicial?" << std::endl;
    std::cin >> stop1;
    std::cout << "Qual é o código da paragem final?" << std::endl;
    std::cin >> stop2;

    do
    {
        std::cout << "    1.) Menos Paragens" << '\n' << "    2.) Menor Distancia" << '\n'
        <<  "    3.) Menos mudancas de Autocarro (Linha)" << '\n' <<  "    4.) Mais Economico" << '\n'
        << "    5.) Maior uso de linha específica" << '\n' << "    0.) Voltar ao menu" << '\n' << std::flush;

        if (inpCheck(userR)) {
            switch (userR) {
                case 1:
                    showPath(stopGraph.bfs_path(stopMap[stop1], stopMap[stop2], time));
                    break;
                case 2:
                    showPath(stopGraph.dijkstra_path(stopMap[stop1], stopMap[stop2], time, userR));
                    break;
                case 3:
                    showPath(stopGraph.dijkstra_path(stopMap[stop1], stopMap[stop2], time, userR));
                    break;
                case 4:
                    showPath(stopGraph.dijkstra_path(stopMap[stop1], stopMap[stop2], time, userR));
                    break;
                case 5:
                    showPath(stopGraph.dijkstra_path(stopMap[stop1], stopMap[stop2], time, userR));
                    break;
                case 0:
                    std::cout << "Aguarde, por favor.\n";
                    requestChosen = true;
                    break;
                default:
                    std::cout <<"Insira uma opcao valida. (1/2/0)\n" << std::flush;
                    std::cin.clear();
                    std::cin.ignore(INFstream, '\n');
            }
        }
        else {
            std::cout << "Insira uma opcao valida. (1/2/0)" << std::flush;
            std::cin.clear();
            std::cin.ignore(INFstream, '\n');
        }
    } while (!requestChosen);
}

