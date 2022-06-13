#pragma once
#include "MyArr.h"
#include <iostream>
// #include <gmpxx.h>

class PascalTriangle
{
    static MyArr<MyArr<unsigned long>> _triangle;

    static unsigned long max(unsigned long in1, unsigned long in2)
    {
        if (in1 > in2)
        {
            return in1;
        }
        else
        {
            return in2;
        }
    }

    static void increaseSize(unsigned long xIn, unsigned long yIn)
    {
        const unsigned long larger = max(xIn, yIn)+1;

        if (larger > _triangle.size())
        {
            const unsigned long oldSize = _triangle.size();
            _triangle.setSize(larger);
            for (unsigned long index = 0; index < larger; index++)
            {
                _triangle[index].setSize(larger);
            }

            for (unsigned long index = oldSize; index < larger; index++)
            {
                _triangle[0][index] = 1;
                _triangle[index][0] = 1;
            }

            for (unsigned long x = max(oldSize, 1); x < larger; x++)
            {
                for (unsigned long y = 1; y < larger; y++)
                {
                    _triangle[x][y] = _triangle[x - 1][y] + _triangle[x][y - 1];
                }
            }
            
            for (unsigned long x = 1; x < oldSize; x++)
            {
                for (unsigned long y = max(oldSize, 1); y < larger; y++)
                {
                    _triangle[x][y] = _triangle[x - 1][y] + _triangle[x][y - 1];
                }
            }
            
        }
    }

    PascalTriangle() {}

public:
    static unsigned long &get(unsigned long x, unsigned long y)
    {
        increaseSize(x, y);
        return _triangle[x][y];
    }
};


