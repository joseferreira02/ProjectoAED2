#include <iostream>
#include "Manager.h"
using namespace std;
#include "Graph.h"


int main()
{
    cout << "Hello World!" <<endl;
    Manager manager;
    Graph graph = Graph(manager);
    graph.tester();
    //graph tester
    return 0;
}