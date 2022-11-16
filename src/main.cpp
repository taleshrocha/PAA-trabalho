#include "../include/Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


int main ( int argc, char* argv[] )
{
  sc::Graph<int> G;

  std::pair<int,int> teste = std::make_pair(95,82);

  G.addEdge(teste);
  G.addEdge(std::make_pair(95,32));

  std::cout << G.size() << endl;

  //int i =0;

  // if(G.findVertex(teste.first) != G.end()) {
  //   auto it = G.findVertex(teste.first);
  //     cout << i << endl;
  //     cout << (*it)->data << endl;
  //     cout << (*it)->degree << endl;
  //     i++;
  //     auto aux = (*it)->next;
  //     while( aux != nullptr ) {
  //         cout << i << endl;
  //         cout << (*aux).data << endl;
  //         i++;
  //         aux = aux->next;
  //     }
  // } else
  //   cout << "não foi dessa vez" << endl;

  auto L = G.getAdjacencyList();

  for (auto i = 0; i<L.size(); i++){
    cout << L[i]->data << " " << L[i]->degree << endl;
    auto aux = L[i]->next;
    while( aux != nullptr ) {
        cout << (*aux).data << endl;
        aux = aux->next;
    }
    cout << "(*aux).data" << endl;
  }

  // if (argc < 2) {
  //   cout << "You must give the test case file!" << endl;
  //   return 1;
  // }

  // std::ifstream infile(argv[1]);
  // std::string line;

  // int a, b;
  // char c;
  // // TODO create an graph G using the data structure.

  // while ( std::getline(infile, line) ) {

  //   std::istringstream iss(line);

  //   if (!line.empty()) {
  //     iss >> a >> c >> b;
  //     // TODO pass the values to the data structure.
  //     cout << a << " " << b << endl;
  //   }
  // }

  // // EdgeGreedyVC

  // /*
  // vector<Vertex> C;

  // for (Edge e : G.edges()) {
  //   if (!isCovered(e, C)) {
  //     // TODO adicione o vértice de e com o maior grau em C.
  //   }
  // }

  // for (Edge e : G.edges()) {
  //   // se apenas uma ponta de e pertence a C.
  //   if (isEndPointIn(e, C)) {
  //     Vertex endPoint = getEndPoint(e, C);
  //     endPoint.loss += 1;
  //   }
  // }

  // for (Vertex v : C) {

  //   if (v.loss == 0) {
  //     // C := C \ {v}
  //     remove(C.begin(), C.end(), v);

  //     // TODO atualize loss dos vértices em Neighboors(v);
  //   }
  // }
  // */

  return 0;
}
