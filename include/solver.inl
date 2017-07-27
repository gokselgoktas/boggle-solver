#ifndef BOGGLE_SOLVER_INL
#define BOGGLE_SOLVER_INL

namespace boggle {
template <class Technique>
typename Technique::Results const &Solver<Technique>::solve(
    Board const &board, Dictionary const &dictionary)
{
    return Technique::operator()(board, dictionary);
}

template <class Technique>
typename Technique::Results const &Solver<Technique>::operator()(
    Board const &board, Dictionary const &dictionary)
{
    return Technique::operator()(board, dictionary);
}

template <class Technique>
typename Technique::Results const &Solver<Technique>::getResults() const
{
    return Technique::results_;
}
}

#endif
