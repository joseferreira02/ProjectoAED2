//
// Created by josep on 02/01/2023.
//

#include "Graph.h"

void Graph::addEdge(Airport airport) {

}

void Graph::addFlight(Airport airportFrom, Airport airportTo, string airline) {

}

void Graph::addNode(Airport airport) {
    Node node = {airport,{}, false};
    nodes.push_back(node);
}

Graph::Graph(Manager manager) {

    airports = manager.getAirports();

    for(Flight flight : manager.getFlights()){

        string airportSourceString = flight.getSource();
        string airportTarget = flight.getTarget();
        string airline = flight.getAirline();



    }
}
