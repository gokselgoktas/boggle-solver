#ifndef BOGGLE_TRIE_INL
#define BOGGLE_TRIE_INL

namespace boggle {
size_t Trie::getCharacterCount() const
{
    return characterCount_;
}

size_t Trie::getWordCount() const
{
    return wordCount_;
}

std::shared_ptr<TrieNode> &Trie::getRootNode()
{
    return root_;
}

std::shared_ptr<TrieNode> const &Trie::getRootNode() const
{
    return root_;
}
}

#endif
