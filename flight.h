#ifndef PROJETOAED2_FLIGHT_H
#define PROJETOAED2_FLIGHT_H

#include <string>
#include <system_error>

using namespace std;

class Flight : public error_code {
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