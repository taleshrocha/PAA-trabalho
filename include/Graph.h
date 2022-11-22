#ifndef _Graph_H_
#define _Graph_H_

#include <iostream>
#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
#include <cstddef>   // std::ptrdiff_t
#include <type_traits>
#include <vector>
#include <utility>
#include <set>
#include <sstream>
#include <string>

using std::set;
using std::string;
using std::copy;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;

namespace sc {

template < typename T >
class Graph {

 public:

  struct Edge {
    T data;
    bool isCovered;
    bool alreadySeen;
    Edge* next;

    Edge(T d = T{}, Edge* n = nullptr, bool i = false, bool al = false)
      : data{ d },
        isCovered{ i },
        alreadySeen{ al },
        next{ n }
    { /* empty */ }
  };

  struct Vertex {
    T data;
    size_t degree;
    size_t loss;
    size_t gain;
    size_t age;
    Edge* next;

    Vertex(T d = T{}, Edge* edge = nullptr, size_t de = 0, size_t l = 0, size_t g = 0, size_t a = 0)
      : data{ d },
        degree{ de },
        loss{ l },
        gain{ g },
        age{ a },
        next{ edge }
    { /* empty */ }
  };

 private:

  vector<Vertex*> adjacencyList;

  using  iterator = typename vector<sc::Graph<T>::Vertex*>::iterator;

 public:

  Graph() {
    /* empty */
  }

  ~Graph() {
    for (auto vertex : adjacencyList) {
      //cout << "VERTEX: " << vertex->data << endl;
      removeAllEdges(vertex->next);
      //cout << "DELETED VERTEX: " << vertex->data << endl;
      delete vertex;
    }
  }

  void removeAllEdges(Edge* edge) {
    if (edge != nullptr) {
      if (edge->next != nullptr) {
        removeAllEdges(edge->next);
      }
      //cout << "DELETED EDGE: " << edge->data << endl;
      delete edge;
    }
  }


  iterator begin() {
    return adjacencyList.begin();
  }

  iterator end() {
    return adjacencyList.end();
  }

  bool empty(void) const {
    return adjacencyList.size() == 0;
  }

  size_t size(void) const {
    return adjacencyList.size();
  }

  void addEdge(std::pair<T, T> values) {
    addEdgeAux(values);
    addEdgeAux(std::make_pair(values.second, values.first));
  }

  iterator findVertex(T value) {
    auto it = begin();
    while (it != end()) {
      if ((*it)->data == value) {
        return it;
      }
      it++;
    }
    return it;
  }

  size_t vertexDegree(T value) {
    return (*findVertex(value))->degree;
  }

  size_t vertexLoss(T value) {
    return (*findVertex(value))->loss;
  }

  size_t vertexGain(T value) {
    return (*findVertex(value))->gain;
  }

  void updateLoss(T value, int dif) {
    (*findVertex(value))->loss = (*findVertex(value))->loss + dif;
  }

  void updateGain(T value, int dif) {
    (*findVertex(value))->gain = (*findVertex(value))->gain + dif;
  }

  void updateLossNeighbors(T value, int dif) {
    auto vertex = findVertex(value);

    // For each edge of "vertex".
    for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next) {
      if (edge->isCovered)
        updateLoss(edge->data, dif);
    }
  }

  void updateGainNeighbors(T value, int dif) {
    auto vertex = findVertex(value);

    // For each edge of "vertex".
    for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next) {
      if (!edge->isCovered)
        updateGain(edge->data, dif);
    }
  }

  void coverEdge(std::pair<T, T> values) {
    coverEdgeAux(values);
    coverEdgeAux(std::make_pair(values.second, values.first));
  }

  void uncoverEdge(std::pair<T, T> values) {
    uncoverEdgeAux(values);
    uncoverEdgeAux(std::make_pair(values.second, values.first));
  }

  void seeEdge(std::pair<T, T> values) {
    seeEdgeAux(values);
    seeEdgeAux(std::make_pair(values.second, values.first));
  }

  bool isVertexCover() {

    // For all vertex.
    for (auto vertex = this->begin(); vertex != this->end(); ++vertex) {
      if ((*vertex)->gain > 0)
        return false;
    }

    return true;
  }

  iterator getMinimumLossVertex(set<int> C) {
    if (C.empty())
      return this->end();

    iterator minLossVertex = findVertex(*(C.begin()));
    iterator vertex = findVertex(*(C.begin()));
    size_t minLoss = (*vertex)->loss;

    for (auto vertexValue : C) {
      vertex = findVertex(vertexValue);

      if ((*vertex)->loss <= minLoss) {
        minLossVertex = vertex;
      }
    }

    return minLossVertex;
  }

  Edge* getRandomUncoveredEdge(int *vertexValue) {
    // For each edge in G.
    for (auto vertex = this->begin(); vertex != this->end(); ++vertex) {
      *vertexValue = (*vertex)->data;
      for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next) {

        // If the edge is uncovered.
        if (! edge->isCovered) {
          return edge;
        }
      }
    }

    cout << "getRandomUncoveredEdge NOT FOUND" << endl;
    return (*this->begin())->next;
  }

  string toString() {
    stringstream ss;
    // For each vertex.
    for (auto vertex = this->begin(); vertex != this->end(); ++vertex) {
      ss << 
        "VERT: " << (*vertex)->data << "\t" << 
        "LOSS: " << (*vertex)->loss << "\t" << 
        "GAIN: " << (*vertex)->gain << "\t" << 
        "DEGR: " << (*vertex)->degree << endl;
      // For each edge of "vertex".
      for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next)
        ss << "\t" <<
          "EDGE: " << edge->data << "\t" << 
          "ISCV: " << edge->isCovered << "\t" << 
          "ALSE: " << edge->alreadySeen << endl;
      ss << endl;
    }

    return ss.str();
  }

  iterator greaterGainEndpoint(int vertexValue, Edge *edge) {
    auto firstVertex = findVertex(vertexValue);
    auto secondVertex = findVertex(edge->data);

    if ((*firstVertex)->gain >= (*secondVertex)->gain)
      return firstVertex;
    else
      return secondVertex;
  }

 private:

  void addEdgeAux(std::pair<T, T> values) {
    Edge* n = new Edge(values.second);

    if (findVertex(values.first) != end()) {
      auto temp = findVertex(values.first);
      (*temp)->degree++;
      auto aux = (*temp)->next;
      while (aux->next != nullptr)
        aux = aux->next;
      aux->next = n;
    } else
      adjacencyList.push_back(new Vertex(values.first, n, 1));
  }

  void coverEdgeAux(std::pair<T, T> values) {
    auto aux = (*findVertex(values.first))->next;
    while (aux != nullptr) {
      if (aux->data == values.second) {
        aux->isCovered = true;
        return;
      }
      aux = aux->next;
    }
  }

  void uncoverEdgeAux(std::pair<T, T> values) {
    auto aux = (*findVertex(values.first))->next;
    while (aux != nullptr) {
      if (aux->data == values.second) {
        aux->isCovered = false;
        return;
      }
      aux = aux->next;
    }
  }

  void seeEdgeAux(std::pair<T, T> values) {
    auto aux = (*findVertex(values.first))->next;
    while (aux != nullptr) {
      if (aux->data == values.second) {
        aux->alreadySeen = true;
        return;
      }
      aux = aux->next;
    }
  }
};
}
#endif
