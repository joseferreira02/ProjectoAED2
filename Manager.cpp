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