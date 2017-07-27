#include "depth-first-search.hpp"

namespace boggle {
DepthFirstSearch::Results const &DepthFirstSearch::operator()(
    Board const &board, Dictionary const &dictionary)
{
    results_.clear();
    visitedPoints_.resize(board.getWidth() * board.getHeight());

    for (unsigned y = 0; y < board.getHeight(); ++y) {
        for (unsigned x = 0; x < board.getWidth(); ++x) {
            visitedPoints_.assign(visitedPoints_.size(), false);
            flood(board, dictionary, x, y, std::string());
        }
    }

    return results_;
}

void DepthFirstSearch::flood(Board const &board, Dictionary const &dictionary,
    int x, int y, std::string string)
{
    if (board.doesContainPoint(x, y) == false ||
        visitedPoints_[x + y * board.getWidth()]) {
        return;
    }

    string += board.getValue(x, y);

    if (dictionary.hasWordPrefix(string) == false) {
        return;
    } else if (string.size() >= 3 && dictionary.hasWord(string) == true) {
        results_.insert(string);
    }

    visitedPoints_[x + y * board.getWidth()] = true;

    flood(board, dictionary, x + 1, y + 0, string);
    flood(board, dictionary, x + 1, y + 1, string);
    flood(board, dictionary, x + 0, y + 1, string);
    flood(board, dictionary, x - 1, y + 1, string);
    flood(board, dictionary, x - 1, y + 0, string);
    flood(board, dictionary, x - 1, y - 1, string);
    flood(board, dictionary, x + 0, y - 1, string);
    flood(board, dictionary, x + 1, y - 1, string);

    /* Sorry guys, this following line is pretty much the entire
     * reason this whole thing is not implemented with a stack.
     *
     * I wish I had enough free-time to convert this to
     * tail-recursion; maybe someday... */
    visitedPoints_[x + y * board.getWidth()] = false;
}
}
