#include "boggle.hpp"

#include <cassert>

#include <random>
#include <chrono>

#include <iostream>
#include <fstream>

void fuzz(int i, std::mt19937 &generator)
{
        std::uniform_int_distribution<unsigned> sizeDistribution(100, 300);
        std::uniform_int_distribution<char> boardDistribution('\1', '\127');

        unsigned width = sizeDistribution(generator);
        unsigned height = sizeDistribution(generator);

        std::string board(width * height, ' ');
        std::transform(board.begin(), board.end(), board.begin(),
                [&](char)
                {
                        return boardDistribution(generator);
                });

        Results results = FindWords(board.c_str(), width, height);

        FreeWords(results);
}

void test(int i, std::mt19937 &generator)
{
        std::uniform_int_distribution<unsigned> sizeDistribution(100, 300);
        std::uniform_int_distribution<char> boardDistribution('a', 'z');

        unsigned width = sizeDistribution(generator);
        unsigned height = sizeDistribution(generator);

        std::string board(width * height, ' ');

        std::transform(board.begin(), board.end(), board.begin(),
                [&](char)
                {
                        return boardDistribution(generator);
                });

        auto start = std::chrono::high_resolution_clock::now();

        Results results = FindWords(board.c_str(), width, height);

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << i << ": " << width << 'x' << height << " - " <<
                results.Count << " words, " << results.Score << " points @" <<
                std::chrono::duration<float,
                        std::chrono::milliseconds::period>(
                                end - start).count() << "ms\n";

        FreeWords(results);
}

int main(int count, char *arguments[])
{
        LoadDictionary("./examples/460k.txt");

        std::mt19937 generator(1337);

        for (int i = 0; i < 100; ++i) {
                fuzz(i, generator);
        }

        std::cout << "Success: FUZZ completed\n\n";

        for (int i = 0; i < 100; ++i) {
                test(i, generator);
        }

        FreeDictionary();

        std::cout << '\n' << *arguments << ": test passed...\n";
        return 0;
}
