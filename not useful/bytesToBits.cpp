#include <gmpxx.h>
#include <iostream>

#define MOD 256
#define SIZE 67

//keep in mind, time to complete goes up when mod goes down

int bitOutput()
{
    int n = MOD-1;
    unsigned int count = 0;
    while (n)
    {
        count++;
        n >>= 1;
    }
    return count * SIZE;
}

int bitSizeOfFourToTheSize()
{
    mpz_t total;
    mpz_init(total);
    mpz_set_ui(total, 4);
    mpz_pow_ui(total, total, SIZE);
    mpz_sub_ui(total, total, 1);
    return mpz_sizeinbase(total, 2);
}

int bitSizeOfPossibilities()
{
    mpz_t total;
    mpz_init(total);
    mpz_set_ui(total, MOD);
    mpz_pow_ui(total, total, SIZE);
    mpz_sub_ui(total, total, 1);
    int ret = mpz_sizeinbase(total, 2);
    mpz_clear(total);
    return ret;
}

int bitSizeOfRepresentedAsBits()
{
    mpz_t total;
    mpz_init(total);
    mpz_set_ui(total, 2);
    mpz_pow_ui(total, total, MOD);
    mpz_sub_ui(total, total, 1);
    int ret = mpz_sizeinbase(total, 2);
    mpz_clear(total);
    return ret;
}

int bitSizeOfPositions()
{
    mpz_t total;
    mpz_init(total);
    mpz_set_ui(total, 2);
    for (int index = 3; index < SIZE + 1; index++)
    {
        mpz_mul_ui(total, total, index);
    }
    // std::cout << total << std::endl;
    mpz_sub_ui(total, total, 1);

    return mpz_sizeinbase(total, 2);
}

int bitSizeOfUnorganizedArray()
{
    mpz_t top;
    mpz_init(top);
    mpz_set_ui(top, 1);
    int topTimes = MOD + SIZE - 1;
    int times = SIZE - 1;
    for (int index = topTimes; index > topTimes - times - 1; index--)
    {
        mpz_mul_ui(top, top, index);
    }
    mpz_t bot;
    mpz_init(bot);
    mpz_set_ui(bot, 1);
    for (int index = 1; index < SIZE + 1; index++)
    {
        mpz_mul_ui(bot, bot, index);
    }

    mpz_t final;
    mpz_init(final);
    mpz_div(final, top, bot);
    mpz_sub_ui(final, final, 1);
    // std::cout << final << std::endl;
    int ret = mpz_sizeinbase(final, 2);
    return ret;
}

int main()
{
    std::cout << "output: " << bitOutput() << std::endl;
    std::cout << "unorganized array: " << bitSizeOfUnorganizedArray() * 2 + SIZE << std::endl;
    // std::cout << "odd or even choice: " << SIZE << std::endl;
    // std::cout << bitOutput() - (bitSizeOfUnorganizedArray() * 2 + SIZE) << std::endl;
    // std::cout << "order of options: " << bitSizeOfFourToTheSize() << std::endl;
    // std::cout << "positions: " << bitSizeOfPositions() << std::endl;
    // std::cout << bitSizeOfRepAsBits() << std::endl;
    // std::cout << bitSizeOfPossibilities() << std::endl;
}