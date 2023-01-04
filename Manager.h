

//
// Created by jose on 27-12-2022.
//

#ifndef PROJETOAED2_MANAGER_H
#define PROJETOAED2_MANAGER_H

#include <list>
#include <unordered_map>
#include <vector>
#include "airport.h"
#include "airline.h"
#include "flight.h"

using namespace std;

typedef unordered_map<string,vector<pair<string,string>>> FlightMap;

class Manager {

private:
    AirportHashTable airports;
    unordered_map<string,list<Airport>> cities;
    FlightMap flightsMap; // list flights in map structure where source airport is key having a pair with target + airline ( used in load of graph)
    list<Airline> airlines;
    list<Flight> flights;
public:
    Manager();
    void loadAirports();
    void loadFlights();
    void loadAirlines();
    void loadCities();
    AirportHashTable getAirports();
    list<Flight> getFlights();
    void listToMap();
    FlightMap  getFlightsMap() const;
};


#endif //PROJETOAED2_MANAGER_H