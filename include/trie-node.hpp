#ifndef BOGGLE_TRIE_NODE_HPP
#define BOGGLE_TRIE_NODE_HPP

#include <memory>
#include <unordered_map>

namespace boggle {
        class TrieNode {
                friend class Trie;
                friend class Dictionary;

        public:
                typedef std::unordered_map<char, std::shared_ptr<TrieNode>>
                        Subnodes;

        public:
                TrieNode() = default;
                TrieNode(TrieNode const &) = default;
                TrieNode(TrieNode &&) = default;

                ~TrieNode() = default;

                TrieNode &operator =(TrieNode const &) = default;
                TrieNode &operator =(TrieNode &&) = default;

                std::shared_ptr<TrieNode> createSubnode(char key);
                std::shared_ptr<TrieNode> findSubnode(char key) const;

                inline bool isWordBoundary() const;

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
                inline size_t getDependencyCount() const;
#endif

                inline Subnodes &getSubnodes();
                inline Subnodes const &getSubnodes() const;

                inline size_t getSubnodeCount() const;

        private:
                Subnodes subnodes_;

                bool isWordBoundary_ = false;

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
                size_t dependencyCount_ = 0;
#endif
        };
}

#include "trie-node.inl"
#endif
