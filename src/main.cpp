#include "boggle.hpp"

#include <chrono>

#include <cassert>
#include <fstream>
#include <iostream>

using namespace boggle;

int main(int count, char *arguments[])
{
    using namespace boggle;

    size_t cullCount = 0;
    size_t totalPoints = 0;

    std::string boardString;

    std::ifstream boardFile("./examples/board-1000.txt");
    boardFile >> boardString;

    boardString =
        "lrfkqyuqfjkxyqvnrtysfrzrmzlygfveulqfpdbhlqdqrrcrwdnxeuoqqeklaitg";
    Board board(boardString, 8, 8);

    Dictionary dictionary(
        "./examples/460k.txt", [&](std::string const &string) {
            for (auto i : string) {
                if (board.hasValue(i) == false) {
                    ++cullCount;
                    return false;
                }
            }

            return true;
        });

    std::cout << "\nCulled " << cullCount
              << " words from the dictionary...\n\nFound:\n";

    Solver<OptimizedSearch> solver;

    auto start = std::chrono::high_resolution_clock::now();
    auto results = solver(board, dictionary);
    auto end = std::chrono::high_resolution_clock::now();

    for (auto const &i : results) {
        totalPoints += getScoreForWord(i);
        std::cout << i << ' ';
    }

    std::cout
        << "\n\nA total of " << solver.getResults().size() << " for "
        << totalPoints << " points @"
        << std::chrono::duration<float, std::chrono::milliseconds::period>(
               end - start)
               .count()
        << "ms\n";

    /* A total of 79334 for 445310 points @25524.9ms
     * A total of 79334 for 445310 points @495.4ms
     *
     * A total of 195654 for 1603214 points @46644.9ms */

    return 0;
}
