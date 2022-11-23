#include "../include/Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using sc::Graph;

using namespace std::chrono;

set<int> edgeGreedyVC(Graph<int>* G) {

  set<int> C;

  // For each vertex in G.
  for (auto vertex = G->begin(); vertex != G->end(); ++vertex) {
    // For each edge of "vertex" in G.
    for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next) {

      // If the edge is uncovered.
      if (!edge->isCovered) {

        // Add the endpoint of the edge (the vertex) with the higher degree into C.
        if (G->vertexDegree((*vertex)->data) >= G->vertexDegree(edge->data))
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
      G->updateLossNeighbors(*vertex, 1, C);
      vertex = C.erase(vertex);
    } else
      vertex++;
  }
  return C;
}

set<int> fastVC(Graph<int>* G, set<int> C, int iterations) {

  set<int> C_;

  while (iterations > 0) {

    // For each vertex in G.
    for (auto vertex = G->begin(); vertex != G->end(); ++vertex) {
      if (C.find((*vertex)->data) == C.end()) { // If the vertex is not in the cover.
        G->updateAge((*vertex)->data, 1);
      }
    }

    //cout << "ITERATION: " << iterations << endl;

    //cout << G->toString();
    //cout << "\n\n";

    // If C covers all edges of G.
    if (G->isVertexCover()) { // If it covers all edges, them the gain of all vertex is 0.
      //cout << "===== IS VERTEX COVER =====\n\n" << endl;
      C_ = C;
      auto minLossVertex = G->getMinimumLossVertex(C);
      C.erase((*minLossVertex)->data);

      // Uncover all edges that don't have a vertex covering it.
      for (auto edge = (*minLossVertex)->next; edge != nullptr; edge = edge->next) {
        if (C.find(edge->data) == C.end()) {
          G->uncoverEdge(make_pair((*minLossVertex)->data, edge->data));
        }
      }
      //cout << "R: " << (*minLossVertex)->data << endl;
      // Updates the loss and the gain. The gain becomes the loss and the loss is going to 0.
      G->updateGain((*minLossVertex)->data, (*minLossVertex)->loss);
      G->updateGainNeighbors((*minLossVertex)->data, 1, C);
      G->updateLossNeighbors((*minLossVertex)->data, 1, C);
      G->updateLoss((*minLossVertex)->data, -(*minLossVertex)->loss); // Loss goes to 0.

      G->updateAge((*minLossVertex)->data, -(*minLossVertex)->age);
      continue;
    }

    // Choose a vertex to remove and remove it.
    auto removeVertex = G->getRandomMinimumLossVertex(C);
    C.erase((*removeVertex)->data);

    // Uncover all edges of the removed vertex.
    for (auto edge = (*removeVertex)->next; edge != nullptr; edge = edge->next) {
      if (C.find(edge->data) == C.end()) {
        G->uncoverEdge(make_pair((*removeVertex)->data, edge->data));
      }
    }

    // Updates the loss and the gain. The gain becomes the loss and the loss is going to 0.
    G->updateGain((*removeVertex)->data, (*removeVertex)->loss);
    G->updateGainNeighbors((*removeVertex)->data, 1, C);
    G->updateLoss((*removeVertex)->data, -(*removeVertex)->loss); // Loss goes to 0.
    G->updateLossNeighbors((*removeVertex)->data, 1, C);
    //cout << "R: " << (*removeVertex)->data << endl;

    G->updateAge((*removeVertex)->data, -(*removeVertex)->age);

    int firstVertexValue = 0;
    int secondVertexValue = 0;
    auto randomUncoveredEdge = G->getRandomUncoveredEdge(&firstVertexValue, &secondVertexValue); // The first uncovered edge it finds.

    //  Breaks ties in favor of the older one.
    auto greaterGainVertex = G->greaterGainEndpoint(randomUncoveredEdge.first, randomUncoveredEdge.second); 

    C.insert((*greaterGainVertex)->data);

    // Updates the loss and the gain. The gain becomes the loss and the loss is going to 0.
    G->updateLoss((*greaterGainVertex)->data, (*greaterGainVertex)->gain);
    G->updateGainNeighbors((*greaterGainVertex)->data, -1, C);
    G->updateGain((*greaterGainVertex)->data, -(*greaterGainVertex)->gain); // Gain goes to 0.
    G->updateLossNeighbors((*greaterGainVertex)->data, -1, C); // Loss goes to 0.
    //cout << "I: " << (*greaterGainVertex)->data << endl;

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
  srand (time(NULL));

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

    auto startEdgeGreedyVC = high_resolution_clock::now();

    set<int> C = edgeGreedyVC(G);

    auto stopEdgeGreedyVC = high_resolution_clock::now();

    auto durationEdgeGreedyVC = duration_cast<milliseconds>(stopEdgeGreedyVC - startEdgeGreedyVC);

    cout << "\n\n\t=== EDGE_GREEDY_VC RESULTS ===\n\n";
    cout << "COVER SIZE: " << C.size() << endl;
    cout << "TIME: " << durationEdgeGreedyVC.count() << " milliseconds" << endl;
    // cout << "DATA\t" << "LOSS\t" << "DEGREE\t" << endl;
    // for (auto vertex : C)
    //   cout << vertex << "\t" << G->vertexLoss(vertex) << "\t" << G->vertexDegree(vertex) << endl;

    auto startFastVC = high_resolution_clock::now();

    C = fastVC(G, C, 50);

    auto stopFastVC = high_resolution_clock::now();

    auto durationFastVC = duration_cast<milliseconds>(stopFastVC - startFastVC);

    cout << "\n\n\t=== FAST_VC RESULTS ===\n\n";
    cout << "COVER SIZE: " << C.size() << endl;
    cout << "TIME: " << durationFastVC.count() << " milliseconds" << endl;
    // cout << "DATA\t" << "LOSS\t" << "GAIN\t" << "AGE\t" << "DEGREE\t" << endl;
    // for (auto vertex : C)
    //   cout << vertex << "\t" << G->vertexLoss(vertex) << "\t" << G->vertexGain(vertex) << "\t" << G->vertexAge(vertex) << "\t" << G->vertexDegree(vertex) << endl;

    delete G;

    return 0;
  }
}
