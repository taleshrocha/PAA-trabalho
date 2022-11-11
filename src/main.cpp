//#include "List.h"
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
  if (argc < 2) {
    cout << "You must give the test case file!" << endl;
    return 1;
  }

  std::ifstream infile(argv[1]);
  std::string line;

  int a, b;
  char c;
  // TODO create an graph G using the data structure.

  while ( std::getline(infile, line) ) {

    std::istringstream iss(line);

    if (!line.empty()) {
      iss >> a >> c >> b;
      // TODO pass the values to the data structure.
      cout << a << " " << b << endl;
    }
  }

  // EdgeGreedyVC

  /*
  vector<Vertex> C;

  for (Edge e : G.edges()) {
    if (!isCovered(e)) {
      // TODO adicione o vértice de e com o maior grau em C.
    }
  }

  for (Vertex v : C) {
    v.loss = 0;
  }

  for (Edge e : G.edges()) {
    // se apenas uma ponta de e pertence a C.
    if (isEndPointIn(e, C)) {
      Vertex endPoint = getEndPoint(e, C);
      endPoint.loss += 1;
    }
  }

  for (Vertex v : C) {

    if (v.loss == 0) {
      // C := C \ {v}
      remove(C.begin(), C.end(), v);

      // TODO atualize loss dos vértices em N(v);
    }
  }
  */

  return 0;
}
