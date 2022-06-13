#pragma once
#include <memory.h>
#include <iostream>

template <typename T>
class MyArr
{
#define ALLOC_SIZE 100
    T *_arr = nullptr;
    unsigned long _size = 0;
    unsigned long _allocated = 0;

public:
    T &operator[](const unsigned long index)
    {
        // if (index < size)
        {
            return _arr[index];
        }
    }

    MyArr &operator=(MyArr &&ref)
    {
        if (ref._allocated)
        {
            _allocated = ref._allocated;
            if (_arr)
            {
                delete[] _arr;
            }
            _arr = new T[_allocated];
        }
        if (ref._size)
        {
            _size = ref._size;
            for (int index = 0; index < _size; index++)
            {
                _arr[index] = ref._arr[index];
            }
        }
        return *this;
    }

    MyArr &operator=(const MyArr &ref)
    {
        if (ref._allocated)
        {
            _allocated = ref._allocated;
            if (_arr)
            {
                delete[] _arr;
            }
            _arr = new T[_allocated];
        }
        if (ref._size)
        {
            _size = ref._size;
            for (int index = 0; index < _size; index++)
            {
                _arr[index] = ref._arr[index];
            }
        }
        return *this;
    }

    void setSize(const unsigned long size)
    {
        if (size > _allocated)
        {
            _allocated = (size / ALLOC_SIZE + 1) * ALLOC_SIZE;
            if (_arr)
            {
                T *backup = _arr;
                _arr = new T[_allocated];
                for (unsigned long index = 0; index < _size; index++)
                {
                    _arr[index] = backup[index];
                }
                // memcpy(_arr, backup, sizeof(T) * _size);
                delete[] backup;
            }
            else
            {
                _arr = new T[_allocated];
            }
        }
        _size = size;
    }

    MyArr(const unsigned long sizeInit)
    {
        _size = sizeInit;
        _allocated = (_size / ALLOC_SIZE + 1) * ALLOC_SIZE;
        _arr = new T[_allocated];
    }

    MyArr(MyArr &ref)
    {
        if (ref._allocated)
        {
            _allocated = ref._allocated;
            _arr = new T[_allocated];
        }
        if (ref._size)
        {
            _size = ref._size;
            for (int index = 0; index < _size; index++)
            {
                _arr[index] = ref._arr[index];
            }
        }
    }

    MyArr()
    {
    }

    ~MyArr()
    {
        if (_arr)
        {
            delete[] _arr;
        }
    }

    unsigned long size()
    {
        return _size;
    }

    unsigned long allocated()
    {
        return _allocated;
    }

    void push_back(T item)
    {
        if (_size == _allocated)
        {
            if (_arr)
            {
                T *backup = _arr;
                _allocated += ALLOC_SIZE;
                _arr = new T[_allocated];
                for (unsigned long index = 0; index < _size; index++)
                {
                    _arr[index] = backup[index];
                }
                // memcpy(_arr, backup, sizeof(T) * _size);
                delete[] backup;
            }
            else
            {
                _allocated += ALLOC_SIZE;
                _arr = new T[_allocated];
            }
        }
        _arr[_size++] = item;
    }

    void pop_back()
    {
        _size--;
    }

    T *getArrPointer()
    {
        return _arr;
    }

    void remove(unsigned long index)
    {
        _size--;
        for (int _index = index; _index < _size; _index++)
        {
            _arr[_index] = _arr[_index + 1];
        }
    }

    void removeDuplicatesWithFunc(unsigned long index)
    {
        _size--;
        for (int _index = index; _index < _size; _index++)
        {
            _arr[_index] = _arr[_index + 1];
        }
    }

    // TODO OPTIMIZE
    void order()
    {
        T finalArray[_size];
        for (short index = 0; index < _size; index++)
        {
            unsigned long smallestIndex = 0;
            for (short index2 = 1; index2 < _size - index; index2++)
            {
                if (_arr[smallestIndex] > _arr[index2])
                {
                    smallestIndex = index2;
                }
            }

            finalArray[index] = _arr[smallestIndex];

            for (int index2 = smallestIndex; index2 < _size - index; index2++)
            {
                _arr[index2] = _arr[index2 + 1];
            }
        }
        memcpy(_arr, finalArray, _size * sizeof(T));
    }

    template <typename ret>
    void orderWithFunc(ret (*func)(T))
    {
        T finalArray[_size];
        for (short index = 0; index < _size; index++)
        {
            unsigned long smallestIndex = 0;
            for (short index2 = 1; index2 < _size - index; index2++)
            {
                if (func(_arr[smallestIndex]) > func(_arr[index2]))
                {
                    smallestIndex = index2;
                }
            }

            finalArray[index] = _arr[smallestIndex];

            for (int index2 = smallestIndex; index2 < _size - index; index2++)
            {
                _arr[index2] = _arr[index2 + 1];
            }
        }
        memcpy(_arr, finalArray, _size * sizeof(T));
    }

    void orderWithFunc(bool (*greaterThan)(T, T))
    {
        T finalArray[_size];
        for (short index = 0; index < _size; index++)
        {
            unsigned long smallestIndex = 0;
            for (short index2 = 1; index2 < _size - index; index2++)
            {
                // if (func(_arr[smallestIndex]) > func(_arr[index2]))
                if (greaterThan(_arr[smallestIndex], _arr[index2]))
                {
                    smallestIndex = index2;
                }
            }

            finalArray[index] = _arr[smallestIndex];

            for (int index2 = smallestIndex; index2 < _size - index; index2++)
            {
                _arr[index2] = _arr[index2 + 1];
            }
        }
        memcpy(_arr, finalArray, _size * sizeof(T));
    }

    void flip()
    {
        T copy;
        unsigned long mid = _size/2;
        for (unsigned long index = 0; index < mid; index++)
        {
            copy = _arr[_size - 1 - index];
            _arr[_size -1- index] = _arr[index];
            _arr[index] = copy;
        }
    }

    bool in(T item)
    {
        for (unsigned long index = 0; index < _size; index++)
        {
            if (_arr[index] == item)
            {
                return 1;
            }
        }
        return 0;
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const MyArr<U> &arr);
};

// TODO FIX OUT OF BOUND ERROR
template <typename T>
std::ostream & operator<<(std::ostream &os, const MyArr<T> &arr)
{
    os << "[";
    for (unsigned long index = 0; index < arr._size - 1; index++)
    {
        os << arr._arr[index] << ", ";
    }
    os << arr._arr[arr._size - 1] << "]";
    return os;
}