#include <iostream>
#include <string>
#include "Manager.h"
#include "Graph.h"


using namespace std;

int main(){
    Manager manager = Manager();
    Graph graph = Graph(manager);
    int option;
    int maxFlights;
    string startingAirport;
    string finalAirport;
    string City;
    do{
        cout << "==============================================================" << endl;
        cout << "1 - Shortest path between two airports" << endl;
        cout << "2 - Shortest path from an airport to a city" << endl;
        cout << "3 - Shortest path from an airport to certain coordenates" << endl;
        cout << "4 - Shortest path from a city to an airport" << endl;
        cout << "5 - Shortest path from certain coordenates to an airport" << endl;
        cout << "6 - Show all the possible flights from a certain airport" << endl;
        cout << "7 - Show all the possible airlines from a certain airport" << endl;
        cout << "8 - Show all the possible destinations from a certain airport" << endl;
        cout << "9 - Show all the possible countries you can fly to from a certain airport" << endl;
        cout << "10 - Check how many airports you can reach with a maximum number of flights and starting at a certain airport" << endl;
        cout << "11 - Check how many cities you can reach with a maximum number of flights and starting at a certain airport" << endl;
        cout << "12 - Check how many countries you can reach with a maximum number of flights and starting at a certain airport" << endl;
        cout << "13 - Information about an airport" << endl;
        cout << "0 - Quit" << endl;
        cout << "==============================================================" << endl;

        cin >> option;

        switch(option){
            case 1:
                cout << "Enter the airport you would like to begin your flight: ";
                cin >> startingAirport;

                cout << "Enter the airport you would like to end your flight: ";
                cin >> finalAirport;

                graph.spAirport(startingAirport, finalAirport);

                break;

            case 2:

                cout << "Enter the airport you would like to begin your flight: ";
                cin >> startingAirport;

                cout << "Enter the city you would like to go to: ";
                cin >> City;

                graph.spCity(startingAirport, City);

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

            case 6:
                cout << "Enter the airport: ";
                cin >> startingAirport;

                manager.countFlightsFromAirport(startingAirport);

                break;
            case 7:
                cout << "Enter the airport: ";
                cin >> startingAirport;

                manager.countUniqueAirlinesFromAirport(startingAirport);

                break;
            case 8:
                cout << "Enter the airport: ";
                cin >> startingAirport;

                manager.countUniqueDestinationsFromAirport(startingAirport);

                break;
            case 9:
                cout << "Enter the airport: ";
                cin >> startingAirport;

                manager.countUniqueCountriesFromAirport(startingAirport);

                break;
            case 10:
                cout << "Enter the airport: ";
                cin >> startingAirport;

                cout << "Enter the number of flights: ";
                cin >> maxFlights;

                manager.countReachableAirports(startingAirport, maxFlights);

                break;
            case 11:
                cout << "Enter the airport: ";
                cin >> startingAirport;

                cout << "Enter the number of flights: ";
                cin >> maxFlights;

                manager.countReachableCities(startingAirport, maxFlights);

                break;
            case 12:
                cout << "Enter the airport: ";
                cin >> startingAirport;

                cout << "Enter the number of flights: ";
                cin >> maxFlights;

                manager.countReachableCountries(startingAirport, maxFlights);

                break;
            case 13:
                cout << "Enter the code of the airport: ";
                cin >> startingAirport;

                manager.showAirportInformation(startingAirport);

                break;

            default:
                cout << "Please enter a valid number" << endl;
                cout << endl;
                break;
        }
    } while (option != 0);
}