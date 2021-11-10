#pragma once

struct Position
{
    unsigned int x, y, z;

    Position()
        : x(0), y(0), z(0) {}

    Position(unsigned int x, unsigned int y, unsigned int z)
        : x(x), y(y), z(z) {}
    
};

// 12