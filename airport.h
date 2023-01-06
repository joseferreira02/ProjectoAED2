#ifndef PROJETOAED2_AIRPORT_H
#define PROJETOAED2_AIRPORT_H

#include <string>
#include <unordered_set>

using namespace std;

class Airport{
private:
    string Code;
    string Name;
    string City;
    string Country;
    float Latitude;
    float Longitude;

public:
    Airport(string Code, string Name, string City, string Country, float Latitude, float Longitude);
    void setCode(string s);
    void setName(string s);
    void setCity(string s);
    void setCountry(string s);
    void setLatitude(float f);
    void setLongitude(float f);
    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
};

struct AirportHash{
    int operator()(const Airport& airport)const{

        char codeVal1 = airport.getCode()[0];
        char codeVal2= airport.getCode()[1];
        char codeVal3 = airport.getCode()[2];

        return codeVal1*31+codeVal2*32+codeVal3*33;

    }

    bool operator()(const Airport& airport1,const Airport& airport2)const{
        return (airport1.getLatitude()==airport2.getLatitude()) && (airport1.getLongitude()==airport2.getLongitude()); // se ambos partilharem a mesma coordenada sao iguais
    }
};

typedef unordered_set<Airport,AirportHash,AirportHash> AirportHashTable;

#endif
