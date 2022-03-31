#ifndef _POSITION_HPP_
#define _POSITION_HPP_

#include <ostream>
#include "Direction.hpp"

class Position {
    private:
        int x;
        int y;
    public:
        Position(int x = 0, int y = 0);
        int getX() const;
        int getY() const;
        Position operator+(const Direction& dir);
        void operator+=(const Direction& dir);
        std::string to_str() const;
        friend std::ostream& operator<<(std::ostream& out, const Position& pos);
};

#endif