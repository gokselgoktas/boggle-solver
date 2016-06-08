#include "trie-node.hpp"

namespace boggle {
        std::shared_ptr<TrieNode> TrieNode::createSubnode(char key)
        {
                key = tolower(key);

                subnodes_[key] = std::make_shared<TrieNode>();
                return subnodes_[key];
        }

        std::shared_ptr<TrieNode> TrieNode::findSubnode(char key) const
        {
                auto i = subnodes_.find(tolower(key));

                if (i == subnodes_.end()) {
                        return nullptr;
                }

                return i->second;
        }
}
