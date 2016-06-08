#include "boggle.hpp"

#include <cassert>
#include <iostream>

int main(int count, char *arguments[])
{
        using namespace boggle;

        LoadDictionary("./test/task.txt");

        Results results = FindWords("zpweaufsx", 3, 3);

        if (results.Count != 38 || results.Score != 40) {
                exit(1);
        }

        FreeWords(results);
        FreeDictionary();

        std::cout << *arguments << ": test passed...\n";

        return 0;
}
