#include "Util.hpp"
#include "Command.hpp"
#include "AvlTree.hpp"

using namespace avlt;
using std::cout;
using std::endl;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  std::string entry;
  std::string command;
  std::string value;
  Command command_sys;

  AvlTree* avlTree = new AvlTree();

  bool h = true;

  while (true)
  {
    std::cout << "avlt_cli> ";
    std::getline(std::cin, entry);

    command = split(entry).front();
    value = split(entry).back();

    switch (command_sys.get_command(command)) {
    case command_sys.insert:
      std::cout << "Inserting..." << std::endl;
      if (avlTree->search(stoi(value), avlTree->getRoot(), true) != nullptr) {
        cout << "The selected key already exists in the tree. Please enter another value." << endl;
      } else { 
        h = true;
        avlTree->insert(stoi(value), avlTree->getRoot(), &h);
        avlTree->print(avlTree->getRoot());
      }
      break;
    case command_sys.remove:
      if (avlTree->search(stoi(value), avlTree->getRoot(), false) == nullptr) {
        cout << "The selected key already not exists in the tree. Please enter another value." << endl;
      } else {
        std::cout << "remove" << std::endl;
        h = true;
        avlTree->remove(stoi(value), avlTree->getRoot(), &h);
        avlTree->print(avlTree->getRoot());
      }
      break;
    case command_sys.search:
      std::cout << "Searching..." << std::endl;
      if (avlTree->search(stoi(value), avlTree->getRoot(), true) == nullptr){
        cout << "Key not found" << endl;
      }
      break;
    case command_sys.exit:
      std::cout << "Exiting.." << std::endl;
      delete avlTree;
      return EXIT_SUCCESS;
      break;
    default:
      std::cout << "Command not found! Please enter a valid command" << std::endl;
      break;
    }

    entry.clear();
    command.clear();
    value.clear();
  }

  return 0;
}
