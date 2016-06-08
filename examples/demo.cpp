#include "boggle.hpp"

#include <iostream>

int main(int count, char *arguments[])
{
        using namespace boggle;

        if (count != 2) {
                std::cout << "Usage: " << *arguments << " [dictionary]\n";
                return 1;
        }

        size_t cullCount = 0;
        size_t totalPoints = 0;

        Board board("zpweaqfsxlasleunpnoanslseavlvalujdihfsxlasleubdhazpweaqfs"
                "xlasleunpnoanslseavlvalujdihfsxlasleubdhaue", 10, 10);

        Dictionary dictionary(arguments[1],
                [&](std::string const &string)
                {
                        for (auto i : string) {
                                if (board.hasValue(i) == false) {
                                        ++cullCount;
                                        return false;
                                }
                        }

                        return true;
                });

        std::cout << board << "\n\nCulled " << cullCount <<
                " words from the dictionary...\n\nFound:\n";

        Solver<DictionaryOriginatedSearch> solver;

        for (auto const &i : solver(board, dictionary)) {
                totalPoints += getScoreForWord(i);
                std::cout << i << ' ';
        }

        std::cout << "\n\nA total of " << solver.getResults().size() <<
                " words for " << totalPoints << " points!\n";

        return 0;
}
