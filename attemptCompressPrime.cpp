#include <math.h>
#include "MyArr.h"
#include <stdio.h>
#include <iostream>

#define TARGET 4294967296
// #define TARGET 10
#define PRIME_COUNT 203280221

// https://www.hackmath.net/en/calculator/combinations-and-permutations?n=7&k=8&order=0&repeat=1

long getMaxNum(long size, long optionCount)
{
    int numberCount;
    if (optionCount - 1 < size)
    {
        numberCount = optionCount - 1;
    }
    else
    {
        numberCount = size;
    }

    int start = size + optionCount - 1;
    int stop = start - numberCount;
    long ret = 1;
    for (int mult = start; mult > stop; mult--)
    {
        ret *= mult;
    }
    for (int div = 2; div <= numberCount; div++)
    {
        ret /= div;
    }
    return ret;
}

int getBits(long num)
{
    int ret = 0;
    while (num)
    {
        ret++;
        num = num >> 1;
    }
    return ret;
}

class Primes
{
    MyArr<unsigned int> primes;

public:
    Primes()
    {
        FILE *read;
        read = fopen("primes.bin", "rb+");
        // primes = new unsigned int[PRIME_COUNT];
        primes = MyArr<unsigned int>(PRIME_COUNT);
        fread(primes.getArrPointer(), PRIME_COUNT * sizeof(unsigned int), 1, read);
        fclose(read);
    }

    template <typename T>
    MyArr<T> getPrimeFactorIndexs(unsigned long num)
    {
        MyArr<T> primesIndex;

        unsigned int index = 0;
        // while numTest is divisible by any number other than 1
        while (num != 1)
        {
            if (num % primes[index] == 0)
            {
                num = num / primes[index];
                // append index of prime, rather than the value
                primesIndex.push_back(index);
            }
            else
            {
                index++;
            }
        }
        return primesIndex;
    }

    template <typename T>
    MyArr<T> getPrimeFactors(unsigned long num)
    {
        MyArr<T> primesIndex;

        unsigned int index = 0;
        // while numTest is divisible by any number other than 1
        while (num != 1)
        {
            if (num % primes[index] == 0)
            {
                num = num / primes[index];
                // append index of prime, rather than the value
                primesIndex.push_back(primes[index]);
            }
            else
            {
                index++;
            }
        }
        return primesIndex;
    }

    unsigned int &operator[](const unsigned long index)
    {
        // if (index < size)
        {
            return primes[index];
        }
    }
};

struct PrimeStruct
{
    unsigned char size = 0;
    unsigned int num;
    unsigned int *primes;

    PrimeStruct(unsigned char primesSize)
    {
        size = primesSize;
        primes = new unsigned int[primesSize];
    }
};

inline long min(long in1, long in2)
{
    if (in1 < in2)
    {
        return in1;
    }
    else
    {
        return in2;
    }
}

int main()
{
    Primes primes;

    FILE *toBeCompress;
    toBeCompress = fopen("test.txt", "rb+");

    fseek(toBeCompress, 0L, SEEK_END);
    long toBeCompressSize = (long)ceil(ftell(toBeCompress) / 4);
    fseek(toBeCompress, 0L, SEEK_SET);

    int largest = 0;
    long largestNum = 0;

    MyArr<unsigned int> primeFactors;
    MyArr<unsigned int> prevPrimeFactors = primes.getPrimeFactorIndexs<unsigned int>(4);

    int size = 0;
    int biggestPrime = 0;
    int amount = 0;

    for (long index = 5; index < 256 * 256; index++)
    {
        primeFactors = primes.getPrimeFactorIndexs<unsigned int>(index);

        if (primeFactors.size() > prevPrimeFactors.size())
        {
            if (primeFactors.size() > largest)
            {
                largest = primeFactors.size();
                std::cout << primeFactors.size() << std::endl;
            }
            if (primeFactors[primeFactors.size() - 1] > largestNum)
            {
                largestNum = primeFactors[primeFactors.size() - 1];
                std::cout << largestNum << std::endl;
                amount++;
                // std::cout << biggestPrime << std::endl;
            }
        }
        else
        {
            if (prevPrimeFactors.size() > largest)
            {
                largest = prevPrimeFactors.size();
                std::cout << prevPrimeFactors.size() << std::endl;
            }
            if (prevPrimeFactors[prevPrimeFactors.size() - 1] > largestNum)
            {
                largestNum = prevPrimeFactors[prevPrimeFactors.size() - 1];
                std::cout << largestNum << std::endl;
                amount++;
                // std::cout << biggestPrime << std::endl;
            }
        }

        

        // size = min(primeFactors.size(), prevPrimeFactors.size());
        // biggestPrime = min(primeFactors[primeFactors.size() - 1], prevPrimeFactors[primeFactors.size() - 1]);

        // if (biggestPrime > largestNum)
        // {
        //     largestNum = biggestPrime;
        //     std::cout << largestNum << std::endl;
        //     // std::cout << biggestPrime << std::endl;
        // }

        // if (size > largest)
        // {
        //     largest = size;
        //     std::cout << size << std::endl;
        // }

        prevPrimeFactors = primeFactors;
    }

    std::cout << amount << std::endl;

    // std::cout << largest << std::endl;
    // std::cout << largestNum << std::endl;

    // unsigned int buff[toBeCompressSize];
    // memset(buff, 0, sizeof(unsigned int) * toBeCompressSize);

    // fread(buff, toBeCompressSize*sizeof(unsigned int), 1, toBeCompress);

    // for (int index = 0; index < toBeCompressSize; index++)
    // {
    //     std::cout << "num:" << buff[index] << "\t" << std::flush;

    //     MyArr<unsigned int> primesIndex = primes.getPrimeFactorIndexs(buff[index]);

    //     for (int index = 0; index < primesIndex.size(); index++)
    //     {
    //         std::cout << primesIndex[index] << ":" << primes[primesIndex[index]] << "\t" << std::flush;
    //     }
    //     std::cout << std::endl;
    // }

    // BREAK

    // // loop through numbers up to target to prime factorize
    // for (long num = 2; num < TARGET; num++)
    // {
    //     MyArr<unsigned int> primesIndex;
    //     long numTest = num;

    //     unsigned int index = 0;
    //     // while numTest is divisible by any number other than 1
    //     while(numTest != 1)
    //     {
    //         if (numTest % primes[index] == 0)
    //         {
    //             numTest = numTest / primes[index];
    //             // append index of prime, rather than the value
    //             primesIndex.push_back(index);
    //         }
    //         else
    //         {
    //             index++;
    //         }
    //     }
    //     // std::cout << "num:" << num << "   " << std::flush;
    //     // for (int index = 0; index < primesIndex.size(); index++)
    //     // {
    //     //     std::cout << primesIndex[0] << ":" << primes[primesIndex[0]] << " " << std::flush;
    //     // }
    //     // std::cout << std::endl;
    // }

    fclose(toBeCompress);
}