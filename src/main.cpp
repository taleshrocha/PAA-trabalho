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
using std::pair;
using std::make_pair;
using std::string;
using sc::Graph;

set<int> edgeGreedyVC(Graph<int>* G) {

  set<int> C;

  // For each vertex in G.
  for (auto vertex = G->begin(); vertex != G->end(); ++vertex) {
    // For each edge of "vertex" in G.
    for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next) {

      // If the edge is uncovered.
      if (!edge->isCovered) {

        // Add the endpoint of the edge (the vertex) with the higher degree into C.
        if (G->vertexDegree((*vertex)->data) > G->vertexDegree(edge->data))
          C.insert((*vertex)->data);

        else
          C.insert(edge->data);

        G->coverEdge(make_pair((*vertex)->data, edge->data));
      }
    }
  }

  // For each vertex in G.
  for (auto vertex = G->begin(); vertex != G->end(); ++vertex) {
    // For each edge of "vertex" in G.
    for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next) {

      if (!edge->alreadySeen) {

        // If only one vertex of the edge belongs to C.
        if (C.find((*vertex)->data) != C.end() && C.find(edge->data) == C.end())
          G->updateLoss((*vertex)->data, 1);

        else if (C.find((*vertex)->data) == C.end() && C.find(edge->data) != C.end())
          G->updateLoss(edge->data, 1);

        // To avoid counting the same edge two times. And avoid a vertex to update loss more than one time.
        G->seeEdge(make_pair((*vertex)->data, edge->data));
      }
    }
  }

  // For each vertex in G.
  auto vertex = C.begin();
  while (vertex != C.end()) {
    if (G->vertexLoss(*vertex) == 0) {
      G->updateLossNeighbors(*vertex, 1);
      vertex = C.erase(vertex);
    } else
      vertex++;
  }
  return C;
}

set<int> fastVC(Graph<int>* G, set<int> C, int iterations) {

  set<int> C_;

  while (iterations > 0) {
    cout << "ITERATION: " << iterations << endl;

    cout << G->toString();
    cout << "\n\n";

    // If C covers all edges of G.
    if (G->isVertexCover()) { // If it covers all edges, them the gain of all vertex is 0.
      cout << "===== IS VERTEX COVER =====\n\n" << endl;
      C_ = C;
      auto minLossVertex = G->getMinimumLossVertex(C);
      C.erase((*minLossVertex)->data);

      // Uncover all edges that don't have a vertex covering it.
      for (auto edge = (*minLossVertex)->next; edge != nullptr; edge = edge->next) {
        if (C.find(edge->data) == C.end()) {
          G->uncoverEdge(make_pair((*minLossVertex)->data, edge->data));
        }
      }

      // Updates the loss and the gain. The gain becomes the loss and the loss is going to 0.
      G->updateGain((*minLossVertex)->data, (*minLossVertex)->loss);
      G->updateGainNeighbors((*minLossVertex)->data, 1);
      G->updateLossNeighbors((*minLossVertex)->data, 1);
      G->updateLoss((*minLossVertex)->data, -(*minLossVertex)->loss); // Loss goes to 0.
    }

    // Choose a vertex to remove and remove it.
    auto removeVertex = G->getMinimumLossVertex(C);
    C.erase((*removeVertex)->data);

    // Uncover all edges of the removed vertex.
    for (auto edge = (*removeVertex)->next; edge != nullptr; edge = edge->next) {
      if (C.find(edge->data) == C.end()) {
        G->uncoverEdge(make_pair((*removeVertex)->data, edge->data));
      }
    }

    // Updates the loss and the gain. The gain becomes the loss and the loss is going to 0.
    G->updateGain((*removeVertex)->data, (*removeVertex)->loss);
    G->updateGainNeighbors((*removeVertex)->data, 1);
    G->updateLoss((*removeVertex)->data, -(*removeVertex)->loss); // Loss goes to 0.

    int vertexValue = 0;
    auto randomUncoveredEdge = G->getRandomUncoveredEdge(&vertexValue); // The first uncovered edge it finds.

    // TODO: Breaks ties in favor of the older one. How to implement?
    auto greaterGainVertex = G->greaterGainEndpoint(vertexValue, randomUncoveredEdge); 

    C.insert((*greaterGainVertex)->data);

    // Updates the loss and the gain. The gain becomes the loss and the loss is going to 0.
    G->updateLoss((*greaterGainVertex)->data, (*greaterGainVertex)->gain);
    G->updateGainNeighbors((*greaterGainVertex)->data, -1);
    G->updateGain((*greaterGainVertex)->data, -(*greaterGainVertex)->gain); // Gain goes to 0.

    // IMPORTANT: Don't change the order! This becomes after the gain and loss update.
    // Cover all edges of this vertex.
    for (auto edge = (*greaterGainVertex)->next; edge != nullptr; edge = edge->next)
      G->coverEdge(make_pair((*greaterGainVertex)->data, edge->data));

    iterations--;
  }

  return C_;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Error: Test case file not informed!" << endl;
    return 1;
  }

  std::ifstream infile(argv[1]);

  if (!infile) {
    cout << "Error: Could not open file '" << argv[1] << "' or it doesn't exist!" << endl;
    return 2;
  }

  else {

    //Graph<int> G;
    Graph<int>* G = new Graph<int>;

    std::string line;
    int a, b;
    char c;

    // Reads the file.
    while (std::getline(infile, line)) {

      std::istringstream iss(line);

      if (!line.empty()) {
        // TODO: see if that works
        //iss >> a >> b;
        iss >> a >> c >> b;
        // Populates the graph.
        G->addEdge(make_pair(a, b));
      }
    }

    cout << "GRAPH SIZE: " << G->size() << endl;

    set<int> C = edgeGreedyVC(G);

    cout << "\n\n\t=== EDGE_GREEDY_VC RESULTS ===\n\n";
    cout << "COVER SIZE: " << C.size() << endl;
    cout << "DATA\t" << "LOSS\t" << "DEGREE\t" << endl;
    for (auto vertex : C)
      cout << vertex << "\t" << G->vertexLoss(vertex) << "\t" << G->vertexDegree(vertex) << endl;

    C = fastVC(G, C, 100);

    cout << "\n\n\t=== FAST_VC RESULTS ===\n\n";
    cout << "COVER SIZE: " << C.size() << endl;
    cout << "DATA\t" << "LOSS\t" << "GAIN\t" << "DEGREE\t" << endl;
    for (auto vertex : C)
      cout << vertex << "\t" << G->vertexLoss(vertex) << "\t" << G->vertexGain(vertex) << "\t" << G->vertexDegree(vertex) << endl;

    delete G;

    return 0;
  }
}
