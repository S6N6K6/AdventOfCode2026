#include <filesystem>
#include <print>
#include <string>
#include <fstream>
#include <vector>

const char* DIAL_SEQUENCE_EXAMPLE= "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL999\nR14\nL82";

#define DO_EXAMPLE true
#ifdef DAY1_EXAMPLE
    #define DO_EXAMPLE false
#endif

enum DIRECTION {
    LEFT = 0,
    RIGHT
};

struct DialSequence {
    DIRECTION direction;
    int value;
};

std::string readFile(const char* fileName){
    /*
    *   Method to read a file into a string that will be further processed down the line
    */
    auto size = std::filesystem::file_size(fileName);
    std::string content(size, '\0');
    std::ifstream in(fileName);
    in.read(&content[0], size);
    return content;
}

std::vector<DialSequence> processSequence(std::string inputSequence){
    std::vector<std::string> tokens;

    size_t pos = 0;
    while (pos != std::string::npos){
        pos = inputSequence.find('\n');
        tokens.push_back(inputSequence.substr(0, pos));
        inputSequence.erase(0, pos+1);
    }

    std::vector<DialSequence> sequences;
    sequences.reserve(tokens.size());
    for(auto e: tokens){
        std::println("Token: {}", e);
        sequences.emplace_back(DialSequence{
            (e[0] == 'L') ? LEFT : RIGHT,
            std::stoi(e.substr(1, e.length()))
        });
    }
    return sequences;
}

int applySequence(int currentPos, DialSequence& sequence){
    int displacement = (sequence.value < 100) ? sequence.value : sequence.value % 100;
    int newPos = currentPos;
    switch (sequence.direction) {
        case LEFT:
            if (currentPos > displacement)
                newPos = currentPos - displacement;
            else
                newPos = 100 - (displacement - currentPos);
            if (newPos >= 100)
                newPos = newPos - 100;
            break;
        case RIGHT:
            newPos = currentPos + displacement;
            if (newPos >= 100)
                newPos = newPos - 100;
            break;
        default:
            std::println("Something Went Horribly Wrong if you are here");
            break;
    }

    std::println("New Position After Dial Sequence Applied: {}", newPos);
    return newPos;
}

int main(){
    int starting_position = 50;
    int currentPosition = starting_position;
    int counter = 0;
    auto seqs = processSequence((DO_EXAMPLE)? std::string(DIAL_SEQUENCE_EXAMPLE) : readFile("day1_input.txt"));
    for(auto seq: seqs){
        currentPosition = applySequence(starting_position, seq);
        if(currentPosition == 0){
            counter++;
        }
        starting_position = currentPosition;
    }

    std::println("Result: {}", counter);

    return 0;
}