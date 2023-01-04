#include <iostream>
#include "Manager.h"
#include "Graph.h"

int main()
{
    std::cout<<"Hello, World!"<<std::endl;
    Manager manager;
    Graph graph = Graph(manager);
    graph.tester();
    //graph tester
    return 0;
}
