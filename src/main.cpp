#include "../include/Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::vector;


std::set<int> edgeGreedyVC ( sc::Graph<int> G ) {
  std::set<int> C;

  auto it = G.begin();
  while ( it != G.end() ) {
    auto temp = (*it)->next;
    while( temp != nullptr ) {
      if ( !(*temp).isCovered ) {
        if ( G.vertexDegree((*it)->data) > G.vertexDegree((*temp).data) )
          C.insert( (*it)->data );
        else
          C.insert( (*temp).data );
        G.coverEdge( std::make_pair( (*it)->data, (*temp).data ) );
      }
      temp = temp->next;
    }
    it++;
  }
  
  auto itt = G.begin();
  while ( itt != G.end() ) {
    auto temp = (*itt)->next;
    while( temp != nullptr ) {
      if ( !(*temp).alreadySeen ) {
        if ( C.find( (*itt)->data ) != C.end() && C.find( (*temp).data ) == C.end() )
          G.updateLoss( (*itt)->data );
        else if ( C.find( (*itt)->data ) == C.end() && C.find( (*temp).data ) != C.end() )
          G.updateLoss( (*temp).data );
        G.seeEdge( std::make_pair( (*itt)->data, (*temp).data ) );
      }
      temp = temp->next;
    }
    itt++;
  }

  auto itr2 = C.begin();
  while ( itr2 != C.end() ) {
    cout << *itr2 << " " << G.vertexLoss(*itr2) << endl;
      itr2++;
  }
  
  auto itr = C.begin();
  while ( itr != C.end() ) {
    cout << "fora " << *itr << endl;
    if ( G.vertexLoss( *itr ) == 0 ) {
      cout <<  "dentro " << *itr << endl;
      G.updateLossNeighbors( *itr );
      //C.erase(itr);
    }
      itr++;
  }
  cout << "aqui3" << endl;
  return C;
}

int main ( int argc, char* argv[] )
{
  if (argc < 2) {
    cout << "Error: Test case file not informed!" << endl;
    return 1;
  }

  std::ifstream infile(argv[1]);

  if ( !infile ) {
    cout << "Error: Could not open file '" << argv[1] << "' or it doesn't exist!" << endl;
    return 1;
  } else {

    sc::Graph<int> G;

    std::string line;
    int a, b;
    char c;

    while ( std::getline(infile, line) ) {

      std::istringstream iss(line);

      if (!line.empty()) {
        iss >> a >> c >> b;
        G.addEdge(std::make_pair(a, b));
      }
    }
    std::cout << G.size() << endl;
    std::set<int> C = edgeGreedyVC( G );
    std::cout << C.size() << endl;

    auto itr = C.begin();
    while ( itr != C.end() ) {
      cout << *itr << " " << G.vertexLoss(*itr) << endl;
        itr++;
    }
    return 0;
  }
}
