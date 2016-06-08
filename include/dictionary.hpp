#ifndef BOGGLE_DICTIONARY_HPP
#define BOGGLE_DICTIONARY_HPP

#include "trie.hpp"

#include <string>
#include <functional>

namespace boggle {
        class Dictionary : public Trie {
        public:
                Dictionary() = default;
                Dictionary(Dictionary const &) = default;
                Dictionary(Dictionary &&) = default;

                inline explicit Dictionary(std::string const &filename);
                Dictionary(std::string const &filename,
                        std::function<bool (std::string const &)> const &
                                filter);

                virtual ~Dictionary() = default;

                Dictionary &operator =(Dictionary const &) = default;
                Dictionary &operator =(Dictionary &&) = default;

                Dictionary clone() const;

                inline TrieNode::Subnodes const &getWordRoots() const;
        };
}

#include "dictionary.inl"
#endif
