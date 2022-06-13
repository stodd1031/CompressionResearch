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

#define keyLeftArr 0
#define keyBotArr 1
#define keyRightArr 2

#define THREADS 7

int total = 0;

class keysArr
{
public:
    int size;
    int numsSize = 0;
    int* hasArr;
    int* nums; // [0, 1, 2, 0 ,1] the amount of number index, 0 0s, 1 1, 2 2s, 0 3s, 1 4

    keysArr(int* numsIn, int sizeIn)
    {
        size = 0;
        hasArr = new int[sizeIn];
        nums = new int[sizeIn];
        numsSize = sizeIn;
        int hasIndex = 0;
        memcpy(nums, numsIn, sizeIn * sizeof(int));
        for (int index = 0; index < sizeIn; index++)
        {
            if (nums[index] > 0)
            {
                size += 1;
                hasArr[hasIndex] = index;
                hasIndex += 1;
            }
        }
    }

    bool has(int item)
    {
        for (int index = 0; index < size; index++)
        {
            if (hasArr[index] == item)
            {
                return 1;
            }
            // else if (has[index] > item)
            // {
            //     return 0;
            // }
        }
        return 0;
    }

    void add(int item)
    {
        for (int index = 0; index < size; index++)
        {
            if (hasArr[index] == item)
            {
                nums[item] += 1;
                return;
            }
            if (hasArr[index] > item)
            {
                for (int index2 = size + 1; index2 > index; index2--)
                {
                    hasArr[index2] = hasArr[index2 - 1];
                }
                hasArr[index] = item;
                size += 1;
                nums[item] += 1;
                return;
            }
        }
        hasArr[size] = item;
        nums[item] += 1;
        size += 1;
    }

    void remove(int item)
    {
        nums[item] -= 1;
        if (nums[item] == 0)
        {
            for (int index = 0; index < size; index++)
            {
                if (hasArr[index] == item)
                {
                    memcpy(hasArr + index, hasArr + index + 1, (size - index - 1) * sizeof(int));
                    break;
                }
            }
            size -= 1;
        }
    }

    void print()
    {
        std::cout << "size: " << size << std::endl;
        std::cout << "hasArr: " << std::flush;
        for (int index = 0; index < size; index++)
        {
            std::cout << hasArr[index] << " " << std::flush;
        }
        std::cout << std::endl
            << "nums: " << std::flush;
        for (int index = 0; index < numsSize; index++)
        {
            std::cout << nums[index] << " " << std::flush;
        }
        std::cout << std::endl;
    }
};

void nothing() {}

void displayChart(short** array, short size)
{
    for (short y = size - 1; y > -1; y--)
    {
        for (short x = 0; x < size; x++)
        {
            if (y > x)
            {
                std::cout << "\t" << std::flush;
            }
            else
            {
                std::cout << array[y][x] << "\t" << std::flush;
            }
            std::cout << std::endl;
        }
    }
}

void order(short*& arrayIn, short size, short mod)
{
    short finalArrayIndex = 0;
    short finalArray[size];
    short arrayCpy[size];
    memcpy(arrayCpy, arrayIn, size * sizeof(short));
    for (short index = 0; index < mod; index++)
    {
        for (short index2 = 0; index2 < size; index2++)
        {
            if (arrayCpy[index2] == index)
            {
                finalArray[finalArrayIndex] = index;
                finalArrayIndex += 1;
                arrayCpy[index2] = -1;
            }
        }
    }
    memcpy(arrayIn, finalArray, size * sizeof(short));
}

short binarySearch(short arr[], short l, short r, short x)
{
    if (r >= l)
    {
        short mid = l + (r - l) / 2;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return 1;

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
    return 0;
}

bool in(short item, short* arr, short size)
{
    return binarySearch(arr, 0, size - 1, item);
    // for (short index = 0; index < size; index++)
    // {
    //     if (item < arr[index])
    //     {
    //         return 0;
    //     }
    //     if (item == arr[index])
    //     {
    //         return 1;
    //     }
    // }
    // return 0;
}

bool in(std::array<short, 2> item, std::vector<std::array<short, 2>> arr)
{
    short count;
    for (short index = 0; index < arr.size(); index++)
    {
        count = 0;
        for (short index2 = 0; index2 < 2; index2++)
        {
            if (item[index2] == arr[index][index2])
            {
                count += 1;
            }
        }
        if (count == 2)
        {
            return 1;
        }
    }
    return 0;
}

bool checkRight(short* rightArr, short* keyRightArray, short size)
{
    short keyRightArrayCpy[size];
    memcpy(keyRightArrayCpy, keyRightArray, size * sizeof(short));

    for (short index = 0; index < size; index++)
    {
        for (short index2 = 0; index2 < size; index2++)
        {
            if (rightArr[index] == keyRightArrayCpy[index2])
            {
                keyRightArrayCpy[index2] = -1;
                break;
            }
            if (index2 == size - 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

void printArray(short* array, short size)
{
    for (short index = 0; index < size; index++)
    {
        std::cout << array[index] << " " << std::flush;
    }
    std::cout << std::endl;
}

void setupKeys(short**& keys, mpz_t** pascal, short size, short mod)
{
    short** keysActual;

    short numKeys = 3; // left, bot, and right keys

    /// create 2D array size x size
    keysActual = new short* [numKeys];
    for (short index = 0; index < numKeys; index++)
    {
        keysActual[index] = new short[size];
    }

    int hardKey[] = { 199, 99, 133, 107, 206, 164, 134, 241, 161, 24, 228, 13, 150, 245, 130, 84, 209, 35, 174, 17, 43, 241, 238, 144, 38, 68, 31, 6, 120, 224, 208, 63, 67, 85, 170, 17, 249, 49, 2, 155, 73, 230, 168, 223, 220, 43, 51, 173, 78, 225, 190, 121, 211, 172, 10, 249, 240, 41, 255, 105 };
    // int hardKey[] = {6, 3, 8, 11, 0, 15, 10, 2, 9, 0, 12, 0, 3, 4, 1, 4, 7, 10, 15, 2, 5, 3, 4, 9, 12};

    for (short index = 0; index < size; index++)
    {
        keysActual[keyLeftArr][index] = rand() % mod;
        keysActual[keyLeftArr][index] = hardKey[index];
    }

    mpz_t botItem;
    mpz_init(botItem);

    for (short index = 0; index < size; index++)
    {
        mpz_set_ui(botItem, 0);
        for (short index2 = 0; index2 < index + 1; index2++)
        {
            mpz_addmul_ui(botItem, pascal[size - 1 - index2][size - 1 - index + index2], keysActual[keyLeftArr][index2]);
        }
        keysActual[keyBotArr][index] = mpz_get_ui(botItem) % mod;
    }
    mpz_clear(botItem);

    mpz_t rightItem;
    mpz_init(rightItem);
    for (short index = 0; index < size; index++)
    {
        mpz_set_ui(rightItem, 0);
        for (short index2 = 0; index2 < index + 1; index2++)
        {
            mpz_addmul_ui(rightItem, pascal[size - 1 - index2][size - 1 - index + index2], keysActual[keyLeftArr][size - 1 - index2]);
        }
        keysActual[keyRightArr][index] = mpz_get_ui(rightItem) % mod;
    }
    mpz_clear(rightItem);

    keys = new short* [numKeys];
    for (short index = 0; index < numKeys; index++)
    {
        keys[index] = new short[mod];
    }

    for (short row = 0; row < numKeys; row++)
    {
        for (short index = 0; index < size; index++)
        {
            keys[row][keysActual[row][index]] += 1;
        }
    }

    printArray(keysActual[keyLeftArr], size);
    printArray(keysActual[keyBotArr], size);
    printArray(keysActual[keyRightArr], size);

    delete (keysActual[0]);
    delete (keysActual[1]);
    delete (keysActual[2]);
}

void setupPascal(mpz_t**& pascal, short size, short mod)
{

    /// create 2D array size x size
    pascal = new mpz_t * [size];
    for (short index = 0; index < size; index++)
    {
        pascal[index] = new mpz_t[size];
    }

    /// set all of pascal to 0
    for (short y = 0; y < size; y++)
    {
        for (short x = 0; x < size; x++)
        {
            mpz_init(pascal[y][x]);
            mpz_set_ui(pascal[y][x], 0);
        }
    }

    /// set right collumn and top row to 1
    for (short index = 0; index < size; index++)
    {
        mpz_set_ui(pascal[index][size - 1], 1); // right collumn
        mpz_set_ui(pascal[size - 1][index], 1); // top row
    }

    /// set rest of pascal values
    for (short y = size - 2; y > -1; y--)
    {
        for (short x = size - 2; x > -1; x--)
        {
            // mpz_set(pascal[y][x], pascal[y + 1][x] + pascal[y][x + 1]);
            mpz_add(pascal[y][x], pascal[y + 1][x], pascal[y][x + 1]);
            mpz_mod_ui(pascal[y][x], pascal[y][x], mod);
        }
    }
}

void displayPascal(mpz_t** pascal, short size)
{
    for (short y = size - 1; y > -1; y--)
    {
        for (short x = 0; x < size; x++)
        {
            std::cout << pascal[y][x] << "\t" << std::flush;
        }
        std::cout << std::endl;
    }
}

short getIndex(short item, short* arry, short size)
{
    for (short index = 0; index < size; index++)
    {
        if (item == arry[index])
        {
            return index;
        }
    }
    return -1;
}

void setupAndCopyKeys(short**& keysDest, short** keysSrc, short size)
{
    short numKeys = 3; // left, bot, and right keys

    /// create 2D array size x size
    keysDest = new short* [numKeys];
    for (short index = 0; index < numKeys; index++)
    {
        keysDest[index] = new short[size];
    }

    for (short y = 0; y < numKeys; y++)
    {
        memcpy(keysDest[y], keysSrc[y], size * sizeof(short));
    }
}

void recMiddle(short current, short* leftArr, short* botArr, mpz_t** pascal, short** keys, short size, short sizeChange, short mod, short& ret);

void recEnd(short current, short* leftArr, short* botArr, mpz_t** pascal, short** keys, short size, short sizeChange, short mod, short& ret);

void recZero(short* leftArr, short* botArr, mpz_t** pascal, short** keys, short size, short mod, short& ret)

{
    std::vector<short> possibilities;

    for (short index = 0; index < mod; index++)
    {
        if (keys[keyLeftArr][index] > 0 && keys[keyBotArr][index] > 0)
        {
            possibilities.push_back(index);
        }
    }

    std::vector<std::future<void>> threadsRunnning;
    for (short index = 0; index < THREADS; index++)
    {
        threadsRunnning.push_back(std::async(nothing));
    }

    for (short index = 0; index < possibilities.size(); index++)
    {
        std::cout << index + 1 << " " << possibilities.size() << std::endl;
        leftArr[0] = possibilities[index];
        botArr[0] = possibilities[index];

        keys[keyLeftArr][possibilities[index]] -= 1;
        keys[keyBotArr][possibilities[index]] -= 1;

        short* leftArrCpy = new short[size];
        short* botArrCpy = new short[size];

        memcpy(leftArrCpy, leftArr, size * sizeof(short));
        memcpy(botArrCpy, botArr, size * sizeof(short));

        short** keysCpy;

        setupAndCopyKeys(keysCpy, keys, mod);

        for (short index2 = 0; index2 < THREADS; index2++)
        {
            if (threadsRunnning[index2].wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
                threadsRunnning[index2] = std::async(std::launch::async, recMiddle, 1, leftArrCpy, botArrCpy, pascal, keysCpy, size, size - 1, mod, std::ref(ret));
                break;
            }
            if (index2 == THREADS - 1)
            {
                bool openThread = 0;
                while (!openThread)
                {
                    usleep(1 * 1000 * 100);
                    for (short index3 = 0; index3 < THREADS; index3++)
                    {
                        if (threadsRunnning[index3].wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
                        {
                            threadsRunnning[index3] = std::async(std::launch::async, recMiddle, 1, leftArrCpy, botArrCpy, pascal, keysCpy, size, size - 1, mod, std::ref(ret));
                            openThread = 1;
                        }
                    }
                }
                break;
            }
        }

        keys[keyLeftArr][possibilities[index]] += 1;
        keys[keyBotArr][possibilities[index]] += 1;
    }
    for (short index = 0; index < THREADS; index++)
    {
        if ((threadsRunnning[index].wait_for(std::chrono::milliseconds(0)) != std::future_status::ready))
        {
            threadsRunnning[index].wait();
        }
    }
    return;
}

void recMiddle(short current, short* leftArr, short* botArr, mpz_t** pascal, short** keys, short size, short sizeChange, short mod, short& ret)
{
    std::vector<std::array<short, 2>> possibilities;
    mpz_t bottomUpto;
    mpz_init(bottomUpto);
    mpz_set_ui(bottomUpto, 0);
    short diff = 0;
    for (short index = 0; index < current; index++)
    {
        mpz_addmul_ui(bottomUpto, pascal[size - 1 - index][size - 1 - current + index], leftArr[index]);
    }
    mpz_fdiv_r_ui(bottomUpto, bottomUpto, mod);
    diff = mpz_get_si(bottomUpto);

    mpz_clear(bottomUpto);

    for (short index = 0; index < mod; index++)
    {
        if (keys[keyLeftArr][index] > 0 && keys[keyBotArr][(index + diff) % mod] > 0)
        {
            possibilities.push_back({ index, (short)((index + diff) % mod) });
        }
    }

    // total += possibilities.size();
    // std::cout << possibilities.size() << std::endl;
    for (short index = 0; index < possibilities.size(); index++)
    {
        leftArr[current] = possibilities[index][0];
        botArr[current] = possibilities[index][1];

        keys[keyLeftArr][possibilities[index][0]] -= 1;
        keys[keyBotArr][possibilities[index][1]] -= 1;

        if (ret)
        {
            return;
        }

        if (current == size - 2)
        {
            long first = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            recEnd(current + 1, leftArr, botArr, pascal, keys, size, sizeChange - 1, mod, ret);
            long second = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            // std::cout << second - first << std::endl;
        }
        else
        {

            recMiddle(current + 1, leftArr, botArr, pascal, keys, size, sizeChange - 1, mod, ret);

        }

        keys[keyLeftArr][possibilities[index][0]] += 1;
        keys[keyBotArr][possibilities[index][1]] += 1;
    }
}

void recEnd(short current, short* leftArr, short* botArr, mpz_t** pascal, short** keys, short size, short sizeChange, short mod, short& ret)
{
    std::cout << "got to end" << std::endl;
    for (short index = 0; index < mod; index++)
    {
        if (keys[keyLeftArr][index] > 0)
        {
            leftArr[current] = index;
        }
        if (keys[keyBotArr][index] > 0)
        {
            botArr[current] = index;
        }
    }

    short rightArr[size];

    mpz_t rightItem;
    mpz_init(rightItem);

    // mpz_t rightItemMod;
    // mpz_init(rightItemMod);
    // mpz_set_ui(rightItemMod, 0);
    for (short index = 0; index < size; index++)
    {
        mpz_set_ui(rightItem, 0);
        for (short index2 = 0; index2 < index + 1; index2++)
        {
            mpz_addmul_ui(rightItem, pascal[size - 1 - index2][size - 1 - index + index2], leftArr[size - 1 - index2]);
        }
        // rightArr[index] = rightItem % mod;
        mpz_fdiv_r_ui(rightItem, rightItem, mod);
        rightArr[index] = mpz_get_si(rightItem);
    }

    mpz_clear(rightItem);

    // printArray(leftArr, size);
    // printArray(botArr, size);
    // std::cout << std::endl;

    short testCountArr[mod];
    memset(testCountArr, 0, mod * sizeof(short));
    for (short index = 0; index < size; index++)
    {
        testCountArr[rightArr[index]] += 1;
    }
    for (short index = 0; index < mod; index++)
    {
        if (testCountArr[index] != keys[keyRightArr][index])
        {
            std::cout << "failed" << std::endl;
            return;
        }
    }
    std::cout << "found" << std::endl;
    printArray(leftArr, size);
    printArray(botArr, size);
    printArray(rightArr, size);
    ret = 1;

    // mpz_clear(rightItemMod);

    return;
}

int main()
{
    srand(time(NULL));
    const short mod = 256;  //256
    const short size = 35; //36

    short leftArr[size];
    short botArr[size];

    memset(leftArr, 0, size * sizeof(short));
    memset(botArr, 0, size * sizeof(short));

    mpz_t** pascal;
    setupPascal(pascal, size, mod);

    // displayPascal(pascal, size);

    short** keys;
    setupKeys(keys, pascal, size, mod);

    // printArray(keys[keyLeftArr], mod);
    printArray(keys[keyBotArr], mod);
    printArray(keys[keyRightArr], mod);
    std::cout << std::endl
        << mod << std::endl;

    long first = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    ;

    short ret = 0;
    recZero(leftArr, botArr, pascal, keys, size, mod, ret);

    long second = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::cout << (second - first) / 1000000.0f << std::endl;

    return 0;
}
