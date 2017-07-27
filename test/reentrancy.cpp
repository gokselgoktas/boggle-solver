#include "boggle.hpp"

#include <cassert>
#include <iostream>

int main(int count, char *arguments[])
{
    using namespace boggle;

    LoadDictionary("./test/task.txt");

    Results results = FindWords("zpweaufsx", 3, 3);
    results = FindWords("juqwapoqw", 3, 3);
    results = FindWords("pzhouceza", 3, 3);
    results = FindWords("zpweaufsx", 3, 3);

    if (results.Count != 38 || results.Score != 40) {
        exit(1);
    }

    for (unsigned i = 0; i < results.Count; ++i) {
        std::cout << results.Words[i] << ' ';
    }

    std::cout << '\n';

    FreeWords(results);
    FreeDictionary();

    std::cout << *arguments << ": test passed...\n";

    return 0;
}
