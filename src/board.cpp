#include "board.hpp"

#include <algorithm>
#include <iostream>

namespace boggle {
        Board::Board(std::string const &data, unsigned width, unsigned height)
        {
                if (data.empty() || data.size() < width * height) {
                        return;
                }

                for (auto i : data) {
                        if (std::isalpha(i) == false)
                                return;
                }

                data_ = data;

                std::transform(data_.begin(), data_.end(), data_.begin(),
                        ::tolower);

                width_ = width;
                height_ = height;

                isValid_ = true;
        }

        std::vector<std::pair<int, int>> Board::findValue(char value) const
        {
                std::vector<std::pair<int, int>> result;
                result.reserve(width_ * height_);

                std::string::size_type i = data_.find(value);

                while (i != std::string::npos && i < width_ * height_) {
                        std::pair<int, int> coordinates {
                                i % width_, i / width_
                        };

                        if (doesContainPoint(coordinates)) {
                                result.push_back(coordinates);
                        }

                        i = data_.find(value, i + 1);
                }

                return result;
        }

        std::ostream &operator <<(std::ostream &stream, Board const &board)
        {
                unsigned const separatorWidth = 4 * board.getWidth() + 1;

                for (unsigned x = 0; x < separatorWidth; ++x) {
                        stream << '-';
                }

                stream << '\n';

                for (unsigned y = 0; y < board.getHeight(); ++y) {
                        stream << "| ";

                        for (unsigned x = 0; x < board.getWidth(); ++x) {
                                stream << board[{ x, y }] << " | ";
                        }

                        stream << '\n';

                        for (unsigned x = 0; x < separatorWidth; ++x) {
                                stream << '-';
                        }

                        if (y < board.getHeight() - 1) {
                                stream << '\n';
                        }
                }

                return stream;
        }
}
