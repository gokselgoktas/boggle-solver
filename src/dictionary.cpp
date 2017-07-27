#include "dictionary.hpp"

#include <stack>

#include <fstream>
#include <iostream>

namespace boggle {
Dictionary::Dictionary(std::string const &filename,
    std::function<bool(std::string const &)> const &filter)
{
    std::ifstream file(filename);

    if (file.good() == false) {
        return;
    }

    while (file.eof() == false) {
        std::string word;
        file >> word;

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (filter(word) == true) {
            insert(word);
        }
    }
}

Dictionary Dictionary::clone() const
{
    Dictionary result;

    std::stack<std::shared_ptr<TrieNode>> stack;

    stack.push(result.root_);
    stack.push(root_);

    while (stack.empty() == false) {
        auto i = stack.top();
        stack.pop();

        auto k = stack.top();
        stack.pop();

        for (auto l : i->getSubnodes()) {
            auto r = k->createSubnode(l.first);

            if (l.second->isWordBoundary()) {
                r->isWordBoundary_ = true;
            }

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
            r->dependencyCount_ = l.second->dependencyCount_;
#endif

            stack.push(r);
            stack.push(l.second);
        }
    }

    result.characterCount_ = characterCount_;
    result.wordCount_ = wordCount_;

    return result;
}
}
