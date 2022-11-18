#include "../include/Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>

using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::make_pair;
using sc::Graph;

set<int> edgeGreedyVC ( Graph<int> *G )
{

  set<int> C;

  // For each edge in G.
  for (auto vertex = G->begin(); vertex != G->end(); ++vertex)
    {
      for (auto vertexNext = (*vertex)->next; vertexNext != nullptr; vertexNext = vertexNext->next)
        {

          // If the edge in uncovered.
          if ( ! vertexNext->isCovered )
            {

              // Add the endpoint of the edge (vertex) with the higher degree into C.
              if ( G->vertexDegree ( (*vertex)->data ) > G->vertexDegree ( vertexNext->data ) )
                C.insert ( (*vertex)->data );

              else
                C.insert ( vertexNext->data );

              G->coverEdge ( make_pair ( (*vertex)->data, vertexNext->data ));
            }
        }
    }

  // For each edge in G.
  for (auto vertex = G->begin(); vertex != G->end(); ++vertex)
    {
      for (auto vertexNext = (*vertex)->next; vertexNext != nullptr; vertexNext = vertexNext->next)
        {
          if ( ! vertexNext->alreadySeen )
            {

              // If only one vertex of the edge belongs to C.
              if ( C.find ( ( *vertex )->data ) != C.end() && C.find ( vertexNext->data ) == C.end() )
                G->updateLoss ( ( *vertex )->data );

              else if ( C.find ( ( *vertex )->data ) == C.end() && C.find ( vertexNext->data ) != C.end() )
                G->updateLoss ( vertexNext->data );

              // To avoid counting the same edge two times. And avoid a vertex to update loss more than one time.
              G->seeEdge ( make_pair ( ( *vertex )->data, vertexNext->data ) );
            }

        }
    }

  // For each edge in G.
  auto vertex = C.begin();
  while ( vertex != C.end() )
    {
      if ( G->vertexLoss ( *vertex ) == 0 )
        {
          G->updateLossNeighbors ( *vertex );
          vertex = C.erase ( vertex );
        }
      else
        vertex++;
    }
  return C;
}

//set<int> fastVC ( Graph<int> *G, set<int> C, std::chrono::milliseconds cutoffTime )
//{
//  set<int> C_;
//  std::chrono::milliseconds elapsedTime{0};
//  std::chrono::steady_clock::time_point end;
//
//  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//  while ( elapsedTime < cutoffTime )
//    {
//      // If C covers all edges of G.
//      if(G->isVertexCover(C))
//        {
//          C_ = C;
//          minLossVertex = G->getMinimumLossVertex(C);
//          C.erase(minLossVertex);
//        }
//
//      auto removeVertex = G->chooseRemoveVertex(C);
//      C.erase(removeVertex);
//      G->updateLossNeighbors( removeVertex );
//      G->updateGainNeighbors( removeVertex );
//
//      auto randomUncoveredEdge = G->getRandomUncoveredEdge(C);
//      auto vertex = G->greaterGainEndpoint(randomUncoveredEdge); // TODO: Breaks ties in favor of the older one. How to implement?
//      C.add(vertex);
//      G->updateLossNeighbors( vertex );
//      G->updateGainNeighbors( vertex );
//
//
//      end = std::chrono::steady_clock::now();
//      //elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
//    }
//  return C_;
//}

int main ( int argc, char* argv[] )
{
  if ( argc < 2 )
    {
      cout << "Error: Test case file not informed!" << endl;
      return 1;
    }

  std::ifstream infile ( argv[1] );

  if ( !infile )
    {
      cout << "Error: Could not open file '" << argv[1] << "' or it doesn't exist!" << endl;
      return 2;
    }

  else
    {

      //Graph<int> G;
      Graph<int> *G = new Graph<int>;

      std::string line;
      int a, b;
      char c;

      // Reads the file.
      while ( std::getline ( infile, line ) )
        {

          std::istringstream iss ( line );

          if ( !line.empty() )
            {
              // TODO: see if that works
              //iss >> a >> b;
              iss >> a >> c >> b;
              // Populates the graph.
              G->addEdge ( make_pair ( a, b ) );
            }
        }

      cout << "GRAPH SIZE: " << G->size() << endl;

      set<int> C = edgeGreedyVC ( G );

      cout << "\n\n\t=== EDGE_GREEDY_VC RESULTS ===\n\n";
      cout << "COVER SIZE: " << C.size() << endl;
      cout << "DATA\t" << "LOSS\t" << "DEGREE\t" << endl;

      for (  auto vertex : C )
          cout << vertex << "\t" << G->vertexLoss ( vertex ) << "\t" << G->vertexDegree( vertex ) << endl;

      delete G;

      return 0;
    }
}
