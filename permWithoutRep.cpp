#include "MyArr.h"
// #include "Pascal.h"
#include <iostream>

#define SIZE 10
// #define OPTIONS 8
// #define BIGGEST_CHANGE (256UL * 256 *256 * 256- 1)
#define BIGGEST_CHANGE (256UL * 256 - 1)
// #define BIGGEST_CHANGE (256 * 256 - 1)

unsigned long getPermWORepPossibilities(unsigned long size)
{
    unsigned long ret = 1;
    for (int index = 2; index <= size; index++)
    {
        ret *= index;
    }
    return ret;
}

void getPermWORepSetRec(long code, MyArr<long> &arr, MyArr<long> &optionsArr)
{
    unsigned long index = code / getPermWORepPossibilities(optionsArr.size() - 1);
    arr.push_back(optionsArr[index]);
    code = code % getPermWORepPossibilities(optionsArr.size() - 1);
    optionsArr.remove(index);

    if (optionsArr.size() != 1)
    {
        getPermWORepSetRec(code, arr, optionsArr);
    }
    else
    {
        arr.push_back(optionsArr[0]);
    }
}

MyArr<long> getPermWORepSet(long code, long size)
{
    MyArr<long> set;
    MyArr<long> optionsArr;
    for (int index = 0; index < size; index++)
    {
        optionsArr.push_back(index);
    }
    getPermWORepSetRec(code, set, optionsArr);

    return set;
}

long sum(MyArr<long> arr)
{
    int ret = arr[0];
    for (int index = 1; index < arr.size(); index++)
    {
        if (index % 2 == 0)
        {
            ret -= arr[index];
        }
        else
        {
            ret += arr[index];
        }
    }
    return ret;
}

int main()
{

    unsigned long poss = getPermWORepPossibilities(SIZE);

    // std::cout << sum(getSet(0, SIZE)) << std::endl;

    for(int index =0 ; index < 256; index++)
    {
        for (int code =0; code < poss; code++)
        {
            MyArr<long> set = getPermWORepSet(code, SIZE);
            int sum = 0;
            for (int index2 = 0; index2 < set.size(); index2++)
            {
                sum += set[index2] *set[index2];
            }
            if (sum == index)
            {
                std::cout << index << std::endl;
                break;
            }
        }
    }


    // for (int index = 0; index < poss; index++)
    // {
    //     long base = sum(getPermWORepSet(index, SIZE));
    //     std::cout << index << " " << base << std::endl;
    //     for (int index2 = 0; index2 < poss; index2++)
    //     {
    //         if (index2 == index)
    //         {
    //             continue;
    //         }
    //         if (sum(getPermWORepSet(index2, SIZE)) == base)
    //         {
    //             std::cout << getPermWORepSet(index2, SIZE) << std::endl;
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    // unsigned long total = 0;

    // MyArr<long> ordered = getSet(0, SIZE);

    // for (unsigned long index = 0; index < poss; index++)
    // {
    //     MyArr<long> start = getSet(index, SIZE);
    //     std::cout << start << std::endl;

    //     MyArr<long> copy = ordered;
    //     int count = 0;

    //     unsigned long num = 0;
    //     unsigned long prevIndex = 0;

    //     while (1)
    //     {
    //         if (copy.size() == 0)
    //         {
    //             break;
    //         }
    //         else if (start[count] == copy[(num + prevIndex) % copy.size()])
    //         {
    //             // prevIndex = (num + prevIndex) % copy.size();
    //             copy.remove((num + prevIndex) % copy.size());
    //             count++;
    //         }
    //         else if (num > BIGGEST_CHANGE)
    //         {
    //             goto next;
    //         }
    //         else
    //         {
    //             copy = ordered;
    //             count = 0;
    //             num++;
    //         }
    //     }
    //     // std::cout << index << " " << num << " " << start << std::endl;
    //     total++;
    // next:;
    // }

    // std::cout << total << " " << poss << std::endl;

    //     MyArr<long> start = getSet(1, SIZE);

    //     MyArr<long> copy = ordered;
    //     int count = 0;

    //     unsigned long num = 0;
    //     unsigned long prevIndex = 0;

    //     while (1)
    //     {
    //         if (copy.size() == 0)
    //         {
    //             break;
    //         }
    //         else if (start[count] == copy[(num + prevIndex) % copy.size()])
    //         {
    //             copy.remove((num + prevIndex) % copy.size());
    //             // prevIndex = (num + prevIndex) % copy.size();
    //             count++;
    //             if (count > SIZE-2)
    //             {
    //                 std::cout << num << std::endl;
    //             }
    //         }
    //         else if (num > BIGGEST_CHANGE)
    //         {
    //             goto next;
    //         }
    //         else
    //         {
    //             copy = ordered;
    //             count = 0;
    //             num++;
    //         }
    //     }
    //     std::cout << 1 << " " << num << std::endl;
    // next:;
}