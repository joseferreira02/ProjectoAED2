//
// Created by jose on 27-12-2022.
//

#include "Manager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>
#include <cmath>


//Constructor
Manager::Manager() {
    loadAirports();
    loadFlights();
    loadAirlines();
    loadCities();
    listToMap();
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
        /*
        Airport temp =  Airport(Code,Name,City,Country,stof(Latitude), stof(Longitude));
        pair<string,Airport> tempPair = {Code,temp};
        tester.insert(tempPair);
         */
    }
    file.close();
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
    aflight.close();
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
    anairline.close();
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
    file.close();
}


int Manager::countFlightsFromAirport(string airportName) {
    int count = 0;
    for (Flight flight : flights) {
        if (flight.getSource() == airportName) {
            count++;
            cout << flight.getSource() << " " << flight.getTarget() << " " << flight.getAirline() << endl;
        }
    }
    cout << "The total number of flights departing from the airport " << airportName << " is: ";
    return count;
}

int Manager::countUniqueAirlinesFromAirport(string airportName){
    unordered_set<string> airlines;
    for (Flight flight: flights){
        if (flight.getSource() == airportName){
            airlines.insert(flight.getAirline());
        }
    }
    vector<string> vec(airlines.begin(), airlines.end());
    for (string x: airlines){
        cout << x << endl;
    }
    cout << "The total number of airlines is ";
    return airlines.size();
}

int Manager::countUniqueDestinationsFromAirport(string AirportName) {
    unordered_set<string> destinations;
    for (Flight flight: flights){
        if (flight.getSource() == AirportName){
            destinations.insert(flight.getTarget());
        }
    }
    for (string x: destinations){
        cout << x << endl;
    }
    cout << "The total number of unique destinations is: ";
    return destinations.size();
}

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
    for (string x: countries){
        cout << x << endl;
    }
    cout << "The total number of unique countries is ";
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
    for (string x: visitedAirports){
        cout << x << endl;
    }
    cout << "The total number of reachable airports is: ";
    return visitedAirports.size();
}

int Manager::countReachableCities(string AirportName, int maxFlights) {
    unordered_set<string> visitedAirports;
    unordered_set<string> visitedCities;
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
    for (string visitedAirport: visitedAirports) {
        auto it = airports.begin();
        while (it != airports.end()) {
            if (it->getCode() == visitedAirport) {
                break;
            }
            it++;
        }
        if (it == airports.end()) {
            continue;
        }
        string city = it->getCity();
        if (visitedCities.find(city) == visitedCities.end()) {
            visitedCities.insert(city);
        }
    }
    for (string x: visitedCities){
        cout << x << endl;
    }
    cout << "The total number of reachable cities is: ";
    return visitedCities.size();
}

int Manager::countReachableCountries(string AirportName, int maxFlights) {
    unordered_set<string> visitedCountries;
    queue<Flight> flightsToProcess;

    // Find the starting airport
    auto it = airports.begin();
    while (it != airports.end()) {
        if (it->getCode() == AirportName) {
            break;
        }
        it++;
    }
    if (it == airports.end()) {
        return -1; // Airport not found
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
        it = airports.begin();
        while (it != airports.end()) {
            if (it->getCode() == currentFlight.getTarget()) {
                break;
            }
            it++;
        }
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
                    if (flightsProcessed < maxFlights) {
                        flightsToProcess.push(flight);
                    }
                }
            }
        }

        flightsProcessed++;
    }
    for (string x: visitedCountries){
        cout << x << endl;
    }
    cout << "The total number of reachable countries is: ";
    return visitedCountries.size();
}

void Manager::showAirportInformation(string AirportName){
    bool airportFound = false;
    for (Airport anairport : airports){
        if (anairport.getCode() == AirportName) {
            airportFound = true;
            cout << "Name : " << anairport.getName() << endl;
            cout << "City : " << anairport.getCountry() << endl;
            cout << "Country : " << anairport.getCountry() << endl;
            cout << "Latitude : " << anairport.getLatitude() << endl;
            cout << "Longitude : " << anairport.getLongitude() << endl;
            break;
        }
        else{
            continue;
        }
    }
    if (airportFound == false){
        cout << "Please enter a valid airport code";
    }
}

double deg2rad(double deg) {
    return deg * (M_PI / 180);
}

double Manager::distanceUsingHaversine(double lat1, double lon1, double lat2, double lon2) {
// Convert latitude and longitude to radians
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);
    // Haversine formula
    double a = pow(std::sin((lat2 - lat1) / 2), 2) + cos(lat1) * cos(lat2) * pow(std::sin((lon2 - lon1) / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

// Earth's radius in kilometers
    double r = 6371;

// Distance in kilometers
    double d = r * c;
    cout << "The distance, in kilometres, between those 2 coordinates is: ";
    return d;
}

AirportHashTable Manager::getAirports() const {
    return airports;
}

list<Flight> Manager::getFlights() {
    return flights;
}

FlightMap Manager::getFlightsMap() const {
    return flightsMap;
}


void Manager::listToMap() {
    for(const Flight& flight : flights){
        flightsMap[flight.getSource()].emplace_back(flight.getTarget(),flight.getAirline());
    }
}

unordered_map<string, list<Airport>> Manager::getCities() const {
    return cities;
}
