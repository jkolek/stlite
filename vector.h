// The MIT License (MIT)
//
// High-performance generic vector - header file
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

#ifndef VECTOR_H
#define VECTOR_H

#define BLOCK_SIZE 100

template <class T>
class VectorIterator;

template <class T>
class Vector
{
    T *_data = nullptr;
    unsigned _max_size = -1;
    unsigned _capacity = 0;
    unsigned _size = 0;

    friend class VectorIterator<T>;

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

    explicit Vector(unsigned n, const T& val)
    {
        _size = n;
        allocate_data(n);
        for (unsigned i = 0; i < n; i++)
            _data[i] = val;
    }

    // This constructor creates list from the given array
    Vector(T *arr, unsigned len);

    Vector(const Vector &other);         // Copy constructor
    Vector(Vector &&other);              // Move constructor

    // Destructor
    ~Vector()
    {
        if (_data)
            delete [] _data;
    }

    void operator=(const Vector &other); // Copy assignment operator
    void operator=(Vector &&other);      // Move assignment operator

    // Capacity
    unsigned size() { return _size; }
    unsigned max_size() { return _max_size; }
    unsigned capacity() { return _capacity; }
    bool empty() { return _size == 0; }

    // Element access
    T operator[](unsigned n) { return _data[n]; }
    T at(unsigned n) { return _data[n]; }
    T front() { return _data[0]; }
    T back() { return _data[_size-1]; }
    T *data() { return _data; }

    // Modifiers
    void push_back(T value);
    bool pop_back();
    void append(const Vector &other);
    void clear();

    // Operations
    void reverse();

    VectorIterator<T> *create_iterator()
    {
        return new VectorIterator<T>(this);
    }
};

//
// Vector iterator class
//

template <class T>
class VectorIterator
{
    Vector<T> *_vector = nullptr;
    unsigned _current = -1;

public:
    VectorIterator(Vector<T> *vec) : _vector(vec) {}

    void first()
    {
        if (!_vector)
            return;
        _current = 0;
    }

    void next()
    {
        if (!_vector)
            return;

        _current++;
    }

    bool is_end()
    {
        if (!_vector)
            return false;

        return _current == _vector->_size;
    }

    T get_current()
    {
        return _vector->_data[_current];
    }
};

#include "vector.cpp"

#endif
