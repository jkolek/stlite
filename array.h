// The MIT License (MIT)
//
// STLite array
// Copyright (c) 2017 Jozef Kolek <jkolek@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef ARRAY_H
#define ARRAY_H

#include "algorithms.h"

#include <algorithm>

namespace stlite
{

// constexpr unsigned vector_block_size = 100;

template <class T>
class Array
{
    T *_data = nullptr;
    unsigned _max_size = -1;
    unsigned _size = 0;

    // TODO: Implement external allocator
    void allocate_data(unsigned capacity)
    {
        _data = new T[capacity];
    }

public:
    Array() {}

    // Fill constructors
    explicit Array(unsigned n)
    {
        _size = n;
        allocate_data(n);
    }

    explicit Array(unsigned n, const T &val)
    {
        _size = n;
        allocate_data(n);
        for (unsigned i = 0; i < n; i++)
            _data[i] = val;
    }

    // This constructor creates array from the given array
    Array(T *arr, unsigned len);

    Array(std::initializer_list<T> initlst);

    Array(const Array &other);              // Copy constructor
    Array(Array &&other);                   // Move constructor

    ~Array() { if (_data) delete [] _data; } // Destructor

    Array<T>& operator=(const Array &other); // Copy assignment operator
    Array<T>& operator=(Array &&other);     // Move assignment operator

    // // Iterators
    // class Iterator
    // {
    //     T *_data = nullptr;
    //     unsigned _current = -1;
    // public:
    //     Iterator() {}
    //     Iterator(T *data, unsigned n) : _data(data), _current(n) {}

    //     // Prefix increment operator
    //     Iterator & operator++()
    //     {
    //         _current++;
    //         return *this;
    //     }

    //     // Postfix increment operator
    //     Iterator operator++(int)
    //     {
    //         Iterator tmp = *this;
    //         _current++;
    //         return tmp;
    //     }

    //     T & operator*()
    //     {
    //         return _data[_current];
    //     }

    //     bool operator==(Iterator other)
    //     {
    //         return other._current == _current;
    //     }

    //     bool operator!=(Iterator other)
    //     {
    //         return other._current != _current;
    //     }
    // };
    // Iterator begin() { return Iterator(_data, 0); }
    // // TODO: This is invalid end
    // Iterator end() { return Iterator(nullptr, _size); }

    // Capacity
    unsigned size() { return _size; }
    unsigned max_size() { return _max_size; }
    bool empty() { return _size == 0; }

    // Element access
    // http://www.cplusplus.com/reference/array/array/operator[]/
    // TODO: We must be able to assign values via []:
    //   arr[2] = 33;
    T operator[](unsigned n) const { return _data[n]; }
    T & operator[](unsigned n) { return _data[n]; }

    // http://www.cplusplus.com/reference/array/array/at/
    // TODO: We must be able to assign values via at():
    //   arr.at(2) = 33;
    T at(unsigned n)
    {
        if (n < _size)
            return _data[n];
        // TODO: Throw out_of_range exception
    }

    T front() { return _data[0]; }
    T back() { return _data[_size-1]; }
    T *data() { return _data; }

    // Modifiers
    void fill(const T &value);
    // swap()
};

//====----------------------------------------------------------------------====
// Implementations of methods
//====----------------------------------------------------------------------====

template <class T>
Array<T>::Array(T *arr, unsigned len)
{
    _size = len;
    allocate_data(len);
    std::copy(arr, arr + _size, _data);
}

template <class T>
Array<T>::Array(std::initializer_list<T> initlst)
{
    _size = initlst.size();
    allocate_data(_size);

    unsigned idx = 0;

    for (auto x : initlst)
        _data[idx++] = x;
}

// Copy constructor
template <class T>
Array<T>::Array(const Array &other)
{
    _size = other._size;
    allocate_data(other._size);
    std::copy(other._data, other._data + _size, _data);
}

// Move constructor
template <class T>
Array<T>::Array(Array &&other)
{
    if (&other != this)
    {
        _data = other._data;
        _size = other._size;

        other._data = nullptr;
        other._size = 0;
    }
}

// Copy assignment operator
template <class T>
Array<T>& Array<T>::operator=(const Array &other)
{
    if (&other != this)
    {
        if (_data)
            delete [] _data;

        _size = other._size;
        allocate_data(other._size);
        std::copy(other._data, other._data + _size, _data);
    }
    return *this;
}

// Move assignment operator
template <class T>
Array<T>& Array<T>::operator=(Array &&other)
{
    if (&other != this)
    {
        if (_data)
            delete [] _data;

        _data = other._data;
        _size = other._size;

        other._data = nullptr;
        other._size = 0;
    }
    return *this;
}

template <class T>
void Array<T>::fill(const T &value)
{
    for (unsigned i = 0; i < _size; ++i)
        _data[i] = value;
}

} // namespace stlite

#endif
