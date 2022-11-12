#ifndef _Graph_H_
#define _Graph_H_

#include <iostream>  // cout, endl
using std::cout;
using std::endl;

#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
using std::copy;
#include <cstddef>   // std::ptrdiff_t
#include <type_traits>
#include <vector>

#include <utility>
#include <optional>

namespace sc {

    template < typename T >
    class Graph
    {
    private:
        struct Node
        {
            T data;
            bool isCovered;
            Node * next;

            Node( const T &d = T{} , bool i = false, Node * n = nullptr )
                : data{ d },
                  isCovered{ i },
                  next{ n }
            { /* empty */ }
        };

        std::vector<std::optional<Node>> adjacencyList;
        std::vector<size_t> loss;

    public:
        Graph()
        { 
            adjacencyList = std::vector{}
            loss = std::vector()
        }

        Graph( size_t size ) : Graph()
        { 
            adjacencyList = std::vector(size, std::optional<Node>{})
            loss = std::vector(size, 0)
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

        size_t size( void ) const 
        { 
            return adjacencyList.size(); 
        }
        
        void addEdge( std::pair<T,T> values )
        { 
            Node *n1 = new Node{ values.first };
            Node *n2 = new Node{ values.second };

            if (!adjacencyList[values.first]) 
                adjacencyList[values.first] = n2
            else {
                aux = adjacencyList[values.first]->next;
                while(aux != nullptr)
                    aux = aux->next;
                aux = n2
            }
            
            if (!adjacencyList[values.second]) 
                adjacencyList[values.second] = n1
            else {
                aux = adjacencyList[values.second]->next;
                while(aux != nullptr)
                    aux = aux->next;
                aux = n1
            }
        }

        void updateLoss( size_t i )
        { 
            loss[i]++;
        }

        // void addEdge( std::pair<T,T> values )
        // { 
        //     Node *n1 = new Node{ values.first };
        //     Node *n2 = new Node{ values.second };

        //     auto it1 = begin() + values.second;
        //     auto it2 = begin() + values.first;

        //     if()
        // }

        
    };

    //=== [VI] OPETARORS

    template < typename T >
    inline bool operator==( const sc::Graph<T> & l1_, const sc::Graph<T> & l2_ )
    {
        if(l1_.size() == l2_.size())
            {
                auto j = l2_.cbegin();
                for ( auto i = l1_.cbegin(); i != l1_.cend(); i++ )
                    {
                        if ( !(*i == *j) ) return false;
                        j++;
                    }
                return true;
            }

        return false;
    }

    template < typename T >
    inline bool operator!=( const sc::Graph<T> & l1_, const sc::Graph<T> & l2_ )
    {
        return !(l1_ == l2_);
    }
}
#endif