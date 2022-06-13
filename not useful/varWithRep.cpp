#include <iostream>
#include <array>
#include <gmpxx.h>
#include <vector>
#include <unistd.h>
#include <bitset>

#define MOD 8
#define SIZE 8

class charArray
{
public:
    unsigned char bounds;
    unsigned char *c;
    // unsigned char* left;
    unsigned char *multArray;
    int size = 0;
    bool run = true;
    mpz_t past;

    mpz_t **pascal;

    charArray(int size)
    {
        this->size = size;
        c = new unsigned char[size];
        multArray = new unsigned char[size];
        memset(c, 0, size);
        setupPascal(pascal, size);
        mpz_init(past);
        for (int index = 0; index < size; index++)
        {
            multArray[index] = mpz_get_ui(pascal[index][size - 1 - index]);
        }
    }

    unsigned short getTop()
    {
        unsigned short ret = 0;
        for (int index = 0; index < size; index++)
        {
            ret += multArray[index] * c[index];
        }
        return ret;
    }

    unsigned short getLeftTop()
    {
        unsigned char left[size];
        left[0] = c[0];

        unsigned char lower[size];
        memcpy(lower, c, size);

        for (int index = 0; index < size - 1; index++)
        {
            for (int index2 = 0; index2 < size - 1 - index; index2++)
            {
                lower[index2] = lower[index2 + 1] - lower[index2];
            }
            left[index + 1] = lower[0];
        }

        unsigned short ret = 0;
        for (int index = 0; index < size; index++)
        {
            ret += multArray[index] * left[index];
        }
        return ret;
    }

    void setupPascal(mpz_t **&pascal, short size)
    {

        /// create 2D array size x size
        pascal = new mpz_t *[size];
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
            }
        }
    }

    void printBot()
    {
        std::cout << "[" << std::flush;
        for (int index = 0; index < size; index++)
        {
            std::cout << +(c[index]) << std::flush;
            if (index + 1 == size)
            {
                std::cout << "]" << std::endl;
            }
            else
            {
                std::cout << ", " << std::flush;
            }
        }
    }

    unsigned char &operator[](int index)
    {
        if (index >= size)
        {
            return bounds;
        }
        return c[index];
    }

    void increase(int count)
    {
        int add = count;
        for (int index = size - 1; index >= 0; index--)
        {
            if (add == 0)
            {
                break;
            }
            int tmpadd = add;
            add = (c[index] + add) / 256;
            c[index] += tmpadd;
        }
    }

    void increment()
    {
        for (int index = size - 1; index >= 0; index--)
        {
            if (c[index] == 255)
            {
                if (index == 0)
                {
                    run = false;
                }

                c[index] = 0;
            }
            else
            {
                mpz_add_ui(past, past, 1);
                std::cout << past << std::endl;
                c[index] += 1;
                return;
            }
        }
    }

    unsigned short getBotTot()
    {
        unsigned short ret = 0;
        for (int index = 0; index < size; index++)
        {
            ret += c[index];
        }
        return ret;
    }

    unsigned long long codeToLong()
    {
        unsigned long long ret = 0;
        for (int index = 0; index < size; index++)
        {
            ret += ((unsigned long long)c[index]) << (8 * (size - 1 - index));
        }
        return ret;
    }

    void longToCode(unsigned long long in)
    {
        std::cout << "[" << std::flush;
        void *inVoidPtr = &in;
        for (int index = 0; index < size; index++)
        {
            std::cout << +(*((unsigned char *)(inVoidPtr + size - 1 - index))) << std::flush;
            if (index + 1 == size)
            {
                std::cout << "]" << std::endl;
            }
            else
            {
                std::cout << ", " << std::flush;
            }
        }
    }

    // unsigned char& operator[](int index)
    // {
    //     void* v = &i;
    //     return *((unsigned char*)(v + index));
    // }
};

template <typename T>
void printVec(std::vector<T> vec)
{
    std::cout << "[" << std::flush;
    int vecSize = vec.size();
    for (int index = 0; index < vecSize; index++)
    {
        std::cout << +(unsigned char)(vec[index]) << std::flush;
        if (index + 1 == vecSize)
        {
            std::cout << "]" << std::endl;
        }
        else
        {
            std::cout << ", " << std::flush;
        }
    }
}

std::vector<char> getCodeRec(mpz_t key, std::vector<char> arr, int currentLevel)
{
    mpz_t setSize;
    mpz_init(setSize);
    mpz_ui_pow_ui(setSize, MOD, (SIZE - 1 - currentLevel));

    mpz_t ret;
    mpz_init(ret);
    mpz_div(ret, key, setSize);
    mpz_mod_ui(ret, ret, MOD);

    arr.push_back(mpz_get_ui(ret));

    mpz_clear(setSize);
    mpz_clear(ret);

    if (currentLevel + 1 == SIZE)
    {
        return arr;
    }
    else
    {
        return getCodeRec(key, arr, currentLevel + 1);
    }

    return std::vector<char>();
}

std::vector<char> getCode(mpz_t key)
{
    mpz_t totalCodes;
    mpz_init(totalCodes);
    mpz_ui_pow_ui(totalCodes, MOD, SIZE);

    int ret = mpz_cmp(key, totalCodes);
    mpz_clear(totalCodes);

    if (ret >= 0)
    {
        return std::vector<char>();
    }
    else
    {
        return getCodeRec(key, std::vector<char>(), 0);
    }
}

template <typename T>
int getTopTotal(std::vector<T> arr)
{
    std::vector<int> newArr;
    for (int index = 0; index < arr.size() - 1; index++)
    {
        if (typeid(T) == typeid(char))
        {
            newArr.push_back((unsigned char)arr[index] + (unsigned char)arr[index + 1]);
        }
        else
        {
            newArr.push_back(arr[index] + arr[index + 1]);
        }
    }
    if (arr.size() == 2)
    {
        return newArr[0];
    }
    else
    {
        return getTopTotal(newArr);
    }
}

std::vector<char> getDiffLeftArrRec(std::vector<char> arr, std::vector<char> outArr)
{
    std::vector<char> newArr;
    for (int index = 0; index < arr.size() - 1; index++)
    {
        int diff = arr[index + 1] - arr[index];
        if (diff < 0)
        {
            diff = MOD + diff;
        }
        newArr.push_back(diff);
    }
    outArr.push_back(newArr[0]);
    if (arr.size() == 2)
    {
        return outArr;
    }
    else
    {
        return getDiffLeftArrRec(newArr, outArr);
    }
}

std::vector<char> getDiffLeftArr(std::vector<char> arr)
{
    std::vector<char> outArr;
    outArr.push_back(arr[0]);
    return getDiffLeftArrRec(arr, outArr);
}

int getArrayTotal(std::vector<char> arr)
{
    int num = 0;
    for (int index = 0; index < arr.size(); index++)
    {
        num += arr[index];
    }
    return num;
}

int main()
{

    mpz_t totalCodes;
    mpz_init(totalCodes);
    mpz_ui_pow_ui(totalCodes, MOD, SIZE);

    std::vector<long> log;
    std::vector<unsigned long long> codes;

    // comb with Rep
    int size = 35;
    int mod = 256;

    mpz_t top;
    mpz_init(top);
    mpz_set_ui(top, 1);
    int topTimes = mod + size - 1;
    int times = size - 1;
    for (int index = topTimes; index > topTimes - times - 1; index--)
    {
        mpz_mul_ui(top, top, index);
    }
    mpz_t bot;
    mpz_init(bot);
    mpz_set_ui(bot, 1);
    for (int index = 1; index < size + 1; index++)
    {
        mpz_mul_ui(bot, bot, index);
    }

    mpz_t final;
    mpz_init(final);
    mpz_div(final, top, bot);
    mpz_sub_ui(final, final, 1);
    // std::cout << top << std::endl;
    // std::cout << bot << std::endl;
    // std::cout << final << std::endl;
    std::cout << mpz_sizeinbase(final, 2) << std::endl;

    mpz_t order;
    mpz_init(order);
    mpz_set_ui(order, 1);
    for (int index = 1; index < size + 1; index++)
    {
        mpz_mul_ui(order, order, index);
    }
    mpz_sub_ui(order, order, 1);
    // std::cout << order << std::endl;
    std::cout << mpz_sizeinbase(order, 2) << std::endl;

    mpz_t possibilities;
    mpz_init(possibilities);
    mpz_set_ui(possibilities, mod);
    mpz_pow_ui(possibilities, possibilities, size);
    mpz_sub_ui(possibilities, possibilities, 1);
    std::cout << mpz_sizeinbase(possibilities, 2) << std::endl;

    std::cout << ((mpz_sizeinbase(final, 2) + mpz_sizeinbase(order, 2)) < mpz_sizeinbase(possibilities, 2)) << std::endl;

    // for (charArray c(SIZE); c.run; c.increment())
    // {
    //     long allTot = 0;
    //     allTot += ((long)c.getTop()) << 32;
    //     allTot += ((int)c.getLeftTop()) << 16;
    //     allTot += c.getBotTot();
    //     // std::array<unsigned short, 3> allTot = {c.getTop(), c.getLeftTop(), c.getBotTot()};
    //     std::vector<long>::iterator at =  std::find(log.begin(), log.end(), allTot);
    //     if (at != log.end())
    //     {
    //         unsigned long long atInt = std::distance(log.begin(), at);
    //         std::cout << "current" << std::endl;
    //         std::cout << std::bitset<48>(allTot) << std::endl;
    //         c.printBot();
    //         std::cout << "previous" << std::endl;
    //         std::cout << std::bitset<48>(log[atInt]) << std::endl;
    //         c.longToCode(codes[atInt]);
    //     }
    //     // std::cout << std::bitset<48>(allTot) << std::endl;
    //     // c.printBot();
    //     // std::cout << c.getTop() << " " << c.getLeftTop() << " " << c.getBotTot() << std::endl;
    //     // c.longToCode(c.codeToLong());
    //     codes.push_back(c.codeToLong());
    //     log.push_back(allTot);
    // }

    return 0;
}
