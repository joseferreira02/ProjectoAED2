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




class Graph {

    struct Edge{
        string dest;
        string airline;
    };

    struct Node{
        string airport;
        list<Edge> adj;
        bool visited;
    };

    vector<Node> nodes;
    unordered_map<string,int> nodeKeys;

public:
    Graph(const Manager& manager);
    void addFlight(const string& airportTo,const string& airportFrom, const string& airline);
    void addNode(const string& airport);
    void tester();
};


#endif //PROJETOAED2_GRAPH_H
