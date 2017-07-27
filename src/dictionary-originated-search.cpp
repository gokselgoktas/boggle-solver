#include "dictionary-originated-search.hpp"

#ifndef NDEBUG
#include <iostream>
#endif

namespace boggle {
DictionaryOriginatedSearch::Results const &DictionaryOriginatedSearch::
    operator()(Board const &board, Dictionary const &dictionary)
{
    results_.clear();

    visitedPoints_.resize(board.getWidth() * board.getHeight());
    visitedPoints_.assign(visitedPoints_.size(), false);

    std::string string;
    traverse(board, dictionary.getRootNode(), string);

    return results_;
}

void DictionaryOriginatedSearch::traverse(Board const &board,
    std::shared_ptr<TrieNode> const &trieNode, std::string &string)
{
    if (trieNode->isWordBoundary() == true) {
        bool isPossible =
            string.size() <= board.getWidth() * board.getHeight() &&
            string.size() >= 3;

        if (isPossible && search(board, string)) {
            results_.insert(string);
        }
    }

    for (auto const &i : trieNode->getSubnodes()) {
        string += i.first;

        if (i.second != nullptr) {
            traverse(board, i.second, string);
        }

        string.pop_back();
    }
}

bool DictionaryOriginatedSearch::search(
    Board const &board, std::string const &string)
{
    auto positions = board.findValue(string[0]);

    for (auto const &i : positions) {
        visitedPoints_.assign(visitedPoints_.size(), false);
        visitedPoints_[i.first + i.second * board.getWidth()] = true;

#ifndef NDEBUG
        visualize(board);
#endif

        if (flood(board, i.first, i.second, string, 0)) {
            return true;
        }
    }

    return false;
}

bool DictionaryOriginatedSearch::flood(Board const &board, int x, int y,
    std::string const &string, std::string::size_type i)
{
    constexpr int const OFFSETS[] = {
        1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1};

    if (i == string.size() - 1) {
        return true;
    }

    for (int r = 0; r < 16; r += 2) {
        int k = x + OFFSETS[r + 0];
        int l = y + OFFSETS[r + 1];

        if (board.doesContainPoint(k, l) == false) {
            continue;
        }

        bool isVisited = visitedPoints_[k + l * board.getWidth()];

        if (isVisited == false && board[{k, l}] == string[i + 1]) {
            visitedPoints_[k + l * board.getWidth()] = true;

#ifndef NDEBUG
            visualize(board);
#endif

            if (flood(board, k, l, string, i + 1)) {
                return true;
            }

            visitedPoints_[k + l * board.getWidth()] = false;
        }
    }

    return false;
}

#ifndef NDEBUG
void DictionaryOriginatedSearch::visualize(Board const &board) const
{
    for (unsigned y = 0; y < board.getHeight(); ++y) {
        for (unsigned x = 0; x < board.getWidth(); ++x) {
            bool value = visitedPoints_[x + y * board.getWidth()];

            std::cout << value << ' ';
        }

        std::cout << '\n';
    }

    std::cout << '\n';
}
#endif
}
