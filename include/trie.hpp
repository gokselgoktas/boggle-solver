#ifndef BOGGLE_TRIE_HPP
#define BOGGLE_TRIE_HPP

#include "trie-node.hpp"

#include <algorithm>
#include <string>

namespace boggle {
class Trie {
public:
    Trie();
    Trie(Trie const &) = default;
    Trie(Trie &&) = default;

    virtual ~Trie() = default;

    Trie &operator=(Trie const &) = default;
    Trie &operator=(Trie &&) = default;

    void insert(std::string const &string);

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
    void prune(std::string const &string);
#endif

    bool hasWordPrefix(std::string const &string) const;
    bool hasWord(std::string const &string) const;

    inline std::shared_ptr<TrieNode> &getRootNode();
    inline std::shared_ptr<TrieNode> const &getRootNode() const;

    inline size_t getCharacterCount() const;
    inline size_t getWordCount() const;

protected:
    std::shared_ptr<TrieNode> root_;

    size_t characterCount_ = 0;
    size_t wordCount_ = 0;
};
}

#include "trie.inl"
#endif
