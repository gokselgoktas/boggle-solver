#include "trie.hpp"

#include <iostream>

namespace boggle {
Trie::Trie() : root_{std::make_shared<TrieNode>()}
{
}

void Trie::insert(std::string const &string)
{
    if (string.empty()) {
        return;
    }

    auto i = root_;
    auto k = string.cbegin();

    for (; k != string.cend(); ++k) {
        if (std::isalpha(*k) == false) {
            continue;
        }

        auto subnode = i->findSubnode(*k);

        if (subnode == nullptr) {
            break;
        }

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
        ++(subnode->dependencyCount_);
#endif

        i = subnode;
    }

    for (; k != string.cend(); ++k) {
        if (std::isalpha(*k) == false) {
            continue;
        }

        i = i->createSubnode(*k);

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
        ++(i->dependencyCount_);
#endif

        ++characterCount_;
    }

    i->isWordBoundary_ = true;
    ++wordCount_;
}

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
void Trie::prune(std::string const &string)
{
    if (string.empty() || hasWord(string) == false) {
        return;
    }

    auto i = root_;

    for (auto k : string) {
        auto subnode = i->findSubnode(k);

        if (subnode->dependencyCount_ > 0) {
            --(subnode->dependencyCount_);
        }
    }
}
#endif

bool Trie::hasWordPrefix(std::string const &string) const
{
    if (string.empty()) {
        return true;
    }

    auto i = root_;

    for (auto k : string) {
        auto subnode = i->findSubnode(k);

        if (subnode == nullptr) {
            return false;
        }

        i = subnode;
    }

    return true;
}

bool Trie::hasWord(std::string const &string) const
{
    if (string.empty()) {
        return root_->isWordBoundary();
    }

    auto i = root_;

    for (auto k : string) {
        auto subnode = i->findSubnode(k);

        if (subnode == nullptr) {
            return false;
        }

        i = subnode;
    }

    return i->isWordBoundary();
}
}
