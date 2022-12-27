#include "airport.h"

using namespace std;

Airport::Airport(string Code, string Name, string City, string Country, float Latitude, float Longitude){
    this->Code = Code;
    this->Name = Name;
    this->City = City;
    this->Country = Country;
    this->Latitude = Latitude;
    this->Longitude = Longitude;
}

void Airport::setCode(string s){
    Code = s;
}

void Airport::setName(string s){
    Name = s;
}

void Airport::setCity(string s){
    City = s;
}

void Airport::setCountry(string s){
    Country = s;
}

void Airport::setLatitude(float f){
    Latitude = f;
}

void Airport::setLongitude(float f){
    Longitude = f;
}

string Airport::getCode() const {
    return Code;
}

string Airport::getName() const {
    return Name;
}

string Airport::getCity() const {
    return City;
}

string Airport::getCountry() const {
    return Country;
}

float Airport::getLatitude() const{
    return Latitude;
}

float Airport::getLongitude() const{
    return Longitude;
}