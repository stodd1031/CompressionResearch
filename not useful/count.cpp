#include <gmpxx.h>
#include <iostream>
#include <cmath>


int main()
{
    int size = 4567;
    int mod = pow(2, 16);
    // int mod = 256;

    int returnSize = ((int)log2(mod-1)+1) * size;

    int top = size+mod - 1;
    int bot = mod -1;

    // unsigned long long botDiv = 1;
    mpz_t botDiv;
    mpz_init(botDiv);
    mpz_set_ui(botDiv, 1);



    for (int index = 2; index <= bot; index++)
    {
        // botDiv *= index;
        mpz_mul_ui(botDiv, botDiv, index);
    }

        mpz_t topDiv;
    mpz_init(topDiv);
    mpz_set_ui(topDiv, 1);

    for (int index = top; index > top-bot; index--)
    {
        mpz_mul_ui(topDiv, topDiv, index);
    }

    for (int index = 0; index < mod-1; index++)
    {

    }

    mpz_t result;
    mpz_init(result);
    mpz_div(result, topDiv, botDiv);
    mpz_sub_ui(result, result, 1);
    // mpz_set_ui(result, 1);

    // std::cout << topDiv << std::endl;
    // std::cout << botDiv << std::endl;
    std::cout << "input 3 " << mpz_sizeinbase(result, 2) * 3<< std::endl;
    std::cout << "output  " << returnSize << std::endl;
    
}