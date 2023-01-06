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
        int dist;
        string lastNode;
    };

    vector<Node> nodes;
    unordered_map<string,int> nodeKeys;
    unordered_map<string,list<Airport>> cities;

public:
    Graph(const Manager& manager);
    void addFlight(const string& airportTo,const string& airportFrom, const string& airline);
    void addNode(const string& airport);
    void tester();
    void bfs(const string& source);
    void spAirport(const string& airportFrom , const string& airportTo);   //shortest path airport
    void spCity(const string& airportFrom , const string& cityTo);  //shortest path city
    bool isCity(const string& city);  //checks if city exists
    bool isAirport(const string& airport); // checks if airport exists
};


#endif //PROJETOAED2_GRAPH_H
