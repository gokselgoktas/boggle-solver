#ifndef BOGGLE_DICTIONARY_INL
#define BOGGLE_DICTIONARY_INL

namespace boggle {
        Dictionary::Dictionary(std::string const &filename)
                : Dictionary(filename,
                        [](std::string const &) { return true; })
        {
        }

        inline TrieNode::Subnodes const &Dictionary::getWordRoots() const
        {
                return getRootNode()->getSubnodes();
        }
}

#endif
