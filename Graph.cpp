//
// Created by josep on 02/01/2023.
//

#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include "Graph.h"

using  namespace std;
Graph::Graph(const Manager& manager) {

    addNode(""); // first useless node
    FlightMap flights1 = manager.getFlightsMap();
    cities = manager.getCities();
    airports = manager.getAirports();
    for(const auto& flight : flights1){
        addNode(flight.first);
        for(const auto& s : flight.second){
            addFlight(flight.first,s.first,s.second);
            flights.push_back(s.second);
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
    for(const Node& node:nodes){
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
    drawPath(path,nrFlights);
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

    while(currPos!=airportFrom){
        path.push_back(currPos);
        currPos = nodes[currKey].lastNode;
        currKey = nodeKeys[currPos];
        if(currPos.empty()){cout<< "IMPOSSIBLE PATH" ;return;} // Checks if currNODE doest have
    }
    if(currPos==airportFrom){path.push_back(airportFrom);}

    //drawing stuff
    drawPath(path,nrFlights1);

}

bool Graph::isCity(const string &city) {
    return cities.find(city) != cities.end();
}

bool Graph::isAirport(const string &airport) {
    return nodeKeys.find(airport) != nodeKeys.end();
}

void Graph::spCoordinate(const string &airportFrom, const int &x, const int &y, const int &radius) {
    //checks condition
    if(!isAirport(airportFrom)){cout << "ERROR: introduce existing airports";return;}

    //get list of airports in wanted radius
    list<string> inAirports;
    for(const auto& a : airports){
        if(inCircle(a.getLatitude(),a.getLongitude(),radius,x,y))inAirports.push_back(a.getCode());
    }

    bfs(airportFrom);

    //checks condition
    if(inAirports.empty()){cout << "ERROR: introduce existing coordinates";return;}


    //finds airport by smallest distance to source
    string smallestFlight;
    int numFlights = INT32_MAX;
    for(const string& a : inAirports){
        if(nodes[nodeKeys[a]].dist<numFlights){
            smallestFlight = a;
            numFlights = nodes[nodeKeys[a]].dist;
        }
    }

    //uses spAirport logic
    vector<string> path;
    string airportTo = smallestFlight;
    string currPos = airportTo;
    int currKey = nodeKeys[airportTo];
    while(currPos!=airportFrom){
        path.push_back(currPos);
        currPos = nodes[currKey].lastNode;
        currKey = nodeKeys[currPos];
        if(currPos.empty()){cout<< "IMPOSSIBLE PATH" ;return;} // Checks if currNODE doest have
    }
    if(currPos==airportFrom){path.push_back(airportFrom);}

    //drawing stuff
    drawPath(path,numFlights);

}

void Graph::drawPath(vector<string> path,const int& nrFlights) {
    cout << "###############  Starting path  ##########################" << endl;
    for (int i = path.size()-1; i >=0 ; --i) {
        cout << path[i];if(i!=0)cout << " -> ";
    }
    cout << endl;
    cout << endl << "Number of flights: " << nrFlights << endl;
    cout << "##########################################################";
}

bool Graph::inCircle(const int &x, const int &y, const int &r, const int &rx, const int &ry) {
    double d = pow(x-rx,2) + pow(y-ry,2);
    return d<= pow(r,2);
}

void Graph::citySpAirport(const string &cityFrom, const string &airportTo) {

    //checks condition
    if(!isAirport(airportTo) || !isCity(cityFrom)){cout << "ERROR: introduce existing airport/city";return;}

    bfs(airportTo);
    //gets the airport with lower nr flights
    string airportFrom;
    int nrFlights = INT32_MAX;
    for(const Airport& airport : cities[cityFrom]){
        if(nrFlights>nodes[nodeKeys[airport.getCode()]].dist){
            airportFrom = airport.getCode();
            nrFlights = nodes[nodeKeys[airport.getCode()]].dist;
        }
    }

    //resets bfs to wanted path
    bfs(airportFrom);
    //uses spAirport logic
    vector<string> path;
    string currPos = airportTo;
    int currKey = nodeKeys[airportTo];
    while(currPos!=airportFrom){
        path.push_back(currPos);
        currPos = nodes[currKey].lastNode;
        currKey = nodeKeys[currPos];
        if(currPos.empty()){cout<< "IMPOSSIBLE PATH" ;return;} // Checks if currNODE doest have
    }
    if(currPos==airportFrom){path.push_back(airportFrom);}

    //drawing stuff
    drawPath(path,nrFlights);
}

void Graph::coordinateSpAirport(const string &airportTo, const int &x, const int &y, const int &radius) {

    if(!isAirport(airportTo)){cout << "ERROR: introduce existing airports";return;}

    //get list of airports in wanted radius
    list<string> inAirports;
    for(const auto& a : airports){
        if(inCircle(a.getLatitude(),a.getLongitude(),radius,x,y))inAirports.push_back(a.getCode());
    }

    if(inAirports.empty()){cout << "ERROR: introduce existing coordinates";return;}


    bfs(airportTo);

    //finds airport by smallest distance to source
    string smallestFlight;
    int numFlights = INT32_MAX;
    for(const string& a : inAirports){
        if(nodes[nodeKeys[a]].dist<numFlights){
            smallestFlight = a;
            numFlights = nodes[nodeKeys[a]].dist;
        }
    }

    string airportFrom = smallestFlight;
    //resets bfs to desired path
    bfs(airportFrom);
    //uses spAirport logic
    vector<string> path;
    string currPos = airportTo;
    int currKey = nodeKeys[airportTo];
    while(currPos!=airportFrom){
        path.push_back(currPos);
        currPos = nodes[currKey].lastNode;
        currKey = nodeKeys[currPos];
        if(currPos.empty()){cout<< "IMPOSSIBLE PATH" ;return;} // Checks if currNODE doest have
    }
    if(currPos==airportFrom){path.push_back(airportFrom);}

    //drawing stuff
    drawPath(path,numFlights);
}


void Graph::spByAirline(const string &airportFrom, const string &airportTo, const string &airline) {
    if(!isAirport(airportFrom) || !isAirport(airportTo)){cout << "ERROR: introduce existing airports";return;}
    if(!isAirline(airline)){cout << "ERROR: introduce existing airline";return;}

    weightedBfs(airportFrom,airline);

    vector<string> path;
    int nrFlights = nodes[nodeKeys[airportTo]].dist;
    string currPos = airportTo;
    int currKey = nodeKeys[airportTo];
    while(currPos!=airportFrom){
        path.push_back(currPos);
        currPos = nodes[currKey].lastNode;
        currKey = nodeKeys[currPos];
        if(currPos.empty()){cout<< "IMPOSSIBLE PATH" ;return;} // Checks if currNODE doest have
    }
    if(currPos==airportFrom){path.push_back(airportFrom);}

    drawPath(path,nrFlights);
}

void Graph::weightedBfs(const string &source,const string& airline) {
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
            if(!nodes[neighbourKey].visited && e.airline==airline){
                q.push(e.dest);
                nodes[neighbourKey].visited = true;
                nodes[neighbourKey].dist = nodes[frontKey].dist +1;
                nodes[neighbourKey].lastNode = nodes[frontKey].airport;
            }
        }
    }
}

bool Graph::isAirline(const string &airline) {
    for(const string& flight : flights){if(airline==flight)return true;}
    return false;
}