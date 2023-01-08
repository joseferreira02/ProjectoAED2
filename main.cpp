#include <iostream>
#include <string>
#include "Manager.h"
#include "Graph.h"


using namespace std;

int main(){
    Manager manager = Manager();
    Graph graph = Graph(manager);
    int option;
    string country;
    string city;
    string airline;
    int option2;
    int latitude;
    int longitude;
    int radius;
    int k;
    int maxFlights;
    string startingAirport;
    string finalAirport;
    string City;
    do{
        cout << "==========================================================================================================================" << endl;
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
        cout << "14 - Network statistics" << endl;
        cout << "15 - Country statistics" << endl;
        cout << "16 - Airline statistics" << endl;
        cout << "17 - Airport statistics" << endl;
        cout << "0 - Quit" << endl;
        cout << "==========================================================================================================================" << endl;

        cin >> option;

        switch(option){
            case 0:
                break;

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
                cout << "Enter the airport you would like to begin your flight: ";
                cin >> startingAirport;
                
                cout << "Enter the latitude: ";
                cin >> latitude;
                
                cout << "Enter the longitude: ";
                cin >> longitude;
                
                cout << "Enter the desired radius: ";
                cin >> radius;
                
                graph.spCoordinate(startingAirport, latitude, longitude, radius);
                break;

            case 4:
                cout << "Enter the city you would like to begin your flight: ";
                cin >> city;
                
                cout << "Enter the airport you would like to travel to: ";
                cin >> finalAirport;
                
                graph.citySpAirport(city, finalAirport);
                break;

            case 5:
                cout << "Enter the airport you would like to travel to: ";
                cin >> finalAirport;
                
                cout << "Enter your beginning latitude: ";
                cin >> latitude;
                
                cout << "Enter your beginning longitude: ";
                cin >> longitude;
                
                cout << "Enter the radius: ";
                cin >> radius;
                
                graph.coordinateSpAirport(finalAirport, latitude, longitude, radius);
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
            case 14:
                cout << "1 - Number of airports" << endl;
                cout << "2 - Number of flights" << endl;
                cout << "3 - Number of airlines" << endl;

                cin >> option2;

                if (option2 == 1){
                    cout << endl;
                    cout << "The number of airports is : " << manager.networkAirports();
                    cout << endl;
                }
                else if (option2 == 2){
                    cout << endl;
                    cout << "The number of flights is : " << manager.networkFlights();
                    cout << endl;
                }
                else if (option2 == 3){
                    cout << endl;
                    cout << "The number of airlines is : " << manager.networkAirlines();
                    cout << endl;
                }
                else{
                    cout << "Invalid input, please try again" << endl;
                }
                break;
            case 15:
                cout << "1 - Number of airports" << endl;
                cout << "2 - Number of flights" << endl;
                cout << "3 - Number of airlines" << endl;

                cin >> option2;

                if (option2 == 1){
                    cout << "Enter the name of the country: " << endl;
                    cin >> country;
                    cout << endl;
                    cout << "The number of airports in this country is : " << manager.countryAirports(country);
                    cout << endl;
                }
                else if (option2 == 2){
                    cout << "Enter the name of the country: " << endl;
                    cin >> country;
                    cout << endl;
                    cout << "The number of flights in this country is : " << manager.countryFlights(country);
                    cout << endl;
                }
                else if (option2 == 3){
                    cout << "Enter the name of the country: " << endl;
                    cin >> country;
                    cout << endl;
                    cout << "The number of airlines in this country is : " << manager.countryAirlines(country);
                    cout << endl;
                }
                else{
                    cout << "Invalid input, please try again" << endl;
                }
                break;
            case 16:
                cout << "1 - Number of airports" << endl;
                cout << "2 - Number of flights" << endl;

                cin >> option2;

                if (option2 == 1){
                    cout << "Enter the name of the airline" << endl;
                    cin >> airline;
                    cout << endl;
                    cout << "The number of airports of this airline is : " << manager.airportsUsingAirline(airline);
                    cout << endl;
                }
                else if (option2 == 2){
                    cout << "Enter the name of the airline" << endl;
                    cin >> airline;
                    cout << endl;
                    cout << "The number of flights of this airline is : " << manager.flightsUsingAirline(airline);
                    cout << endl;
                }
                else{
                    cout << "Invalid input, please try again" << endl;
                }
                break;

            case 17:
                cout << "1 - Top airports with the most flights" << endl;
                cout << "2 - Top airports with the most airlines" << endl;

                cin >> option2;

                if (option2 == 1){
                    cout << "Enter the number of top airports you would like to view : " << endl;
                    cin >> k;
                    cout << endl;
                    manager.topKAirportsWithMostFlights(k);
                }
                else if (option2 == 2){
                    cout << "Enter the number of top airports you would like to view : " << endl;
                    cin >> k;
                    cout << endl;
                    manager.topKAirportsWithMostAirlines(k);
                }
                else{
                    cout << "Invalid input, please try again" << endl;
                }
                break;
            default:
                cout << "Please enter a valid number" << endl;
        }
    } while (option != 0);
}
