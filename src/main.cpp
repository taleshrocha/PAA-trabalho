//#include "List.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;


int main ( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] )
{
  std::ifstream infile("./data/SW-100-3-0d1-trial2.edges");

  std::string line;

  while ( std::getline(infile, line) ) {

    std::istringstream iss(line);

    int a, b;

    if (!(iss >> a >> b)) { break; } // error

    cout << a << " " << b << endl;
  }


  return 0;
}
