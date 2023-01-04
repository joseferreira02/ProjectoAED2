#ifndef PROJETOAED2_FLIGHT_H
#define PROJETOAED2_FLIGHT_H

#include <string>
using namespace std;

class Flight{
private:
    string Source;
    string Target;
    string Airline;
public:
    Flight();
    Flight(string Source, string Target, string Airline);
    void setSource(string s);
    void setTarget(string s);
    void setAirline(string s);
    string getSource() const;
    string getTarget() const;
    string getAirline() const;
};

#endif