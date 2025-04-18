// ===== File: AirportGraph.cpp =====
#include "AirportGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int AirportGraph::findAirportIndex(const string& code) {
    if (airportIndexMap.find(code) != airportIndexMap.end()) {
        return airportIndexMap[code];
    }
    return -1;
}

void AirportGraph::addEdge(int srcIdx, int destIdx, int distance, int cost) {
    Edge* newEdge = new Edge{destIdx, distance, cost, airports[srcIdx].head};
    airports[srcIdx].head = newEdge;
}

void AirportGraph::loadTXT(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string origin, destination, city1, city2, distStr, costStr;

        getline(ss, origin, '|');
        getline(ss, destination, '|');
        getline(ss, city1, '|');
        getline(ss, city2, '|');
        getline(ss, distStr, '|');
        getline(ss, costStr, '|');

        int distance = stoi(distStr);
        int cost = stoi(costStr);

        int srcIdx = findAirportIndex(origin);
        if (srcIdx == -1) {
            Airport a = {origin, city1, "", nullptr, (int)airports.size()};
            airports.push_back(a);
            srcIdx = a.index;
            airportIndexMap[origin] = srcIdx;
        }

        int destIdx = findAirportIndex(destination);
        if (destIdx == -1) {
            Airport a = {destination, city2, "", nullptr, (int)airports.size()};
            airports.push_back(a);
            destIdx = a.index;
            airportIndexMap[destination] = destIdx;
        }

        addEdge(srcIdx, destIdx, distance, cost);
    }
    file.close();
}

void AirportGraph::displayAirports() const {
    for (const auto& airport : airports) {
        cout << airport.index << ": " << airport.code << " - " << airport.city << endl;
    }
}

void AirportGraph::displayGraph() const {
    for (const auto& airport : airports) {
        cout << airport.code << " -> ";
        for (Edge* e = airport.head; e != nullptr; e = e->next) {
            cout << airports[e->dest].code << " (Dist: " << e->distance << ", Cost: " << e->cost << ") ";
        }
        cout << endl;
    }
}

const vector<Airport>& AirportGraph::getAirports() const {
    return airports;
}