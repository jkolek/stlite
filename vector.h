// The MIT License (MIT)
//
// STLite vector
// Copyright (c) 2017, 2018 Jozef Kolek <jkolek@gmail.com>
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

#ifndef VECTOR_H
#define VECTOR_H

#include "algorithms.h"

#include <algorithm>

namespace stlite
{

constexpr unsigned vector_block_size = 100;

template <class T>
class Vector
{
    T *_data = nullptr;
    unsigned _max_size = -1;
    unsigned _capacity = 0;
    unsigned _size = 0;

    // TODO: Implement external allocator
    void allocate_data(unsigned capacity)
    {
        _capacity = capacity;
        _data = new T[_capacity];
    }

public:
    Vector() {}

    // Fill constructors
    explicit Vector(unsigned n)
    {
        _size = n;
        allocate_data(n);
    }

    explicit Vector(unsigned n, const T &val)
    {
        _size = n;
        allocate_data(n);
        for (unsigned i = 0; i < n; i++)
            _data[i] = val;
    }

    // This constructor creates list from the given array
    Vector(T *arr, unsigned len);

    Vector(std::initializer_list<T> initlst);

    Vector(const Vector &other);               // Copy constructor
    Vector(Vector &&other);                    // Move constructor

    ~Vector() { if (_data) delete [] _data; }  // Destructor

    Vector<T>& operator=(const Vector &other); // Copy assignment operator
    Vector<T>& operator=(Vector &&other);      // Move assignment operator

    // Iterators
    class Iterator
    {
        T *_data = nullptr;
        unsigned _current = -1;
    public:
        Iterator() {}
        Iterator(T *data, unsigned n) : _data(data), _current(n) {}

        // Prefix increment operator
        Iterator & operator++()
        {
            _current++;
            return *this;
        }

        // Postfix increment operator
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            _current++;
            return tmp;
        }

        T & operator*()
        {
            return _data[_current];
        }

        bool operator==(Iterator other)
        {
            return other._current == _current;
        }

        bool operator!=(Iterator other)
        {
            return other._current != _current;
        }
    };

    Iterator begin() { return Iterator(_data, 0); }
    // TODO: This is invalid end
    Iterator end() { return Iterator(nullptr, _size); }

    // Capacity
    unsigned size() { return _size; }
    unsigned max_size() { return _max_size; }
    unsigned capacity() { return _capacity; }
    bool empty() { return _size == 0; }

    // Element access
    // http://www.cplusplus.com/reference/vector/vector/operator[]/
    // We must be able to assign values via []:
    //   arr[2] = 33;
    T & operator[](int n) { return _data[n]; }
    T operator[](int n) const { return _data[n]; }

    // http://www.cplusplus.com/reference/vector/vector/at/
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
    void push_back(T value);
    bool pop_back();
    void append(const Vector &other);
    void clear();

    // Allocator
    // http://www.cplusplus.com/reference/vector/vector/get_allocator/
    // get_allocator()

    // Operations
    void reverse();
};

//====----------------------------------------------------------------------====
// Implementations of methods
//====----------------------------------------------------------------------====

template <class T>
Vector<T>::Vector(T *arr, unsigned len)
{
    _size = len;
    allocate_data(len);
    std::copy(arr, arr + _size, _data);
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> initlst)
{
    _size = initlst.size();
    allocate_data(_size);

    unsigned idx = 0;

    for (auto x : initlst)
        _data[idx++] = x;
}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector &other)
{
    _size = other._size;
    allocate_data(other._size);
    std::copy(other._data, other._data + _size, _data);
}

// Move constructor
template <class T>
Vector<T>::Vector(Vector &&other)
{
    if (&other != this)
    {
        _data = other._data;
        _capacity = other._capacity;
        _size = other._size;

        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }
}

// Copy assignment operator
template <class T>
Vector<T>& Vector<T>::operator=(const Vector &other)
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
Vector<T>& Vector<T>::operator=(Vector &&other)
{
    if (&other != this)
    {
        if (_data)
            delete [] _data;

        _data = other._data;
        _capacity = other._capacity;
        _size = other._size;

        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }
    return *this;
}

// Append element to end of the list
template <class T>
void Vector<T>::push_back(T value)
{
    if (!_data)
    {
        allocate_data(vector_block_size);
    }
    else if (_size >= _capacity)
    {
        unsigned new_capacity = _capacity + vector_block_size;

        if (new_capacity > _max_size)
            return;

        T *tmp = new T[new_capacity];
        std::copy(_data, _data + _size, tmp);
        delete [] _data;
        _data = tmp;
        _capacity = new_capacity;
    }

    _data[_size++] = value;
}

template <class T>
bool Vector<T>::pop_back()
{
    if (_size > 0)
        _size--;
}

// Append elements of other to end of the vector
template <class T>
void Vector<T>::append(const Vector &other)
{
    // TODO: Implement
}

template <class T>
void Vector<T>::clear()
{
    _size = 0;
}

template <class T>
void Vector<T>::reverse()
{
    if (_size == 0)
        return;

    unsigned i = 0;
    unsigned j = _size-1;

    while (i < j)
        swap(_data[i++], _data[j--]);
}

} // namespace stlite

#endif
