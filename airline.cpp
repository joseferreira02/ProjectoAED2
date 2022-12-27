#include "airline.h"

using namespace std;

Airline::Airline(string Airline_Code, string Airline_Name, string Callsign, string Country){
    this->Airline_Code = Airline_Code;
    this->Airline_Name = Airline_Name;
    this->Callsign = Callsign;
    this->Country = Country;
}

void Airline::setCode(string s){
    Airline_Code = s;
}

void Airline::setName(string s){
    Airline_Name = s;
}

void Airline::setCallsign(string s){
    Callsign = s;
}

void Airline::setCountry(string s){
    Country = s;
}

string Airline::getCode(){
    return Airline_Code;
}

string Airline::getName(){
    return Airline_Name;
}

string Airline::getCallsign(){
    return Callsign;
}

string Airline::getCountry(){
    return Country;
}