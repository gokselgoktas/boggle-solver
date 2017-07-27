#ifndef BOGGLE_OPTIMIZED_SEARCH_HPP
#define BOGGLE_OPTIMIZED_SEARCH_HPP

#include "board.hpp"
#include "dictionary.hpp"

#include <unordered_set>

namespace boggle {
class OptimizedSearch {
public:
    typedef std::unordered_set<std::string> Results;

    Results const &operator()(Board const &board, Dictionary const &dictionary);

private:
    void search(Board const &board, unsigned x, unsigned y, char letter,
        std::shared_ptr<TrieNode> const &trieNode, std::string &string);

protected:
    Results results_;

private:
    std::vector<bool> visitedPoints_;
};
}

#endif
