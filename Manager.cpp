//
// Created by jose on 27-12-2022.
//

#include "Manager.h"
#include <sstream>
#include <fstream>
#include <iostream>


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

AirportHashTable Manager::getAirports() {
    return airports;
}

list<Flight> Manager::getFlights() {
    return flights;
}
