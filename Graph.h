//
// Created by josep on 02/01/2023.
//

#ifndef PROJETOAED2_GRAPH_H
#define PROJETOAED2_GRAPH_H

#include <list>
#include <vector>
#include "airport.h"
#include "Manager.h"
#include "flight.h"


struct Edge{
    Airport airport; //destination
    string airline; //weight
};

struct Node{
    Airport airport;
    list<Edge> adj;
    bool  visited;
};


class Graph{
public:
    AirportHashTable airports;
    vector<Node> nodes;

private:
    Graph(Manager manager);
    void addEdge(Airport airport);
    void addNode(Airport airport);
    void addFlight(Airport airportFrom, Airport airportTo, string airline);
};


#endif //PROJETOAED2_GRAPH_H
