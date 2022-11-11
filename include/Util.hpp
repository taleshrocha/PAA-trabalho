#ifndef UTIL_HPP_
#define UTIL_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <filesystem>
#include "AvlTree.hpp"

using std::cout;
using std::endl;

#define file_prefix_in "./data/in/prefix.in"

#define file_out_dir "./data/out"
#define file_prefix_out "./data/out/prefix.out"
#define file_postfix_out "./data/out/postfix.out"
#define file_infix_out "./data/out/infix.out"
#define file_aval_out "./data/out/aval.out"

using notation_t = std::vector<std::string>;

  /*
   * @brief Gets a char and checking if is an operator.
   * @param const char str: a char.
   * @return True if last character is a operator, false otherwise.
   */
bool is_operator(const char str);

std::fstream openFile(std::string fileName);

notation_t readFile(std::string fileName);

void writeFile(notation_t expressions, std::string fileName);

void print(std::vector<std::string> notation);

int calculator(std::string expression);

void check_dir(const std::filesystem::path path);

std::vector<std::string> split(std::string str);

#endif
