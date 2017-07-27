#include "optimized-search.hpp"
#include <iostream>

namespace boggle {
OptimizedSearch::Results const &OptimizedSearch::operator()(
    Board const &board, Dictionary const &dictionary)
{
    results_.clear();

    visitedPoints_.resize(board.getWidth() * board.getHeight());
    visitedPoints_.assign(visitedPoints_.size(), false);

    for (auto const &i : dictionary.getRootNode()->getSubnodes()) {
        auto positions = board.findValue(i.first);

        for (auto const &k : positions) {
            std::string string;
            search(board, k.first, k.second, i.first, i.second, string);
        }
    }

    return results_;
}

void OptimizedSearch::search(Board const &board, unsigned x, unsigned y,
    char letter, std::shared_ptr<TrieNode> const &trieNode, std::string &string)
{
    visitedPoints_[x + y * board.getWidth()] = true;
    string += letter;

    if (trieNode->isWordBoundary() == true) {
        bool isPossible =
            string.size() <= board.getWidth() * board.getHeight() &&
            string.size() >= 3;

        if (isPossible) {
            results_.insert(string);
        }
    }

    constexpr int const OFFSETS[] = {
        1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1};

    for (int r = 0; r < 16; r += 2) {
        int k = x + OFFSETS[r + 0];
        int l = y + OFFSETS[r + 1];

        if (board.doesContainPoint(k, l) == false) {
            continue;
        }

        bool isVisited = visitedPoints_[k + l * board.getWidth()];

        auto i = trieNode->findSubnode(board[{k, l}]);

        if (isVisited == false && i != nullptr) {
            search(board, k, l, board[{k, l}], i, string);
        }

        if (board[{x, y}] == 'q') {
            i = trieNode->findSubnode('u');

            if (isVisited == false && i != nullptr) {
                search(board, x, y, 'u', i, string);
            }
        }
    }

    string.pop_back();
    visitedPoints_[x + y * board.getWidth()] = false;
}
}
