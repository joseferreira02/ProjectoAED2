#ifndef PROJETOAED2_AIRLINE_H
#define PROJETOAED2_AIRLINE_H

#include <string>
using namespace std;

class Airline{
private:
    string Airline_Code;
    string Airline_Name;
    string Callsign;
    string Country;
public:
    Airline(string Code, string Name, string Callsign, string Country);
    void setCode(string s);
    void setName(string s);
    void setCallsign(string s);
    void setCountry(string s);
    string getCode();
    string getName();
    string getCallsign();
    string getCountry();
};

#endif
