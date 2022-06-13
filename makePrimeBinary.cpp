#include "MyArr.h"
#include "math.h"
#include <iostream>
#include "stdio.h"

#define INCR_SIZE (1000 * 1000)
#define TARGET 4294967296

// #define MAKE_BINARY

int main()
{
#ifdef MAKE_BINARY
    FILE *clear;
    clear = fopen("primes.bin", "w");
    fclose(clear);

    FILE *write;
    write = fopen("primes.bin", "rb+");
#endif

    MyArr<unsigned int> primes;
    primes.push_back(2);
    primes.push_back(3);

    for (unsigned long num = 5; num < INCR_SIZE; num += 2)
    {
        unsigned long stop = sqrt(num);
        for (long index = 0; index < stop; index++)
        {
            if (num % primes[index] == 0)
            {
                goto next;
            }
        }
        primes.push_back(num);
    next:;
    }

    unsigned long num = INCR_SIZE;

    while (num < TARGET)
    {
        bool *primeOrNot = new bool[INCR_SIZE];
        memset(primeOrNot, 1, INCR_SIZE);

        unsigned long root = sqrt(num + INCR_SIZE) + 1;

        for (unsigned long index = 0; index < primes.size() && root > primes[index]; index++)
        {
            unsigned long start = primes[index] - ((num) % primes[index]);
            if (start == primes[index])
            {
                start = 0;
            }
            while (start < INCR_SIZE)
            {
                primeOrNot[start] = 0;
                start += primes[index];
            }
        }
        for (long index = 0; index < INCR_SIZE; index++)
        {
            if (primeOrNot[index])
            {
                primes.push_back(num + index);
            }
        }

        delete[] primeOrNot;
        num += INCR_SIZE;
    }

    while (primes[primes.size() - 1] < INCR_SIZE)
    {
        primes.pop_back();
    }

    std::cout << primes.size() << std::endl;

#ifdef MAKE_BINARY
    fwrite(primes.getArrPointer(), primes.size() * sizeof(unsigned int), 1, write);

    fclose(write);
#endif
}