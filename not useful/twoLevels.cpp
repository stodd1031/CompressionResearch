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

#define KEYS 5

#define keyLeftArr 0
#define keyBotArr 1
#define secondRow 2
#define keyRightArr 3
#define thirdRow 4

#define THREADS 7

class diffsArray;

void nothing() {}

void displayChart(int **array, int size)
{
    for (int y = size - 1; y > -1; y--)
    {
        for (int x = 0; x < size; x++)
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

void order(int *&arrayIn, int size, int mod)
{
    int finalArrayIndex = 0;
    int finalArray[size];
    int arrayCpy[size];
    memcpy(arrayCpy, arrayIn, size * sizeof(int));
    for (int index = 0; index < mod; index++)
    {
        for (int index2 = 0; index2 < size; index2++)
        {
            if (arrayCpy[index2] == index)
            {
                finalArray[finalArrayIndex] = index;
                finalArrayIndex += 1;
                arrayCpy[index2] = -1;
            }
        }
    }
    memcpy(arrayIn, finalArray, size * sizeof(int));
}

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

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

bool in(int item, int *arr, int size)
{
    return binarySearch(arr, 0, size - 1, item);
    // for (int index = 0; index < size; index++)
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

bool in(std::array<int, 2> item, std::vector<std::array<int, 2>> arr)
{
    int count;
    for (int index = 0; index < arr.size(); index++)
    {
        count = 0;
        for (int index2 = 0; index2 < 2; index2++)
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

bool checkRight(int *rightArr, int *keyRightArray, int size)
{
    int keyRightArrayCpy[size];
    memcpy(keyRightArrayCpy, keyRightArray, size * sizeof(int));

    for (int index = 0; index < size; index++)
    {
        for (int index2 = 0; index2 < size; index2++)
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

void printArray(int *array, int size)
{
    for (int index = 0; index < size; index++)
    {
        std::cout << array[index] << " " << std::flush;
    }
    std::cout << std::endl;
}

void setupKeys(int **&keys, mpz_t **pascal, int size, int mod)
{
    int **keysActual;

    int numKeys = KEYS; // left, bot, and right keys

    /// create 2D array size x size
    keysActual = new int *[numKeys];
    for (int index = 0; index < numKeys; index++)
    {
        keysActual[index] = new int[size];
    }

    // int hardKey[] = {90, 17, 234, 124, 153, 23, 70, 207, 195, 224, 46, 100, 21, 41, 171, 230, 224, 229, 131, 44, 79, 86, 122, 203, 103, 106, 45, 185, 52, 112, 46, 142, 129, 24, 2, 47, 70};
    int hardKey[] = {6, 3, 8, 11, 0, 15, 10, 2, 9, 0, 12, 0, 3, 4, 1, 4, 7, 10, 15, 2, 5, 3, 4, 9, 12};

    for (int index = 0; index < size; index++)
    {
        keysActual[keyLeftArr][index] = rand() % mod;
        // keysActual[keyLeftArr][index] = hardKey[index];
    }

    mpz_t botItem;
    mpz_init(botItem);

    for (int index = 0; index < size; index++)
    {

        mpz_set_ui(botItem, 0);
        for (int index2 = 0; index2 < index + 1; index2++)
        {
            mpz_addmul_ui(botItem, pascal[size - 1 - index2][size - 1 - index + index2], keysActual[keyLeftArr][index2]);
        }
        keysActual[keyBotArr][index] = mpz_get_ui(botItem) % mod;
    }
    mpz_clear(botItem);

    for (int index = 0; index < size; index++)
    {
        if (index < 1)
        {
            keysActual[secondRow][index] = 0;
        }
        else
        {
            keysActual[secondRow][index] = keysActual[keyBotArr][index] - keysActual[keyBotArr][index - 1];
            if (keysActual[secondRow][index] < 0)
            {
                keysActual[secondRow][index] = mod + keysActual[secondRow][index];
            }
        }
    }

    for (int index = 0; index < size; index++)
    {
        if (index < 2)
        {
            keysActual[thirdRow][index] = 0;
        }
        else
        {
            keysActual[thirdRow][index] = keysActual[secondRow][index] - keysActual[secondRow][index - 1];
            if (keysActual[thirdRow][index] < 0)
            {
                keysActual[thirdRow][index] = mod + keysActual[thirdRow][index];
            }
        }
    }

    mpz_t rightItem;
    mpz_init(rightItem);
    for (int index = 0; index < size; index++)
    {
        mpz_set_ui(rightItem, 0);
        for (int index2 = 0; index2 < index + 1; index2++)
        {
            mpz_addmul_ui(rightItem, pascal[size - 1 - index2][size - 1 - index + index2], keysActual[keyLeftArr][size - 1 - index2]);
        }
        keysActual[keyRightArr][index] = mpz_get_ui(rightItem) % mod;
    }
    mpz_clear(rightItem);

    keys = new int *[numKeys];
    for (int index = 0; index < numKeys; index++)
    {
        keys[index] = new int[mod];
        memset(keys[index], 0, mod * sizeof(int));
    }

    for (int row = 0; row < numKeys; row++)
    {
        for (int index = 0; index < size; index++)
        {
            keys[row][keysActual[row][index]] += 1;
        }
    }

    keys[secondRow][0] -= 1;
    keys[thirdRow][0] -= 2;

    // printArray(keysActual[keyLeftArr], size);
    printArray(keysActual[thirdRow], size);
    printArray(keysActual[secondRow], size);
    printArray(keysActual[keyBotArr], size);

    delete (keysActual[0]);
    delete (keysActual[1]);
    delete (keysActual[2]);
}

void setupPascal(mpz_t **&pascal, int size)
{

    /// create 2D array size x size
    pascal = new mpz_t *[size];
    for (int index = 0; index < size; index++)
    {
        pascal[index] = new mpz_t[size];
    }

    /// set all of pascal to 0
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            mpz_init(pascal[y][x]);
            mpz_set_ui(pascal[y][x], 0);
        }
    }

    /// set right collumn and top row to 1
    for (int index = 0; index < size; index++)
    {
        mpz_set_ui(pascal[index][size - 1], 1); // right collumn
        mpz_set_ui(pascal[size - 1][index], 1); // top row
    }

    /// set rest of pascal values
    for (int y = size - 2; y > -1; y--)
    {
        for (int x = size - 2; x > -1; x--)
        {
            // mpz_set(pascal[y][x], pascal[y + 1][x] + pascal[y][x + 1]);
            mpz_add(pascal[y][x], pascal[y + 1][x], pascal[y][x + 1]);
        }
    }
}

void displayPascal(mpz_t **pascal, int size)
{
    for (int y = size - 1; y > -1; y--)
    {
        for (int x = 0; x < size; x++)
        {
            std::cout << pascal[y][x] << "\t" << std::flush;
        }
        std::cout << std::endl;
    }
}

int getIndex(int item, int *arry, int size)
{
    for (int index = 0; index < size; index++)
    {
        if (item == arry[index])
        {
            return index;
        }
    }
    return -1;
}

void setupAndCopyKeys(int **&keysDest, int **keysSrc, int size)
{
    int numKeys = KEYS; // left, bot, and right keys

    /// create 2D array size x size
    keysDest = new int *[numKeys];
    for (int index = 0; index < numKeys; index++)
    {
        keysDest[index] = new int[size];
    }

    for (int y = 0; y < numKeys; y++)
    {
        memcpy(keysDest[y], keysSrc[y], size * sizeof(int));
    }
}

void recMiddle(int current, int *botArr, int *secArr, int *thiArr, int **keys, int size, int mod, int &ret);

void recEnd(int current, int *botArr, int *secArr, int *thiArr, int **keys, int size, int mod, int &ret);

void recZero(int *botArr, int *secArr, int *thiArr, int **keys, int size, int mod, int &ret)
{
    std::vector<int> possibilities;

    for (int index = 0; index < mod; index++)
    {
        if (keys[keyBotArr][index] > 0)
        {
            possibilities.push_back(index);
        }
    }

    std::vector<std::future<void>> threadsRunnning;
    for (int index = 0; index < THREADS; index++)
    {
        threadsRunnning.push_back(std::async(nothing));
    }

    for (int index = 0; index < possibilities.size(); index++)
    {
        std::cout << index + 1 << " " << possibilities.size() << std::endl;
        botArr[0] = possibilities[index];

        keys[keyBotArr][possibilities[index]] -= 1;

        int *secArrCpy = new int[size];
        int *botArrCpy = new int[size];
        int *thiArrCpy = new int[size];

        memcpy(secArrCpy, secArr, size * sizeof(int));
        memcpy(botArrCpy, botArr, size * sizeof(int));
        memcpy(thiArrCpy, botArr, size * sizeof(int));

        int **keysCpy;

        setupAndCopyKeys(keysCpy, keys, mod);

        for (int index2 = 0; index2 < THREADS; index2++)
        {
            if (threadsRunnning[index2].wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
                threadsRunnning[index2] = std::async(std::launch::async, recMiddle, 1, botArrCpy, secArrCpy, thiArrCpy, keysCpy, size, mod, std::ref(ret));
                break;
            }
            if (index2 == THREADS - 1)
            {
                bool openThread = 0;
                while (!openThread)
                {
                    usleep(1 * 1000 * 10);
                    for (int index3 = 0; index3 < THREADS; index3++)
                    {
                        if (threadsRunnning[index3].wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
                        {
                            threadsRunnning[index3] = std::async(std::launch::async, recMiddle, 1, botArrCpy, secArrCpy, thiArrCpy, keysCpy, size, mod, std::ref(ret));
                            openThread = 1;
                        }
                    }
                }
                break;
            }
        }

        keys[keyBotArr][possibilities[index]] += 1;
    }
    for (int index = 0; index < THREADS; index++)
    {
        if ((threadsRunnning[index].wait_for(std::chrono::milliseconds(0)) != std::future_status::ready))
        {
            threadsRunnning[index].wait();
        }
    }
    return;
}

void recMiddle(int current, int *botArr, int *secArr, int *thiArr, int **keys, int size, int mod, int &ret)
{
    std::vector<std::array<int, 2>> possibilities;
    for (int index = 0; index < mod; index++)
    {
        if (keys[secondRow][index] > 0 && keys[keyBotArr][(index + botArr[current - 1]) % mod] > 0)
        {
            possibilities.push_back({(index + botArr[current - 1]) % mod, index});
        }
    }

    for (int index = 0; index < possibilities.size(); index++)
    {
        keys[keyBotArr][possibilities[index][0]] -= 1;
        keys[secondRow][possibilities[index][1]] -= 1;

        botArr[current] = possibilities[index][0];
        secArr[current] = possibilities[index][1];

        if (ret)
        {
            return;
        }

        if (current == size - 2)
        {
            recEnd(current + 1, botArr, secArr, thiArr, keys, size, mod, ret);
        }
        else
        {
            recMiddle(current + 1, botArr, secArr, thiArr, keys, size, mod, ret);
        }

        keys[keyBotArr][possibilities[index][0]] += 1;
        keys[secondRow][possibilities[index][1]] += 1;
    }
}

void recEnd(int current, int *botArr, int *secArr, int *thiArr, int **keys, int size, int mod, int &ret)
{
    int second;
    for (int index = 0; index < mod; index++)
    {
        if (keys[keyBotArr][index] > 0)
        {
            botArr[current] = index;
        }
        if (keys[secondRow][index] > 0)
        {
            second = index;
        }
    }

    if ((botArr[current - 1] + second) % mod != botArr[current])
    {
        return;
    }

    int chart[size][size];
    for (int y = 0; y<size;y++)
    {
        for (int x = 0; x<size;x++)
        {
            chart[y][x] = 0;
        }
    }

    memcpy(chart[0], botArr, size*sizeof(int));

    for (int y = 1; y<size;y++)
    {
        for (int x = 1; x<size;x++)
        {
            if (y > x)
            {
                continue;
            }
            chart[y][x] = chart[y][x];
        }
    }

    std::cout << "found" << std::endl;
    // printArray(leftArr, size);
    printArray(botArr, size);
    ret = 1;

    // mpz_clear(rightItemMod);

    return;
}

int main()
{
    srand(time(NULL));
    int mod = 16; //256
    int size = 10;     //36

    int botArr[size];
    int secArr[size];
    int thiArr[size];

    memset(botArr, 0, size * sizeof(int));
    memset(secArr, 0, size * sizeof(int));
    memset(thiArr, 0, size * sizeof(int));    

    mpz_t **pascal;
    setupPascal(pascal, size);

    // displayPascal(pascal, size);

    int **keys;
    setupKeys(keys, pascal, size, mod);

    // printArray(keys[keyLeftArr], mod);
    // printArray(keys[secondRow], mod);
    // printArray(keys[keyBotArr], mod);
    std::cout << std::endl
              << mod << std::endl;

    long first = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    ;

    int ret = 0;
    recZero(botArr, secArr, thiArr, keys, size, mod, ret);

    long second = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::cout << (second - first) / 1000000.0f << std::endl;

    return 0;
}
