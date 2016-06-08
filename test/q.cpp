#include "boggle.hpp"

#include <chrono>

#include <iostream>
#include <fstream>
#include <cassert>

int main(int count, char *arguments[])
{
        LoadDictionary("./test/q.txt");

        auto start = std::chrono::high_resolution_clock::now();
        Results results = FindWords("paqezoatirdkquic", 4, 4);
        auto end = std::chrono::high_resolution_clock::now();

        if (results.Count != 6 || results.Score != 10) {
                exit(1);
        }

        for (unsigned i = 0; i < results.Count; ++i) {
                std::cout << results.Words[i] << ' ';
        }

        std::cout << "\n\nA total of " << results.Count <<
                " words found for " << results.Score << " points @" <<
                std::chrono::duration<float,
                        std::chrono::milliseconds::period>(
                                end - start).count() << "ms\n";

        FreeWords(results);
        FreeDictionary();

        std::cout << '\n' << *arguments << ": test passed...\n";

        return 0;
}
