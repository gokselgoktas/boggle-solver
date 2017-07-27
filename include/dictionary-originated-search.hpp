#ifndef BOGGLE_DICTIONARY_ORIGINATED_SEARCH
#define BOGGLE_DICTIONARY_ORIGINATED_SEARCH

#include "board.hpp"
#include "dictionary.hpp"

#include <unordered_set>

namespace boggle {
struct DictionaryOriginatedSearch {
    typedef std::unordered_set<std::string> Results;

    Results const &operator()(Board const &board, Dictionary const &dictionary);

private:
    void traverse(Board const &board, std::shared_ptr<TrieNode> const &trieNode,
        std::string &string);

    bool search(Board const &board, std::string const &string);

    bool flood(Board const &board, int x, int y, std::string const &string,
        std::string::size_type i = 0);

#ifndef NDEBUG
private:
    void visualize(Board const &board) const;
#endif

protected:
    Results results_;

private:
    std::vector<bool> visitedPoints_;
};
}

#endif
