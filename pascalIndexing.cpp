#include <iostream>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>
#include "MyArr.h"
#include "math.h"

int main()
{
    FILE *pascalWrite;
    pascalWrite = fopen("pascalWrite.txt", "r+");

    // fseek(pascalWrite, 0L, SEEK_END);
    // long pascalWriteSize = (long)ceil(ftell(pascalWrite));
    // fseek(pascalWrite, 0L, SEEK_SET);

    // unsigned char *buff = new unsigned char[pascalWriteSize];
    // fread(buff, pascalWriteSize, 1, pascalWrite);

    MyArr<MyArr<mpz_t*>> pascal;
    MyArr<mpz_t*> pascal1D;

    // mpz_t one;
    // mpz_init(one);
    // mpz_set_ui(one, 1);
    // // pascal1D.push_back();
    // mpz_set(*pascal1D[0], one);

    mpz_t *prevLayer;

    for (int index = 1; index <= 1000; index++)
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
        }

        pascal.push_back(MyArr<mpz_t*>());
        for (int index2 = 0; index2 < index; index2++)
        {
            pascal[index2].push_back((mpz_t*)new mpz_t);
            mpz_init(*(pascal[index2][index-1-index2]));
            mpz_set(*(pascal[index2][index-1-index2]), layer[index2]);
        }

        for (int index2 = 1; index2 < ceil(index/2.0); index2++)
        {
            pascal1D.push_back((mpz_t*)new mpz_t);
            mpz_init(*pascal1D[pascal1D.size()-1]);
            mpz_set(*pascal1D[pascal1D.size()-1], layer[index2]);
        }

        prevLayer = layer;
    }

    // std::cout << pascal << std::endl;
    // std::cout << pascal1D << std::endl;

    for (unsigned long index = 0; index < pascal1D.size(); index++)
    {
        std::cout << *pascal1D[index] << std::endl;
    }

    // int good = 0;

    // for (int index = 4; index < 256*256; index++)
    // {
    //     for (int index2 = 0; index2 < pascal1D.size();index2++)
    //     {
    //         if (mpz_cmp_ui(pascal1D[index2], index) > 0)
    //         {
    //             continue;
    //         }
    //         mpz_t diff;
    //         mpz_init(diff);
    //         mpz_ui_sub(diff, index, pascal1D[index2]);
    //         for (int index3 = 0; index3 < pascal1D.size();index3++)
    //         {
    //             if (mpz_cmp(diff, pascal1D[index3]) == 0)
    //             {
    //                 // std::cout << index << " " << pascal1D[index3] << " " << pascal1D[index2] << std::endl;
    //                 good++;
    //                 goto next;
    //             }
    //         }
    //     }
    //     std::cout << index << std::endl;
    //     next:;
    // }

    // std::cout << good << std::endl;

    fclose(pascalWrite);


}