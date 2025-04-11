// ===== File: AirportGraph.h =====
#ifndef AIRPORT_GRAPH_H
#define AIRPORT_GRAPH_H

#include <string>
#include <vector>
#include <map>
using namespace std;

struct Edge {
    int dest;       // destination airport index
    int distance;
    int cost;
    Edge* next;
};

struct Airport {
    string code;
    string city;
    string state;
    Edge* head;
    int index;
};

class AirportGraph {
private:
    vector<Airport> airports;  // list of airports
    map<string, int> airportIndexMap; // map airport code to index
    int findAirportIndex(const string& code);
    void addEdge(int srcIdx, int destIdx, int distance, int cost);

public:
    void loadTXT(const string& filename); // updated to read from .txt
    void displayAirports() const;
    void displayGraph() const;
    const vector<Airport>& getAirports() const;
};

#endif