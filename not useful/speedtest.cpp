#include <iostream>
#include <vector>
#include <memory.h>
#include <array>
#include <ostream>

#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <unistd.h>

#include <future>
#include <chrono>
#include <thread>
#include <gmpxx.h>


void removeItem(int index, char *array, int size)
{
    // std::cout << size << " " << index << std::endl;
    memcpy(array + index, array + 1 + index, (size - 1 - index) * sizeof(char));
}

void addItem(int index, char item, char *array, int size)
{

    if (size == index)
    {
        array[index] = item;
        return;
    }
    else
    {
        int endCopy = array[size - 1];
        memcpy(array + 1 + index, array + index, (size - index - 1) * sizeof(char));
        array[size] = endCopy;
        array[index] = item;
    }

    // int arrEnd[size-index];
    // memcpy(arrEnd, array + index, (size - index) * sizeof(int));
    // memcpy(array + 1 + index, arrEnd, (size - index) * sizeof(int));
    // array[index] = item;

    // for (int index2 = 0; index2 < size-index; index2++)
    // {
    //     array[size-index2] = array[size-index2-1];
    // }
    // array[index] = item;
}



int main()
{

    char testArr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

    long first = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


    int num = 0;
    for (int index = 0; index < 10000000; index++)
    {
        if (num > 15)
        {
            num = num % 16;
        }
        std::cout << num << std::endl;
        num++;
        
    }

    
    long second = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::cout << (second-first)/1000000.0f << std::endl;
    return 0;
}