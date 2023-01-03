//
// Created by jose on 27-12-2022.
//

#include "Manager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>


//Constructor
Manager::Manager() {
    loadAirports();
    loadFlights();
    loadAirlines();
    loadCities();
}

//Loaders
void Manager::loadAirports() {
    string  line;
    ifstream file;

    file.open("airports.csv");
    getline(file,line);

    //temp variables
    string Code;
    string Name;
    string City;
    string Country;
    string Latitude;
    string Longitude;
    while(!file.eof()){
        getline(file,line);
        istringstream currLine(line);

        //loads each temp variable
        getline(currLine,Code,',');
        getline(currLine,Name,',');
        getline(currLine,City,',');
        getline(currLine,Country,',');
        getline(currLine,Latitude,',');
        getline(currLine,Longitude,',');
        airports.insert(Airport(Code,Name,City,Country,stof(Latitude), stof(Longitude)));
    }

}

void Manager::loadFlights(){
    Flight someflight;

    ifstream aflight;
    aflight.open("flights.csv");

    string line;
    getline(aflight, line); // Passar á frente a primeira linha do ficheiro

    while(getline(aflight, line)){
        string temp;
        stringstream input(line);

        getline(input, temp, ','); // Obter Source
        someflight.setSource(temp);
        getline(input, temp, ','); // Obter Target
        someflight.setTarget(temp);
        getline(input, temp, ','); // Obter Airline
        someflight.setAirline(temp);
        flights.push_back(someflight);
    }
}



void Manager::loadAirlines() {
    ifstream anairline;
    anairline.open("airlines.csv");
    string line;
    getline (anairline, line);
    while(getline(anairline, line)){
        string temp;
        stringstream input(line);
        string code, name, callsign, country;
        getline(input, code, ',');
        getline(input, name, ',');
        getline(input, callsign, ',');
        getline(input, country, ',');
        Airline someairline(code, name, callsign, country);
        airlines.push_back(someairline);
    }
}

void Manager::loadCities() {
    string  line;
    ifstream file;

    file.open("airports.csv");
    getline(file,line);

    list<Airport> tempAirports;
    string Code;
    string Name;
    string City;
    string lastCity;
    string Country;
    string Latitude;
    string Longitude;
    bool isFirst = false;

    while(!file.eof()){
        if(!getline(file,line)){cities[lastCity] = tempAirports;}
        istringstream currLine(line);

        //loads each temp variable
        getline(currLine,Code,',');
        getline(currLine,Name,',');
        getline(currLine,City,',');
        getline(currLine,Country,',');
        getline(currLine,Latitude,',');
        getline(currLine,Longitude,',');

        //checks if it's the first element and if it's the same city as the city in the last line
        if(lastCity!=City&&isFirst){
            cities[lastCity] = tempAirports;
            tempAirports.clear();
            tempAirports.emplace_back(Code,Name,City,Country,stof(Latitude), stof(Longitude));
        }else{
            tempAirports.emplace_back(Code,Name,City,Country,stof(Latitude), stof(Longitude));
        }

        isFirst= true;
        lastCity = City;
    }

}

int Manager::countFlightsFromAirport(string airportName) {
    int count = 0;
    for (Flight flight : flights) {
        if (flight.getSource() == airportName) {
            count++;
        }
    }
    return count;
}

int Manager::countUniqueAirlinesFromAirport(string airportName){
    unordered_set<string> airlines;
    for (Flight flight: flights){
        if (flight.getSource() == airportName){
            airlines.insert(flight.getAirline());
        }
    }
    return airlines.size();
}

int Manager::countUniqueDestinationsFromAirport(string AirportName) {
    unordered_set<string> destinations;
    for (Flight flight: flights){
        if (flight.getSource() == AirportName){
            destinations.insert(flight.getTarget());
        }
    }
    return destinations.size();
}
/*
int Manager::countUniqueCountriesFromAirport(string AirportName) {
    unordered_set<string> countries;
    for (Flight flight: flights) {
        if (flight.getSource() == AirportName) {
            Airport target = airports[flight.getTarget()];
            countries.insert(target.getCountry());
        }
    }
    return countries.size();
}
*/
int Manager::countUniqueCountriesFromAirport(string AirportName) {
    unordered_set<string> countries;
    for (Flight flight: flights) {
        if (flight.getSource() == AirportName) {
            // Find the Airport object with the matching target code
            for (const Airport& airport : airports) {
                if (airport.getCode() == flight.getTarget()) {
                    countries.insert(airport.getCountry());
                    break;
                }
            }
        }
    }
    return countries.size();
}

int Manager::countReachableAirports(string AirportName, int maxFlights) {
    unordered_set<string> visitedAirports;
    queue<Flight> flightsToProcess;
    visitedAirports.insert(AirportName);
    for (Flight flight: flights) {
        if (flight.getSource() == AirportName) {
            flightsToProcess.push(flight);
        }
    }
    int flightsProcessed = 0;
    while (!flightsToProcess.empty() && flightsProcessed < maxFlights) {
        Flight currentFlight = flightsToProcess.front();
        flightsToProcess.pop();
        string target = currentFlight.getTarget();
        if (visitedAirports.find(target) == visitedAirports.end()) {
            visitedAirports.insert(target);
            for (Flight flight: flights) {
                if (flight.getSource() == target) {
                    flightsToProcess.push(flight);
                }
            }
        }
        flightsProcessed++;
    }
    return visitedAirports.size();
}

int Manager::countReachableCities(string startingCity, int maxFlights) {
    unordered_set<string> visitedCities;
    queue<pair<string,int>> citiesToProcess;
    visitedCities.insert(startingCity);
    for (Airport airport: cities[startingCity]) {
        citiesToProcess.push(make_pair(airport.getCity(), 1));
    }
    while (!citiesToProcess.empty()) {
        pair<string,int> currentCity = citiesToProcess.front();
        citiesToProcess.pop();
        string city = currentCity.first;
        int flights = currentCity.second;
        if (visitedCities.find(city) == visitedCities.end() && flights <= maxFlights) {
            visitedCities.insert(city);
            for (Airport airport: cities[city]) {
                citiesToProcess.push(make_pair(airport.getCity(), flights+1));
            }
        }
    }
    return visitedCities.size();
}

int Manager::countReachableCountries(string AirportName, int maxFlights) {
    unordered_set<string> visitedCountries;
    queue<Flight> flightsToProcess;
    // Find the airport with the given name
    Airport startingAirport = Airport(AirportName, "", "", "", 0, 0);
    auto it = airports.find(startingAirport);
    if (it == airports.end()) {
        return -1;  // Airport not found
    }

// Insert the country of the starting airport into the set of visited countries
    visitedCountries.insert((*it).getCountry());

// Find all flights departing from the starting airport and add them to the queue
    for (Flight flight: flights) {
        if (flight.getSource() == AirportName) {
            flightsToProcess.push(flight);
        }
    }

    int flightsProcessed = 0;
// Perform a breadth-first search to find all reachable airports and their countries
    while (!flightsToProcess.empty() && flightsProcessed < maxFlights) {
        Flight currentFlight = flightsToProcess.front();
        flightsToProcess.pop();

        // Find the destination airport of the current flight
        Airport destination = Airport(currentFlight.getTarget(), "", "", "", 0, 0);
        it = airports.find(destination);
        if (it == airports.end()) {
            continue;  // Airport not found
        }
        string targetCountry = (*it).getCountry();

        // If the country of the destination airport has not been visited yet, add it to the set of visited countries
        // and find all flights departing from the destination airport and add them to the queue
        if (visitedCountries.find(targetCountry) == visitedCountries.end()) {
            visitedCountries.insert(targetCountry);
            for (Flight flight: flights) {
                if (flight.getSource() == currentFlight.getTarget()) {
                    flightsToProcess.push(flight);
                }
            }
        }

        flightsProcessed++;
    }

    return visitedCountries.size();
}



