#include "flight.h"

using namespace std;

Flight::Flight(){
    Source = "";
    Target = "";
    Airline = "";
}

Flight::Flight(string Source, string Target, string Airline){
    this->Source = Source;
    this->Target = Target;
    this->Airline = Airline;
}

void Flight::setSource(string s){
    Source = s;
}

void Flight::setTarget(string s){
    Target = s;
}

void Flight::setAirline(string s){
    Airline = s;
}

string Flight::getSource() const{
    return Source;
}

string Flight::getTarget() const{
    return Target;
}

string Flight::getAirline() const{
    return Airline;
}