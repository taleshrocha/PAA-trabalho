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
#include <stdlib.h>

using std::set;
using std::string;
using std::copy;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;
using std::pair;
using std::make_pair;

namespace sc {

template < typename T >
class RCPSP {

 public:

  struct Edge {
    T data;
    Edge* next;

    Edge(T d = T{}, Edge* n = nullptr)
      : data{ d },
        next{ n }
    { /* empty */ }
  };

  struct Vertex {
    T data;
    int inDegree;
    int duration;
    int resourcesRequired[4] = {};
    Edge* next;

    Vertex(T d = T{}, Edge* edge = nullptr, int inDegree = 0, int dur = 0)
      : data{ d },
        inDegree{ inDegree },
        next{ edge },
        duration{ dur }
    { /* empty */ }
  };

 private:

  vector<Vertex*> adjacencyList;

  using iterator = typename vector<sc::RCPSP<T>::Vertex*>::iterator;

 public:

  RCPSP() { /* empty */ }

  ~RCPSP() {
    for (auto vertex : adjacencyList) {
      //cout << "VERTEX: " << vertex->data << endl;
      removeAllEdges(vertex->next);
      //cout << "DELETED VERTEX: " << vertex->data << endl;
      delete vertex;
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

  int size(void) const {
    return adjacencyList.size();
  }

  int vertexInDegree(T value) {
    return (*findVertex(value))->inDegree;
  }

  void addEdge(std::pair<T, T> values) {
    Edge* n = new Edge(values.second);

    auto temp = findVertex(values.first);
    if (temp != end()) {
      if ((*temp)->next != nullptr) {
        auto aux = (*temp)->next;
        while (aux->next != nullptr)
          aux = aux->next;
        aux->next = n;
      } else
        (*temp)->next = n;
    } else
      adjacencyList.push_back(new Vertex(values.first, n, 0));

    auto temp2 = findVertex(values.second);
    if (temp2 != end())
      (*temp2)->inDegree++;
    else
      adjacencyList.push_back(new Vertex(values.second, nullptr, 1));
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

  void removeAllEdges(Edge* edge) {
    if (edge != nullptr) {
      if (edge->next != nullptr) {
        removeAllEdges(edge->next);
      }
      //cout << "DELETED EDGE: " << edge->data << endl;
      delete edge;
    }
  }

  void setDuration(T value, int duration) { (*findVertex(value))->duration = duration; }

  void setResources(T value, vector<int> dur) { (*findVertex(value))->resourcesRequired = dur; }

  int totalDuration() {
    int totalDuration = 0;
    for (auto vertex = this->begin(); vertex != this->end(); ++vertex) 
        totalDuration += (*vertex)->duration;
    return totalDuration;
  }

  vector<T> availableTasks(){
    vector<T> aux;
    for (auto vertex = this->begin(); vertex != this->end(); ++vertex) {
      if ((*vertex)->inDegree == 0) 
        aux.push_back((*vertex)->data);
    }
    return aux;
  }

  bool isTaskAvailable(T value, vector<int> resources) {
    auto aux = findVertex(value);
    for(int i = 0; i < 4; i++) {
      if((*aux)->resourcesRequired[i] > resources[i])
        return false;
    }
    return true;
  }

  void taskCompleted(T value, vector<int> & availableTasks, vector<int> & inDegrees){
    auto aux = findVertex(value);
    for (auto edge = (*aux)->next; edge != nullptr; edge = edge->next) {
      // auto temp = findVertex(edge->data);
      // (*temp)->inDegree -= 1;
      inDegrees[edge->data - 1]--;
      if (inDegrees[edge->data - 1] == 0)
        availableTasks.push_back(edge->data);
    }
  }

  vector<int> getDurations() {
    vector<int> durations(adjacencyList.size(), 0);

    for (auto vertex = this->begin(); vertex != this->end(); ++vertex) {
      durations[(*vertex)->data - 1] = (*vertex)->duration;
    }

    return durations;
  }

vector<int> getInDegrees() {
  vector<int> inDegrees(adjacencyList.size(), 0);

  for (auto vertex = this->begin(); vertex != this->end(); ++vertex) {
    inDegrees[(*vertex)->data - 1] = (*vertex)->inDegree;
  }

  return inDegrees;
}

  string toString() {
    stringstream ss;
    // For each vertex.
    for (auto vertex = this->begin(); vertex != this->end(); ++vertex) {
      ss << 
        "VERT: " << (*vertex)->data << "\t" <<  
        "IN_DEGR: " << (*vertex)->inDegree << "\t" <<
        "DURATION: " << (*vertex)->duration << "\t" << "RESOURCES: ";
      for (int i = 0; i < 4; i++)
        ss << (*vertex)->resourcesRequired[i] << "  ";
      ss << endl;
      // For each edge of "vertex".
      for (auto edge = (*vertex)->next; edge != nullptr; edge = edge->next)
        ss << "\t" << "EDGE: " << edge->data << endl;
      ss << endl;
    }

    return ss.str();
  }
};
}
#endif
