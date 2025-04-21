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

    graph.findShortestRoute("IAD", "MIA", true, true);
    graph.findShortestRoute("PIT", "ACT", true, true);

    graph.findAllShortestRoutesToState("ATL", "TX");
    
    graph.findShortestRouteGivenStops("IAD", "MIA", 3);
    graph.findShortestRouteGivenStops("PIT", "ACT", 2);
    
    graph.displayConnections();
    
    graph.CreateGraphU();

    graph.primMST();
    
    graph.KruskalMST();
    return 0;
}
