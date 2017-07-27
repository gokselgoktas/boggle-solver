#include "boggle.hpp"

#include <cassert>

#include <fstream>
#include <iostream>

void test(unsigned width, unsigned height)
{
    unsigned totalScore = 0;
    std::ofstream dictionary("./test/worst-case.txt");

    for (unsigned i = 0; i < width * height - 3; ++i) {
        std::string word(i + 3, 'w');

        dictionary << word << '\n';
        totalScore += boggle::getScoreForWord(word);
    }

    dictionary.close();

    LoadDictionary("./test/worst-case.txt");

    std::string board(width * height, 'w');
    Results results = FindWords(board.c_str(), width, height);

    if (results.Count != (width * height - 3) || results.Score != totalScore) {
        exit(1);
    }

    FreeWords(results);
    FreeDictionary();

    std::cout << width << 'x' << height << ' ';
}

int main(int count, char *arguments[])
{
    for (unsigned y = 3; y <= 4; ++y) {
        for (unsigned x = 3; x <= 4; ++x) {
            test(x, y);
        }
    }

    std::cout << '\n' << *arguments << ": test passed...\n";
    return 0;
}
