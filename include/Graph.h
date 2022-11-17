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

using std::copy;
using std::vector;

namespace sc
{

template < typename T >
class Graph
{

public:

  struct Edge
  {
    T data;
    bool isCovered;
    bool alreadySeen;
    Edge* next;

    Edge ( T d = T{}, Edge* n = nullptr, bool i = false, bool al = false )
      : data{ d },
        isCovered{ i },
        alreadySeen{ al },
        next{ n }
    { /* empty */ }
  };

  struct Vertex
  {
    T data;
    size_t degree;
    size_t loss;
    Edge* next;

    Vertex ( T d = T{}, Edge* n = nullptr, size_t de = 0, size_t l = 0 )
      : data{ d },
        degree{ de },
        loss{ l },
        next{ n }
    { /* empty */ }
  };

private:

  vector<Vertex*> adjacencyList;

  using  iterator = typename vector<sc::Graph<T>::Vertex*>::iterator;

public:

  Graph()
  {
    /* empty */
  }

  ~Graph()
  {
    // clear();
    // delete m_head;
    // delete m_tail;
  }

  iterator begin()
  {
    return adjacencyList.begin();
  }

  iterator end()
  {
    return adjacencyList.end();
  }

  bool empty ( void ) const
  {
    return adjacencyList.size() == 0;
  }

  size_t size ( void ) const
  {
    return adjacencyList.size();
  }

  void addEdge ( std::pair<T,T> values )
  {
    addEdgeAux ( values );
    addEdgeAux ( std::make_pair ( values.second, values.first ) );
  }

  iterator findVertex ( T value )
  {
    auto it = begin();
    while ( it != end() )
    {
      if ( ( *it )->data == value )
      {
        return it;
      }
      it++;
    }
    return it;
  }

  size_t vertexDegree ( T value )
  {
    return ( *findVertex ( value ) )->degree;
  }

  size_t vertexLoss ( T value )
  {
    return ( *findVertex ( value ) )->loss;
  }

  void updateLoss ( T value )
  {
    ( *findVertex ( value ) )->loss++;
  }

  void updateLossNeighbors ( T value )
  {
    auto temp = ( *findVertex ( value ) )->next;
    while ( temp != nullptr )
    {
      updateLoss ( ( *temp ).data );
      temp = temp->next;
    }
  }

  void coverEdge ( std::pair<T,T> values )
  {
    coverEdgeAux ( values );
    coverEdgeAux ( std::make_pair ( values.second, values.first ) );
  }

  void seeEdge ( std::pair<T,T> values )
  {
    seeEdgeAux ( values );
    seeEdgeAux ( std::make_pair ( values.second, values.first ) );
  }

private:

  void addEdgeAux ( std::pair<T,T> values )
  {
    Edge* n = new Edge ( values.second );

    if ( findVertex ( values.first ) != end() )
    {
      auto temp = findVertex ( values.first );
      ( *temp )->degree++;
      auto aux = ( *temp )->next;
      while ( aux->next != nullptr )
        aux = aux->next;
      aux->next = n;
    }
    else
      adjacencyList.push_back ( new Vertex ( values.first, n, 1 ) );
  }

  void coverEdgeAux ( std::pair<T,T> values )
  {
    auto aux = ( *findVertex ( values.first ) )->next;
    while ( aux != nullptr )
    {
      if ( aux->data == values.second )
      {
        aux->isCovered = true;
        return;
      }
      aux = aux->next;
    }
  }

  void seeEdgeAux ( std::pair<T,T> values )
  {
    auto aux = ( *findVertex ( values.first ) )->next;
    while ( aux != nullptr )
    {
      if ( aux->data == values.second )
      {
        aux->alreadySeen = true;
        return;
      }
      aux = aux->next;
    }
  }
};
}
#endif
