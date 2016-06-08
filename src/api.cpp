#include "boggle.hpp"

using namespace boggle;

static Dictionary *DICTIONARY = nullptr;

void LoadDictionary(char const *path)
{
        DICTIONARY = new Dictionary(path);
}

Results FindWords(char const *values, unsigned width, unsigned height)
{
        Results results { nullptr, 0, 0, nullptr };

        Board board(values, width, height);

        if (board.isValid() == false) {
                return results;
        }

        Solver<OptimizedSearch> solver;
        auto words = solver(board, *DICTIONARY);

        if (words.size() == 0) {
                return results;
        }

        char **buffer = new char *[words.size()];

        for (auto const &i : words) {
                buffer[results.Count] = new char[i.size() + 1];

                i.copy(buffer[results.Count], i.size());
                buffer[results.Count][i.size()] = '\0';

                results.Score += getScoreForWord(i);
                ++results.Count;
        }

        results.Words = buffer;
        return results;
}

void FreeWords(Results results)
{
        for (unsigned i = 0; i < results.Count; ++i) {
                delete[] results.Words[i];
        }

        delete[] results.Words;
}

void FreeDictionary()
{
        delete DICTIONARY;
}
