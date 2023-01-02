

//
// Created by jose on 27-12-2022.
//

#ifndef PROJETOAED2_MANAGER_H
#define PROJETOAED2_MANAGER_H

#include <list>
#include <unordered_map>
#include "airport.h"
#include "airline.h"
#include "flight.h"

using namespace std;

class Manager {

private:
    AirportHashTable airports;
    unordered_map<string,list<Airport>> cities;
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
};


#endif //PROJETOAED2_MANAGER_H