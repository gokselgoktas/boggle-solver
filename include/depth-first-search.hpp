#ifndef BOGGLE_DEPTH_FIRST_SEARCH
#define BOGGLE_DEPTH_FIRST_SEARCH

#include "board.hpp"
#include "dictionary.hpp"

#include <unordered_set>

namespace boggle {
struct DepthFirstSearch {
    typedef std::unordered_set<std::string> Results;

    Results const &operator()(Board const &board, Dictionary const &dictionary);

private:
    void flood(Board const &board, Dictionary const &dictionary, int x, int y,
        std::string string);

protected:
    Results results_;

private:
    std::vector<bool> visitedPoints_;
};
}

#endif
