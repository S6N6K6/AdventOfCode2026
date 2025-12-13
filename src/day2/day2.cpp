#include <cstdint>
#include <print>

#include "utils.hpp"

#define DAY2_EXAMPLE_FILENAME "day2_example.txt"

#ifdef DAY2_EXAMPLE
    #define DO_EXAMPLE true
#else
    #define DO_EXAMPLE false
    #define INPUT_FILE "day2_input.txt"
#endif

bool containsRepeatedSequence(std::int64_t n)
{
    std::string stringNumber = std::to_string(n);

    if (stringNumber.length() % 2 != 0)
        return false;

    int halfSize = stringNumber.length() / 2; // because it can be divide by 2
    if (strcmp(stringNumber.substr(0, halfSize).c_str(), stringNumber.substr(halfSize).c_str()) == 0)
        return true;
    return false;
}

class IDRange
{
public:
    IDRange(std::int64_t start, std::int64_t end) : m_start(start), m_end(end) {}

    IDRange() : IDRange(0, 0) {}

    std::int64_t findUnsuitableIndices()
    {
        std::int64_t sum = 0;
        for (std::int64_t i = m_start; i <= m_end; i++)
        {
            if (containsRepeatedSequence(i))
            {
                sum += i;
                
                std::println("Found Invalid ID: {}", i);
            }
        }

        return sum;
    }

private:
    std::int64_t m_start;
    std::int64_t m_end;
};

std::vector<std::pair<std::string, std::string>> processIds(std::vector<std::string> input)
{
    std::vector<std::pair<std::string, std::string>> result;
    result.reserve(input.size());
    for (std::string elem : input)
    {
        auto items = splitStringByDelimiter(elem, '-');
        result.emplace_back(std::pair{items[0], items[1]});
    }

    return result;
}

int main()
{
    // std::println("Hello from day2 solution");
    #if DO_EXAMPLE
        std::string example = readFile(DAY2_EXAMPLE_FILENAME);
    #else
        std::string example = readFile(INPUT_FILE);
    #endif
    // std::println("Read example: {}", example);
    auto splittedString = splitStringByDelimiter(example, ',');
    // printContainer(splittedString.begin(), splittedString.end());
    auto pairs = processIds(splittedString);
    std::vector<IDRange> idranges;
    idranges.reserve(pairs.size());
    std::string::size_type sz;
    for (std::pair<std::string, std::string> pair : pairs)
    {
        std::println("Pair({} | len={}, {} | len={})", pair.first, pair.first.length(), pair.second, pair.second.length());
        idranges.emplace_back(IDRange(stoll(pair.first, &sz), stoll(pair.second, &sz)));
    }
    std::int64_t totalSum = 0;
    for (auto e : idranges)
    {
        totalSum += e.findUnsuitableIndices();
    }

    std::println("Total Sum: {}", totalSum);
}