#ifndef BINTREE_HPP_
#define BINTREE_HPP_

#include "Util.hpp"
#include <iostream>
#include <string>

namespace avlt {
  class AvlTree {
    private:
      struct Node {
        int key;     //!< The node key.
        int balance; //!< The difference between right height and the left height.
        Node* left;  //!< A pointer to the left node in the list.
        Node* right; //!< A pointer to the right node in the list.

        //! Default Ctro.
        Node(const int k, int b = 0, Node* l = nullptr, Node* r = nullptr)
          : key{k}, balance{b}, left{l}, right{r} { /*empty*/}
      };

      Node* root; //!< The root node.

    public:
      // @brief The class constructor.
      AvlTree(Node* r = new Node(0)) : root{r} { /*empty*/}

      // @brief The class destructor.
      ~AvlTree();

      /*
       * @brief
       * @param
       */
      Node* right_rotation(Node* root);

      Node* left_rotation(Node* root);

      Node* double_left_rotation(Node* root);

      Node* double_right_rotation(Node* root);

      void insert(int key, Node* node, bool* h);

      void right_rebalance(Node* node, bool* h);
      
      void left_rebalance(Node* node, bool* h);

      bool remove(int key, Node* node, bool* h);

      /*
       * @brief Recursively removes the node from memory with all its sub-nodes.
       * @param A pointer to a node.
       */
      void remove_node(Node* node);

      /*
       * @brief Gives the root node of the tree.
       * @return The root node of the tree.
       */
      Node* getRoot();

      /*
       * @brief Gives the key value of the node.
       * @param node: a arbitrary node.
       * @return The key in the node.
       */
      int visit(Node* node);


      /*
       * @brief Prints the binary tree in a nice way.
       * @param node an Node containing the node that the tree is going to start to
       be printed.
       * @param prefix a string to help indent the tree.
       * @param isLeft a bool to just to see if the node is a left one.
       */
      void print(Node* node, std::string prefix = "", bool isLeft = false);

      Node* search(int key, Node* root, bool forPrint);
  };
} // namespace avlt

#endif // BINTREE_HPP_
