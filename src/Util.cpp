#include "Util.hpp"

using notation_t = std::vector<std::string>;

bool is_operator(const char str) {
  return (
      ( str == 'B' ||
        str == 'I' ||
        str == 'R') ? true : false);
}

std::fstream openFile(std::string fileName){
  std::fstream fs;

  fs.open(fileName);

  if(!fs.is_open()) {
    fs.clear();
    fs.open(fileName, std::ios::out); //Create file.
    fs.close();
    fs.open(fileName);
    std::cout << "Arquivo " << fileName << " criado" << std::endl; 
  }

  return fs;
}

notation_t readFile(std::string fileName) {
  std::vector<std::string> eq;
  std::string line;

  std::fstream fs = openFile(fileName);

  while (std::getline(fs, line))
    eq.push_back(line);

  fs.close();

  return eq;
}

void writeFile(notation_t expressions, std::string fileName) {
  std::fstream fs = openFile(fileName);

  for (std::string expression : expressions) {
    fs << expression << std::endl;
  }
  fs.close();
}

void print(std::vector<std::string> notation) {
  for(std::string line : notation)
    std::cout << line << std::endl;
}

int calculator(std::string expression) {
  std::stack<int> result;
  int a, b;
  size_t pos = 0;
  std::string delim = " ";
  std::string number;
  std::string str;

  while( ( pos = expression.find(delim) ) != std::string::npos ) {
    str = expression.substr(0, pos);
    expression.erase(0, pos + delim.length());

    if(str == "+") {
      a = result.top();
      result.pop();
      b = result.top();
      result.pop();
      result.push(a+b);
    }

    else if(str == "-") {
      a = result.top();
      result.pop();
      b = result.top();
      result.pop();
      result.push(b-a);
    }

    else if(str == "*") {
      a = result.top();
      result.pop();
      b = result.top();
      result.pop();
      result.push(a*b);
    }

    else if(str == "/") {
      a = result.top();
      result.pop();
      b = result.top();
      result.pop();
      result.push(int(b/a));
    }

    else if(str == "^") {
      a = result.top();
      result.pop();
      b = result.top();
      result.pop();
    }

    else
      result.push(stoi(str));
  }
  return result.top();
}

void check_dir(const std::filesystem::path path) {
  if (!std::filesystem::exists(path)){
    if (std::filesystem::create_directory(path)){
      std::cout << "Directory data/out created success" << std::endl;
    } else {
      std::cout << "Directory data/out created fail" << std::endl;
    }
  }
}

std::vector<std::string> split(std::string str) {
    std::vector<std::string> commands;
    std::stringstream ss(str);
    std::string word;
    
    while (ss >> word) {
      commands.push_back(word);
    }
    return commands;
}