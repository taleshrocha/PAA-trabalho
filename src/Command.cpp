#include "Command.hpp"

int Command::get_command(std::string command) {
  if (matchCommand.find(command) != matchCommand.end())
    return matchCommand.at(command);
  return -1;
}

Command::Command() {
  //Constructor empty
}