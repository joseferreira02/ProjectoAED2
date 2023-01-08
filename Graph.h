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
    AirportHashTable airports;
    vector<string> flights;

public:
    Graph(const Manager& manager);
    void addFlight(const string& airportTo,const string& airportFrom, const string& airline);
    void addNode(const string& airport);
    void tester();
    void bfs(const string& source);
    void weightedBfs(const string& source,const string& airline);
    void spAirport(const string& airportFrom , const string& airportTo);   //shortest path airport
    void spCity(const string& airportFrom , const string& cityTo);  //shortest path city
    void spCoordinate(const string& airportFrom ,const int& x ,const int& y,const int& radius);  // shortest path airport to coordinate area given ( x^2 + y^2 <= r2)
    void citySpAirport(const string& cityFrom , const string& airportTo);
    void coordinateSpAirport(const string& airportTo ,const int& x ,const int& y,const int& radius);
    void spByAirline(const string& airportFrom,const string& airportTo,const string& airline);
    bool isCity(const string& city);  //checks if city exists
    bool isAirport(const string& airport); // checks if airport exists
    bool isAirline(const string& airline);
    static void drawPath(vector<string> path ,const int& nrFlights); // draws paths
    static bool inCircle(const int& x,const int& y ,const int& r ,const int& rx ,const int& ry); // checks if x and y are in circle
};


#endif //PROJETOAED2_GRAPH_H