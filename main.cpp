#include <iostream>
#include "Manager.h"
<<<<<<< HEAD
using namespace std;
=======
#include "Graph.h"
>>>>>>> 84e38c306013e28a585b04e13e946f9ad978cd13

int main()
{
    cout << "Hello World!" <<endl;
    Manager manager;
    Graph graph = Graph(manager);
    graph.tester();
    //graph tester
    return 0;
}