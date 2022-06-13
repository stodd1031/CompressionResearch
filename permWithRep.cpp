#include "MyArr.h"
#include <iostream>

#define SIZE 16
#define BASE 2

// void getPermWRepSetRec(long code, MyArr<long> &arr, MyArr<long> &optionsArr)
// {
//     unsigned long index = code / getPermWORepPossibilities(optionsArr.size() - 1);
//     arr.push_back(optionsArr[index]);
//     code = code % getPermWORepPossibilities(optionsArr.size() - 1);
//     optionsArr.remove(index);

//     if (optionsArr.size() != 1)
//     {
//         getPermWRepSetRec(code, arr, optionsArr);
//     }
//     else
//     {
//         arr.push_back(optionsArr[0]);
//     }
// }

MyArr<long> getPermWRepSet(long code, long size, long base)
{
    MyArr<long> set;

    long power = 1;

    for (int index = 1; index < size; index++)
    {
        power*= base;
    }

    for (int index = size; index> 0; index--)
    {
        long digitVal = code / power;
        set.push_back(digitVal);
        code -= digitVal * power;
        power /= base;
    }
    return set;
}

unsigned long getPermWRepPossibilities(unsigned long size, long base)
{
    unsigned long ret = base;
    for (int index = 2; index <= size; index++)
    {
        ret *= base;
    }
    return ret;
}

int main()
{
    long poss = getPermWRepPossibilities(SIZE, BASE);
    std::cout << poss << std::endl;

    std::cout << getPermWRepSet(poss-1, SIZE, BASE) << std::endl;

//     int wrongCount = 0;

//     for(int index =0 ; index < 256; index++)
//     {
//         for (int code =0; code < poss; code++)
//         {
//             MyArr<long> set = getPermWRepSet(code, SIZE, BASE);
//             int sum = 0;
//             for (int index2 = 0; index2 < set.size(); index2++)
//             {
//                 sum += set[index2] *set[index2];
//             }
//             if (sum == index)
//             {
//                 // std::cout << index << std::endl;
//                 goto succeed;
//             }
//         }
//         wrongCount++;
// std::cout << index << std::endl;
//         succeed:;
//     }
//     std::cout << std::endl << wrongCount << std::endl;
}