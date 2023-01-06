#include <iostream>
#include "Manager.h"
using namespace std;
#include "Graph.h"


//
// importante : CRIAR RESTRIÇOES PARA CASOS COMO EXISTE AEROPORTO ? EXISTE CIDADE ? EXISTE AIRLINE ? (FAZER TODAS AS RESTRIÇOES EM FUNÇOES EXPECIFICAS DENTRO DO GRAPH ||||||||||| EX : bool isCity(const string& city)) necessario para nao atirar errors estrnhos
int main()
{
    cout << "Hello World!" <<endl;
    Manager manager;
    Graph graph = Graph(manager);
    graph.spCity("JFK","2");
    //graph tester
    return 0;
}