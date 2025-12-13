#pragma once
/*
    UTILITIES TO STREAMLINE CERTAIN FUNCTIONS
*/

#include <filesystem>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>

/*Method to read a file into a single string*/
std::string readFile(const char *fileName) {
  auto size = std::filesystem::file_size(fileName);
  std::string content(size, '\0');
  std::ifstream in(fileName);
  in.read(&content[0], size);
  return content;
}

std::vector<std::string> splitStringByDelimiter(std::string inputSequence, char delim) {
  std::vector<std::string> tokens;

  size_t pos = 0;
  while (pos != std::string::npos) {
    pos = inputSequence.find(delim);
    tokens.push_back(inputSequence.substr(0, pos));
    inputSequence.erase(0, pos + 1);
  }

  return tokens;
}

template<typename Iter>
void printContainer(Iter it, Iter end){
  for (; it!= end; ++it){
    std::println("{}", *it);
  }
}