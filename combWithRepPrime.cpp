#include "MyArr.h"
#include <iostream>
// #include <memory.h>
#include "Pascal.h"

// #include <gmpxx.h>
// #include <gmp.h>

#define MOD 3
#define SIZE 4

void getCombWRepSetRec(long key, MyArr<long> &arr, long currentLevel, long pascalSum, long pascalYStart, long optionCount)
{
    for (long pascalY = pascalYStart; pascalY >= 0; pascalY--)
    {
        pascalSum += PascalTriangle::get(currentLevel, pascalY);
        if (key < pascalSum)
        {
            if (0 == currentLevel)
            {
                arr.push_back(optionCount - pascalY);
                return;
            }
            else
            {
                arr.push_back(optionCount - pascalY);
                getCombWRepSetRec(key, arr, currentLevel - 1, pascalSum - PascalTriangle::get(currentLevel, pascalY), pascalY, optionCount);
                return;
            }
        }
    }
}

MyArr<long> getCombWRepSet(long key, long size, long optionCount)
{
    MyArr<long> arr;
    getCombWRepSetRec(key, arr, size - 1, 0, optionCount - 1, optionCount - 1);
    return arr;
}

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

long sub(MyArr<long> arr)
{
    int ret = arr[0];
    for (int index = 1; index < arr.size(); index++)
    {
        if (index % 2 == 0)
        {
            ret += arr[index];
        }
        else
        {
            ret -= arr[index];
        }
    }
    return ret;
}

int main()
{

    for (long index = 0; index < 2829055; index++)
    {
        MyArr<long> set = getCombWRepSet(index, 3, 256);
        long setSum = sum(set);
        long setSub = sub(set);

        for (long index2 = 0; index2 < 2829055; index2++)
        {
            if(index2 == index)
            {
                continue;
            }

            MyArr<long> indexSet = getCombWRepSet(index2, 3, 256);
            if (sum(indexSet) == setSum && sub(indexSet) == setSub)
            {
                std::cout << indexSet << " " << set << std::endl;
            }
        }
    }

    return 0;
}