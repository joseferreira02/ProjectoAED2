

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
    int countFlightsFromAirport(string airportName);
    int countUniqueAirlinesFromAirport(string airportName);
    int countUniqueDestinationsFromAirport(string AirportName);
    int countUniqueCountriesFromAirport(string AirportName);
    int countReachableAirports(string AirportName, int maxFlights);
    int countReachableCities(string startingAirport, int maxFlights);
    int countReachableCountries(string AirportName, int maxFlights);
    int networkAirports();
    int networkFlights();
    int networkAirlines();
    int countryAirports(const string& country);
    int countryFlights(const string& country);
    int countryAirlines(const string& country);
    int airportsUsingAirline(const string& airline);
    int flightsUsingAirline(const string& airline);
    int topKAirportsWithMostFlights(int k);
    int topKAirportsWithMostAirlines(int k);
    static double distanceUsingHaversine(double lat1, double lon1, double lat2, double lon2);
    AirportHashTable getAirports() const;
    list<Flight> getFlights();
    void listToMap();
    FlightMap  getFlightsMap() const;
    unordered_map<string,list<Airport>> getCities() const;
};


#endif //PROJETOAED2_MANAGER_H
