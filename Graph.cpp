//
// Created by josep on 02/01/2023.
//

#include <algorithm>
#include <iostream>
#include <queue>
#include "Graph.h"

using  namespace std;
Graph::Graph(const Manager& manager) {

    addNode(""); // first useless node
    FlightMap flights = manager.getFlightsMap();
    cities = manager.getCities();
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
        if(node.airport.empty()){cout << "STARTING" << endl;}
        cout<< "#########" <<node.airport<< "##########"<< endl;
        for(const Edge& edge : node.adj){
            std::cout << "   [" << edge.dest << "<---" << edge.airline << "]   ";
        }
        cout << endl;
    }

}

void Graph::bfs(const string& source) {
    //sets preferred values before start
    for(Node& node : nodes){node.visited= false;node.dist = -1;node.lastNode = "";}
    nodes[nodeKeys[source]].visited = true;
    nodes[nodeKeys[source]].dist = 0;

    //basic bfs
    queue<string> q;
    q.push(source);
    while(!q.empty()){
        string front = q.front();q.pop();
        int frontKey = nodeKeys[front];
        for(const Edge& e : nodes[frontKey].adj ){
            int neighbourKey = nodeKeys[e.dest];
            if(!nodes[neighbourKey].visited){
                q.push(e.dest);
                nodes[neighbourKey].visited = true;
                nodes[neighbourKey].dist = nodes[frontKey].dist +1;
                nodes[neighbourKey].lastNode = nodes[frontKey].airport;
            }
        }
    }


}

void Graph::spAirport(const string& airportFrom , const string& airportTo) {
    //checks conditions of args
    if(!isAirport(airportFrom) || !isAirport(airportTo)){cout << "ERROR: introduce existing airports";return;}

    bfs(airportFrom);
    //resources
    vector<string> path;
    string currPos = airportTo;
    //temps
    int currKey = nodeKeys[airportTo];
    int nrFlights = nodes[currKey].dist;

    //checks if currPos last node is our airport start
    //Its retracing the path from "Airportfrom to Airportto" by checking the last node and updating that node to out path(which is reversed)
    while(currPos!=airportFrom){
        path.push_back(currPos);
        currPos = nodes[currKey].lastNode;
        currKey = nodeKeys[currPos];
        if(currPos.empty()){cout<< "IMPOSSIBLE PATH" ;return;} // Checks if currNODE doest have
    }
    if(currPos==airportFrom){path.push_back(airportFrom);}

    //drawing stuff
    cout << "Starting path: ";
    for (int i = path.size()-1; i >=0 ; --i) {
        cout << path[i];if(i!=0)cout << "->";
    }
    cout << endl << "Number of flights: " << nrFlights << endl;
}

void Graph::spCity(const string& airportFrom , const string& cityTo) {
    //checks conditions of args
    if(!isAirport(airportFrom) || !isCity(cityTo)){cout << "ERROR: introduce existing airport/city";return;}

    bfs(airportFrom);
    //finds airport from cityTo with last amount of flights
    string smallestFlight;
    int nrFlights1 = INT32_MAX;
    int currKey1;
    for(const Airport& x : cities[cityTo]){
        //finds index of curr flight
        currKey1 = nodeKeys[x.getCode()];
        //checks nr of flights of curr airport
        if(nodes[currKey1].dist<nrFlights1){
            smallestFlight = nodes[currKey1].airport;
            nrFlights1 = nodes[currKey1].dist;
        }
    }

    //same logic as in spA;
    string airportTo = smallestFlight;
    vector<string> path;
    string currPos = airportTo;
    int currKey = nodeKeys[airportTo];
    int nrFlights = nodes[currKey].dist;
    while(currPos!=airportFrom){
        path.push_back(currPos);
        currPos = nodes[currKey].lastNode;
        currKey = nodeKeys[currPos];
        if(currPos.empty()){cout<< "IMPOSSIBLE PATH" ;return;} // Checks if currNODE doest have
    }
    if(currPos==airportFrom){path.push_back(airportFrom);}

    //drawing stuff
    cout << "Starting path: ";
    for (int i = path.size()-1; i >=0 ; --i) {
        cout << path[i];if(i!=0)cout << "->";
    }
    cout << endl << "Number of flights: " << nrFlights << endl;

}

bool Graph::isCity(const string &city) {
    return cities.find(city) != cities.end();
}

bool Graph::isAirport(const string &airport) {
    return nodeKeys.find(airport) != nodeKeys.end();
}
