#ifndef BOGGLE_BOGGLE_HPP
#define BOGGLE_BOGGLE_HPP

#include "api.hpp"

#include "board.hpp"
#include "dictionary.hpp"

#include "solver.hpp"

namespace boggle {
inline unsigned getScoreForWord(std::string const &word);
}

#include "boggle.inl"
#endif
