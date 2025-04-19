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

//Counts and Sorts the connections of all airports. (could be optimized)
void AirportGraph::displayConnections() const {
    //array to store amount of connections
    int connections[airports.size()] = { 0 };
    //iterates through all connection add increments the array for both start and destination
    for (const auto& airport : airports) {
        
        for (Edge* e = airport.head; e != nullptr; e = e->next) {
            connections[airport.index]++;
            connections[e->dest]++; 
        }
        
    }
    
    struct AirportConnection {
        string code;
        int count;
    };
    
    AirportConnection airportConnections[airports.size()];
    
    // Populate the array
    for (const auto& airport : airports) {
        airportConnections[airport.index].code = airport.code;
        airportConnections[airport.index].count = connections[airport.index];
    }
    
    // Sort the array in descending order based on connection count
    for (size_t i = 0; i < airports.size() - 1; i++) {
        for (size_t j = 0; j < airports.size() - i - 1; j++) {
            if (airportConnections[j].count < airportConnections[j+1].count) {
                // Swap
                AirportConnection temp = airportConnections[j];
                airportConnections[j] = airportConnections[j+1];
                airportConnections[j+1] = temp;
            }
        }
    }
    
    // Display the sorted connections
    cout << "Airport connections:" << endl;
    for (size_t i = 0; i < airports.size(); i++) {
        cout << airportConnections[i].code << ": " << airportConnections[i].count << endl;
    }
}
