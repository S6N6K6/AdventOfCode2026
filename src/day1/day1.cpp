#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <vector>

const char *DIAL_SEQUENCE_EXAMPLE =
    "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82";

#ifdef DAY1_EXAMPLE
    #define DO_EXAMPLE true
#else
    #define DO_EXAMPLE false
#endif

enum DIRECTION { LEFT = 0, RIGHT };

struct DialSequence {
  DIRECTION direction;
  int value;
};

std::string readFile(const char *fileName) {
  /*
   *   Method to read a file into a string that will be further processed down
   * the line
   */
  auto size = std::filesystem::file_size(fileName);
  std::string content(size, '\0');
  std::ifstream in(fileName);
  in.read(&content[0], size);
  return content;
}

std::vector<DialSequence> processSequence(std::string inputSequence) {
  std::vector<std::string> tokens;

  size_t pos = 0;
  while (pos != std::string::npos) {
    pos = inputSequence.find('\n');
    tokens.push_back(inputSequence.substr(0, pos));
    inputSequence.erase(0, pos + 1);
  }

  std::vector<DialSequence> sequences;
  sequences.reserve(tokens.size());
  for (auto e : tokens) {
    sequences.emplace_back(DialSequence{(e[0] == 'L') ? LEFT : RIGHT,
                                        std::stoi(e.substr(1, e.length()))});
  }
  return sequences;
}

int applySequence(int currentPos, DialSequence &sequence, int &clicks) {
  int displacement =
      (sequence.value < 100) ? sequence.value : sequence.value % 100;
  clicks += ((sequence.value < 100)
                 ? 0
                 : static_cast<int>(floor(sequence.value / 100.0)));
  int newPos = currentPos;
  switch (sequence.direction) {
  case LEFT:
    if (currentPos > displacement)
      newPos = currentPos - displacement;
    else {
      newPos = 100 - (displacement - currentPos);
      /* std::println("currentPos: {}| displacement: {} | newPos: {} | Add one click to {}",
                   currentPos, sequence.value, newPos, clicks); */
      if (currentPos != 0)
        clicks += 1;
    }
    if (newPos >= 100) {
      /* std::println("currentPos: {}| displacement: {} | newPos: {} |",
                   currentPos, sequence.value, newPos); */
      newPos = newPos - 100;
    }
    break;
  case RIGHT:
    newPos = currentPos + displacement;
    if (newPos >= 100) {
      newPos = newPos - 100;
      clicks += 1;
    }
    break;
  default:
    std::println("Something Went Horribly Wrong if you are here");
    break;
  }
  //std::println("Clicks: {}", clicks);

  return newPos;
}

int main() {
  int starting_position = 50;
  int currentPosition = starting_position;
  int counter = 0;
  int clicks = 0;
  auto seqs = processSequence((DO_EXAMPLE) ? std::string(DIAL_SEQUENCE_EXAMPLE)
                                           : readFile("day1_input.txt"));
  for (auto seq : seqs) {
    currentPosition = applySequence(starting_position, seq, clicks);
    if (currentPosition == 0) {
      counter++;
    }
    starting_position = currentPosition;
  }

  std::println("Result: {}", counter);
  std::println("Number of times the dial passes through 0: {}", clicks);

  return 0;
}