# Boggle Solver
A dumb, single-threaded Boggle solver

## What is Boggle?
According to the super reliable source of Wikipedia, Boggle is a word game
played using a plastic grid of lettered dice, in which players attempt to find
words in sequences of adjacent letters.

## How does it work?
If it isn't obvious by now, this whole thing has depth-first search *(DFS)*
written all over it. The solver works by constructing a trie for representing
its dictionary, it then performs DFS on the board while pruning away
impossible, or readily explored paths from the trie.

