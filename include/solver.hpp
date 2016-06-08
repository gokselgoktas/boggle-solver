#ifndef BOGGLE_SOLVER_HPP
#define BOGGLE_SOLVER_HPP

#include "depth-first-search.hpp"
#include "dictionary-originated-search.hpp"
#include "optimized-search.hpp"

namespace boggle {
        template <class Technique>
        class Solver : public Technique {
        public:
                Solver() = default;
                ~Solver() = default;

                inline typename Technique::Results const &
                        solve(Board const &board,
                                Dictionary const &dictionary);

                inline typename Technique::Results const &
                        operator ()(Board const &board,
                                Dictionary const &dictionary);

                inline typename Technique::Results const &
                        getResults() const;
        };
}

#include "solver.inl"
#endif
