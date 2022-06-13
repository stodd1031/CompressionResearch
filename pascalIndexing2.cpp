#include <iostream>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>
#include "MyArr.h"
#include "math.h"

#define DEPTH 15
#define SIZE 80
#define BITS 119

// 4 33 32 bits
// 5 20 32 bits

// 5 35 40 bits
// 6 24 40 bits

// 5 63 48 bits
// 6 38 48 bits

bool setExistsRec(mpz_t num, mpz_t test, const int depth, MyArr<mpz_t *> &pascal1D, int currentLevel, unsigned long start)
{
    if (depth == currentLevel)
    {
        return 0;
    }
    const int levelFlipped = depth-currentLevel;
    for (unsigned long index = start; index < pascal1D.size(); index++)
    {
        // mpz_set(test, *pascal1D[index]);
        // mpz_mul_ui(test, test, levelFlipped);

        mpz_mul_ui(test, *pascal1D[index], depth-currentLevel);

        if(mpz_cmp(num, test) > 0)
        {
            return 0;
        }

        if (mpz_cmp(num, *pascal1D[index]) > 0)
        {
            mpz_sub(num, num, *pascal1D[index]);
            bool succeed = setExistsRec(num, test, depth, pascal1D, currentLevel + 1, index);
            mpz_add(num, num, *pascal1D[index]);
            if (succeed)
            {
                return 1;
            }
        }
        else if(mpz_cmp(num, *pascal1D[index]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

bool setExists(mpz_t num, int depth, MyArr<mpz_t *> &pascal1D)
{
    mpz_t test;
    mpz_init(test);

    return setExistsRec(num, test, depth, pascal1D, 0, 0);
}

bool orderCompare(mpz_t *op1, mpz_t *op2)
{
    if (mpz_cmp(*op1, *op2) > 0)
    {
        return 1;
    }
    return 0;
}

int main()
{

    std::cout << "select: " << DEPTH << " pascal size: " << SIZE << " bits: " << BITS << std::endl;

    MyArr<MyArr<mpz_t *>> pascal;
    MyArr<mpz_t *> pascal1D;

    for (unsigned long index = 0; index < SIZE; index++)
    {
        pascal.push_back(MyArr<mpz_t *>());
        for (unsigned long index2 = 0; index2 < SIZE; index2++)
        {
            pascal[index].push_back((mpz_t *)new mpz_t);
            mpz_init(*pascal[index][index2]);
        }
    }

    for (unsigned long index = 0; index < SIZE; index++)
    {
        mpz_set_ui(*pascal[0][index], 1);
        mpz_set_ui(*pascal[index][0], 1);
    }

    for (unsigned long index = 1; index < SIZE; index++)
    {
        for (unsigned long index2 = 1; index2 < SIZE; index2++)
        {
            mpz_add(*pascal[index][index2], *pascal[index][index2 - 1], *pascal[index - 1][index2]);
        }
    }

    for (unsigned long index = SIZE - 1; index > 0; index--)
    {
        for (unsigned long index2 = SIZE - 1; index2 >= index; index2--)
        {
            pascal1D.push_back(pascal[index2][index]);
        }
    }

    pascal1D.push_back((mpz_t *)new mpz_t);
    mpz_init(*pascal1D[pascal1D.size() - 1]);
    mpz_set_ui(*pascal1D[pascal1D.size() - 1], 1);
    pascal1D.push_back((mpz_t *)new mpz_t);
    mpz_init(*pascal1D[pascal1D.size() - 1]);
    mpz_set_ui(*pascal1D[pascal1D.size() - 1], 0);


    pascal1D.orderWithFunc(orderCompare);
    pascal1D.flip();

    // std::cout << *pascal[SIZE-1][SIZE-1] << std::endl;

    // for (unsigned long index = 0; index < pascal1D.size(); index++)
    // {
    //     std::cout << *pascal1D[index] << std::endl;
    // }
    std::cout << "biggest pascal num: " << *pascal1D[0] << std::endl;
    std::cout << "pascal array size: " << pascal1D.size() << std::endl;

    mpz_t num;
    mpz_init(num);
    mpz_set_ui(num, 2);
    mpz_pow_ui(num, num, BITS);
    mpz_sub_ui(num, num, 1);

    // while (mpz_cmp_ui(num, 256*256) < 0)
    while (1)
    {
        std::cout << "num: " << num << std::endl;
        if (!setExists(num, DEPTH, pascal1D))
        {
            break;
        }
        // mpz_add_ui(num, num, 1);
        mpz_sub_ui(num, num, 1);
    }
}