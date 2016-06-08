#ifndef BOGGLE_BOARD_INL
#define BOGGLE_BOARD_INL

namespace boggle {
        unsigned Board::getWidth() const
        {
                return width_;
        }

        unsigned Board::getHeight() const
        {
                return height_;
        }

        char Board::getValue(int x, int y) const
        {
                if (doesContainPoint(x, y) == false) {
                        return '\0';
                }

                return data_[x + y * width_];
        }

        char Board::operator [](std::pair<int, int> const &coordinates) const
        {
                return getValue(coordinates.first, coordinates.second);
        }

        bool Board::hasValue(char value) const
        {
                return (data_.find(value) != std::string::npos);
        }

        bool Board::isValid() const
        {
                return isValid_;
        }

        bool Board::doesContainPoint(int x, int y) const
        {
                unsigned k = static_cast<unsigned>(x);
                unsigned l = static_cast<unsigned>(y);

                if (k >= width_ || l >= height_) {
                        return false;
                }

                return true;
        }

        bool Board::doesContainPoint(
                std::pair<int, int> const &coordinates) const
        {
                return doesContainPoint(coordinates.first, coordinates.second);
        }
}

#endif
