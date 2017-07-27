#ifndef BOGGLE_TRIE_NODE_INL
#define BOGGLE_TRIE_NODE_INL

namespace boggle {
bool TrieNode::isWordBoundary() const
{
    return isWordBoundary_;
}

#ifdef BOGGLE_COUNT_NODE_DEPENDENCIES
size_t TrieNode::getDependencyCount() const
{
    return dependencyCount_;
}
#endif

TrieNode::Subnodes &TrieNode::getSubnodes()
{
    return subnodes_;
}

TrieNode::Subnodes const &TrieNode::getSubnodes() const
{
    return subnodes_;
}

size_t TrieNode::getSubnodeCount() const
{
    return subnodes_.size();
}
}

#endif
