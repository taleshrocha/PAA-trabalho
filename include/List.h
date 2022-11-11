#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>  // cout, endl
using std::cout;
using std::endl;

#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
using std::copy;
#include <cstddef>   // std::ptrdiff_t
#include <type_traits>

namespace sc { // linear sequence. Better name: sequence container (same as STL).

    template < typename T >
    class List
    {
    private:
        //=== the data node.
        struct Node
        {
            T data;
            Node * next;
            Node * prev;

            Node( const T &d = T{} , Node * n = nullptr, Node * p = nullptr )
                : data{ d },
                  next{ n },
                  prev{ p }
            { /* empty */ }
        };

        //=== The iterator classes.
    public:
        /// Implements tha infrastrcture to support a bidirectional iterator.
        class iterator : public std::bidirectional_iterator_tag
        {
            //=== Some aliases to help writing a clearer code.
        public:
            using value_type        = T; //!< The type of the value stored in the List.
            using pointer           = T *; //!< Pointer to the value.
            using reference         = T &; //!< reference to the value.
            using const_reference   = const T &; //!< const reference to the value.
            using difference_type   = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

        private:
            Node * m_ptr; //!< The raw pointer.

        public:
            iterator( Node * ptr_ = nullptr ) : m_ptr{ ptr_ } { /* empty */ }

            ~iterator() = default;

            iterator( const iterator & ptr_ ) = default;

            iterator& operator=( const iterator & ptr_ ) = default;

            reference operator*()
            {
                return m_ptr->data;
            }

            const_reference  operator*() const
            {
                return m_ptr->data;
            }

            iterator operator++()
            {
                m_ptr = m_ptr->next;
                return *this;
            }

            iterator operator++(int)
            {
                iterator dummy{ *this };
                m_ptr = m_ptr->next;
                return dummy;
            }

            iterator operator--()
            {
                m_ptr = m_ptr->prev;
                return *this;
            }

            iterator operator--(int)
            {
                iterator dummy{ *this };
                m_ptr = m_ptr->prev;
                return dummy;
            }

            /// Equality operator.
            bool operator==( const iterator & rhs_ ) const
            {
                return m_ptr == rhs_.m_ptr;
            }

            /// Not equality operator.
            bool operator!=( const iterator & rhs_ ) const
            {
                return !(m_ptr == rhs_.m_ptr);
            }

            //=== Other methods that you might want to implement.
            /// it += 3; // Go back  3 positions within the container.
            iterator operator+=( difference_type step )
            {
                for ( auto i{0}; i < step; i++ ) m_ptr = m_ptr->next;
                return *this;
            }

            /// it -= 3; // Go back  3 positions within the container.
            iterator operator-=( difference_type step )
            {
                for ( auto i{0}; i < step; i++ ) m_ptr = m_ptr->prev;
                return *this;
            }
                
            /// it->method()
            pointer operator->( void ) const
            {
                return *this;
            }

            /// it1 - it2
            difference_type operator-( const iterator & rhs_ ) const
            {
                if (m_ptr > rhs_.m_ptr) return std::distance(rhs_.m_ptr, m_ptr);
                return std::distance(m_ptr, rhs_.m_ptr);
            }

            // We need friendship so the List<T> class may access the m_ptr field.
            friend class List<T>;

            /*friend std::ostream & operator<< ( std::ostream & os_, const iterator & s_ )
              {
              os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
              return os_;
              }*/
        };  
        
        class const_iterator : public std::bidirectional_iterator_tag 
        {
            //=== Some aliases to help writing a clearer code.
        public:
            using value_type        = T;         //!< The type of the value stored in the List.
            using pointer           = T *;       //!< Pointer to the value.
            using reference         = T &;       //!< reference to the value.
            using const_reference   = const T &; //!< const reference to the value.
            using difference_type   = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

        private:
            Node * m_ptr; //!< The raw pointer.

        public:
            const_iterator( Node * ptr = nullptr ) : m_ptr{ ptr } { /* empty */ }

            ~const_iterator() = default;

            const_iterator( const const_iterator & ) = default;

            const_iterator& operator=( const const_iterator & ) = default;

            reference operator*()
            {
                return m_ptr->data;
            }

            const_reference  operator*() const
            {
                return m_ptr->data;
            }

            const_iterator operator++()
            {
                m_ptr = m_ptr->next;
                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator dummy{ *this };
                m_ptr = m_ptr->next;
                return dummy;
            }

            const_iterator operator--()
            {
                m_ptr = m_ptr->prev;
                return *this;
            }

            const_iterator operator--(int)
            {
                const_iterator dummy{ *this };
                m_ptr = m_ptr->prev;
                return dummy;
            }

            /// Equality operator.
            bool operator==( const const_iterator & rhs_ ) const
            {
                return m_ptr == rhs_.m_ptr;
            }

            /// Not equality operator.
            bool operator!=( const const_iterator & rhs_ ) const
            {
                return !(m_ptr == rhs_.m_ptr);
            }

            //=== Other methods that you might want to implement.
            /// it += 3; // Go back  3 positions within the container.
            const_iterator operator+=( difference_type step )
            {
                for ( auto i{0}; i < step; i++ ) m_ptr = m_ptr->next;
                return *this;
            }

            /// it -= 3; // Go back  3 positions within the container.
            const_iterator operator-=( difference_type step )
            {
                for ( auto i{0}; i < step; i++ ) m_ptr = m_ptr->prev;
                return *this;
            }
                
            /// it->method()
            pointer operator->( void ) const
            {
                return *this;
            }

            /// it1 - it2
            difference_type operator-( const const_iterator & rhs_ ) const
            {
                if (m_ptr > rhs_.m_ptr) return std::distance(rhs_.m_ptr, m_ptr);
                return std::distance(m_ptr, rhs_.m_ptr);
            }

            // We need friendship so the List<T> class may access the m_ptr field.
            friend class List<T>;

            /*friend std::ostream & operator<< ( std::ostream & os_, const iterator & s_ )
              {
              os_ << "[@"<< s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
              return os_;
              }*/
        };

        //=== Private members.
    private:
        size_t m_size;
        Node * m_head;
        Node * m_tail;

    public:
        //=== Public interface

        //=== [I] Special members

        List() : m_size{ 0 }
        { 
            m_head = new Node();
            m_tail = new Node();

            m_head->next = m_tail;
            m_tail->prev = m_head;
        }

        explicit List( size_t count ) : List()
        {
            for ( size_t i = 0; i < count; i++ ) 
                push_back(T{});
        }

        template< typename InputIt >
        List( InputIt first, InputIt last ) : List()
        { 
            for ( InputIt i = first; i != last; i++ ) 
                push_back(*i);
        }

        List( const List & clone_ ) : List()
        {
            Node * cp = clone_.m_head->next;

            while ( cp->next != nullptr )
                {
                    push_back(cp->data);
                    cp = cp->next;
                }
        }

        List( std::initializer_List<T> iList_ ) : List()
        {
            for( auto i = iList_.begin(); i != iList_.end(); i++ )
                push_back(*i);
        }

        ~List()
        { 
            clear(); 
            delete m_head;
            delete m_tail;
        }

        List & operator=( const List & rhs )
        { 
            if ( !empty() ) clear();
            
            Node * cp = rhs.m_head->next;

            while ( cp->next != nullptr )
                {
                    push_back(cp->data);
                    cp = cp->next;
                }
            
            return *this;
        }

        List & operator=( std::initializer_List<T> iList_ )
        {
            if ( not empty() ) clear();

            for(auto i = iList_.begin(); i != iList_.end(); i++)
                push_back(*i);

            return *this;
        }


        //=== [II] ITERATORS
        iterator begin()
        { 
            return iterator( m_head->next );
        }

        const_iterator cbegin() const  
        { 
            return const_iterator( m_head->next );; 
        }

        iterator end() 
        { 
            return iterator( m_tail ); 
        }

        const_iterator cend() const  
        { 
            return const_iterator( m_tail ); 
        }


        //=== [III] Capacity/Status
        bool empty ( void ) const 
        { 
            return m_size == 0;
        }

        size_t size( void ) const 
        { 
            return m_size; 
        }

        //=== [IV] Modifiers
        
        void clear()  
        { 
            erase(begin(), end());
            m_size = 0;
        }

        T front( void ) 
        { 
            return m_head->next->data; 
        }

        T front( void ) const 
        { 
            return m_head->next->data; 
        }

        T back( void ) 
        {  
            return m_tail->prev->data; 
        }

        T back( void ) const 
        { 
            return m_tail->prev->data; 
        }

        void push_front( const T & value_ ) 
        { 
            insert(begin(), value_); 
        }

        void push_back( const T & value_ ) 
        { 
            insert(end(), value_); 
        }

        void pop_front()
        { 
            erase(begin()); 
        }

        void pop_back() 
        { 
            erase(m_tail->prev); 
        }


        //=== [IV-a] MODIFIERS W/ ITERATORS
        
        template < class InItr >
        void assign( InItr first_, InItr last_ )
        { 
            clear();
            while (first_ != last_)
                {
                    push_back(*first_);
                    first_++;
                }
        }
        
        void assign( std::initializer_List<T> iList_ )
        { 
            clear();
            for(auto it = iList_.begin(); it != iList_.end(); it++)
                push_back(*it);
        }
        
        iterator insert(iterator pos_, const T & value_ )
        { 
            Node *n = new Node{ value_ };
            n->prev = pos_.m_ptr->prev;
            n->next = pos_.m_ptr;
            pos_.m_ptr->prev->next = n;
            pos_.m_ptr->prev = n;
            m_size++;
            return iterator{n};
        }

        template < typename InItr >
        iterator insert( iterator pos_, InItr first_, InItr last_ )
        { 
            while (first_ != last_)
                {
                    insert(pos_,*first_);
                    first_++;
                }
            return pos_;
        }
        
        iterator insert( iterator cpos_, std::initializer_List<T> iList_ )
        { 
            for(auto it = iList_.begin(); it != iList_.end(); it++)
                insert(cpos_, *it);
            return cpos_; 
        }

        iterator erase( iterator it_ )
        {
            Node * temp = it_.m_ptr->next;
            it_.m_ptr->prev->next = it_.m_ptr->next;
            it_.m_ptr->next->prev = it_.m_ptr->prev;
            delete it_.m_ptr;
            m_size--;
            return iterator{temp}; 
            
        }

        iterator erase( iterator start, iterator end )
        {
            while(start != end)
                start = erase(start);
            return end; 
        }

        //=== [V] UTILITY METHODS
        void merge( List & other )
        { 
            Node * t_aux = m_head->next;
            Node * o_aux = other.m_head->next;
            Node * temp = o_aux; 
            while(t_aux != nullptr && o_aux->next != nullptr) {   
                if(o_aux->data < t_aux->data) { 
                    temp = o_aux;
                    o_aux = o_aux->next;
                    temp->next = t_aux;
                    t_aux->prev->next = temp;
                    temp->prev = t_aux->prev;
                    t_aux->prev = temp;
                    m_size++;
                    other.m_size--;
                } else if(t_aux->next == nullptr && o_aux->next != nullptr) 
                    {
                        temp = o_aux;
                        o_aux = o_aux->next;
                        temp->next = t_aux;
                        t_aux->prev->next = temp;
                        temp->prev = t_aux->prev;
                        t_aux->prev = temp;
                        m_size++;
                        other.m_size--;
                    } else {t_aux = t_aux->next; }
            }
            
            other.m_head->next = other.m_tail;
            other.m_tail->prev = other.m_head;
        }

        void splice( const_iterator pos, List & other )
        {
            m_size += other.size();
            
            pos.m_ptr->prev->next = other.m_head->next; 
            other.m_head->next->prev = pos.m_ptr->prev;
            other.m_tail->prev->next = pos.m_ptr; 
            pos.m_ptr->prev = other.m_tail->prev; 

            other.m_size = 0;
            other.m_head->next = other.m_tail;
            other.m_tail->prev = other.m_head;     
        }

        void reverse( void ) 
        { 
            Node * aux;
            Node * changer = m_head;
            do {
                aux = changer->next; 
                std::swap(changer->next, changer->prev);
                changer = aux;
            } while (changer != nullptr);
            std::swap(m_head,m_tail); 
        }
        
        void unique( void ) 
        { 
            iterator first = begin();
            iterator last = end();
            
            if (begin() == end())
                return;

            iterator next = first;
            
            while (++next != last){
                if (*first == *next){
                    erase(next);
                }else
                    first = next;
                next = first;
            }
            return;
        }
        
        void sort( void ) 
        { 
            if(size() <= 1) { return; }
            
            iterator it_aux = begin();
            size_t half_size = size()/2;
            for(size_t i = 0; i < half_size; i++)
                it_aux++;
            List<T> List_aux;
            
            List_aux.m_tail->prev = m_tail->prev;
            m_tail->prev->next =  List_aux.m_tail;
            
            m_tail->prev = it_aux.m_ptr->prev;
            it_aux.m_ptr->prev->next = m_tail;
            it_aux.m_ptr->prev = nullptr;
            
            List_aux.m_head->next = it_aux.m_ptr;
            it_aux.m_ptr->prev = List_aux.m_head;
            
            List_aux.m_size = size() - half_size;
            m_size = half_size; 
            
            sort();
            List_aux.sort();
            merge(List_aux);

        }
    };

    //=== [VI] OPETARORS

    template < typename T >
    inline bool operator==( const sc::List<T> & l1_, const sc::List<T> & l2_ )
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
    inline bool operator!=( const sc::List<T> & l1_, const sc::List<T> & l2_ )
    {
        return !(l1_ == l2_);
    }
}
#endif
