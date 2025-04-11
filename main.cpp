// ===== File: main.cpp =====
#include <iostream>
#include "AirportGraph.h"
using namespace std;

int main() {
    AirportGraph graph;
    graph.loadTXT("airports.txt");

    cout << "\n--- All Airports ---" << endl;
    graph.displayAirports();

    cout << "\n--- Airport Graph (Adjacency List) ---" << endl;
    graph.displayGraph();

    return 0;
}