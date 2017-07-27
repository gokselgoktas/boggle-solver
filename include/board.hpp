#ifndef BOGGLE_BOARD_HPP
#define BOGGLE_BOARD_HPP

#include <utility>

#include <string>
#include <vector>

#include <ostream>

namespace boggle {
class Board {
public:
    Board(std::string const &data, unsigned width, unsigned height);

    ~Board() = default;

    inline unsigned getWidth() const;
    inline unsigned getHeight() const;

    inline char getValue(int x, int y) const;
    inline char operator[](std::pair<int, int> const &coordinates) const;

    inline bool hasValue(char value) const;
    std::vector<std::pair<int, int>> findValue(char value) const;

    inline bool isValid() const;

    inline bool doesContainPoint(int x, int y) const;
    inline bool doesContainPoint(std::pair<int, int> const &coordinates) const;

private:
    Board() = delete;
    Board(Board const &) = delete;
    Board(Board &&) = delete;

    Board &operator=(Board const &) = delete;
    Board &operator=(Board &&) = delete;

private:
    std::string data_;

    unsigned width_ = 0;
    unsigned height_ = 0;

    bool isValid_ = false;
};

std::ostream &operator<<(std::ostream &stream, Board const &board);
}

#include "board.inl"
#endif
