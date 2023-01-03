#include <iostream>
#include "Manager.h"
using namespace std;

int main()
{
    cout << "Hello World!" <<endl;
    Manager manager;
    cout << "Hello, World!" <<endl;
    manager.loadFlights();
    manager.loadAirlines();
    manager.loadAirports();
    manager.loadCities();
    cout << manager.countFlightsFromAirport("CDG") << endl;
    cout << manager.countUniqueAirlinesFromAirport("CDG") << endl;
    cout << manager.countUniqueDestinationsFromAirport("CDG") << endl;
    cout << manager.countUniqueCountriesFromAirport("CDG") << endl;
    cout << manager.countReachableAirports("CDG", 3) << endl;
    cout << manager.countReachableCities("CDG", 3) << endl;
    cout << manager.countReachableCountries("CDG", 3) << endl;
    return 0;
}