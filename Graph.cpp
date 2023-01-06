//
// Created by josep on 02/01/2023.
//

#include <algorithm>
#include <iostream>
#include "Graph.h"

using  namespace std;
Graph::Graph(const Manager& manager) {

    addNode(""); // first useless node
    FlightMap flights = manager.getFlightsMap();
    for(const auto& flight : flights){
        addNode(flight.first);
        for(const auto& s : flight.second){
            addFlight(flight.first,s.first,s.second);
        }
    }
}

void Graph::addNode(const string &airport) {
    Node node = {airport,{}, false};
    nodeKeys[airport] = nodes.size();
    nodes.push_back(node);
}

void Graph::addFlight(const string &airportTo, const string &airportFrom, const string &airline) {
    int nodePosition = nodeKeys[airportTo];
    Edge edge = {airportFrom,airline};
    nodes[nodePosition].adj.push_back(edge);
}

void Graph::tester() {
    for(Node node:nodes){
        if(node.airport==""){cout << "STARTING" << endl;}
        cout<< "#########" <<node.airport<< "##########"<< endl;
        for(Edge edge : node.adj){
            std::cout << "   [" << edge.dest << "<---" << edge.airline << "]   ";
        }
        cout << endl;
    }

}
