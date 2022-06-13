#include <iostream>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>
#include "MyArr.h"

int main()
{
    FILE *pascalWrite;
    pascalWrite = fopen("pascalWriteNoWhiteSpace.txt", "w+");

    mpz_t *start = new mpz_t[2];
    mpz_init(start[0]);
    mpz_init(start[1]);
    mpz_set_ui(start[0], 1);
    mpz_set_ui(start[1], 1);

    fwrite("1", 1, 1, pascalWrite);   

    mpz_t *prevLayer = start;

    for (int index = 2; index < 1000; index++)
    {
        mpz_t *layer = new mpz_t[index];
        for (int index2 = 0; index2 < index; index2++)
        {
            mpz_init(layer[index2]);
        }
        mpz_set_ui(layer[0], 1);
        mpz_set_ui(layer[index - 1], 1);

        for (int index2 = 1; index2 < index - 1; index2++)
        {
            mpz_add(layer[index2], prevLayer[index2 - 1], prevLayer[index2]);
        }

        for (int index2 = 0; index2 < index; index2++)
        {
            int numDigits = mpz_sizeinbase(layer[index2], 10);

            char buf[numDigits + 1];

            mpz_get_str(buf, 10, layer[index2]);
            numDigits = strlen(buf);
            buf[numDigits] = ' ';

            fwrite(buf, numDigits, 1, pascalWrite);
        }

        // fwrite("\n", 1, 1, pascalWrite);

        for (int index2 = 0; index2 < index - 1; index2++)
        {
            mpz_clear(prevLayer[index2]);
        }

        delete[] prevLayer;
        prevLayer = layer;
    }

    // std::cout << pascal << std::endl;





    fclose(pascalWrite);


}