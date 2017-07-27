#ifndef BOGGLE_BOGGLE_INL
#define BOGGLE_BOGGLE_INL

namespace boggle {
/* I honestly have no clue why I did this, but I felt like writing this
 * without an if, and it turned out to be even worse readability wise.
 *
 * Well, I still think it's funny, so I am keeping it.  Also, damn the
 * guy who decided to make Boggle scoring non-linear! */
unsigned getScoreForWord(std::string const &word)
{
    return std::max(std::min(static_cast<int>(word.size() - 3) +
                            (word.size() == 7) + (6 * (word.size() > 7)),
                        11),
        1);
}
}

#endif
