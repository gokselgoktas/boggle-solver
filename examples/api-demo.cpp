#include "boggle.hpp"

#include <iostream>

int main(int count, char *arguments[])
{
        using namespace boggle;

        if (count != 2) {
                std::cout << "Usage: " << *arguments << " [dictionary]\n";
                return 1;
        }

        LoadDictionary(arguments[1]);

        Results results = FindWords("zpweaufsx", 3, 3);

        for (unsigned i = 0; i < results.Count; ++i) {
                std::cout << results.Words[i] << ' ';
        }

        std::cout << "\n\nA total of " << results.Count <<
                " words for " << results.Score << " points!\n";

        FreeWords(results);
        FreeDictionary();

        return 0;
}
