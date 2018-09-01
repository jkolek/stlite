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
#include "allocator.h"

#ifdef USE_STL
#include <algorithm>
#endif

namespace stlite
{

constexpr unsigned vector_block_size = 100;

template <class T, class Alloc = Allocator<T>>
class Vector
{
    T* _data = nullptr;
    size_t _max_size = -1;
    size_t _capacity = 0;
    size_t _size = 0;
    Alloc allocator;

    void allocate_data(size_t capacity)
    {
        _capacity = capacity;
        _data = allocator.allocate(capacity);
    }

    void check_and_alloc_data();

public:
    Vector() {}

    // Fill constructors
    explicit Vector(size_t n)
    {
        _size = n;
        allocate_data(n);
    }

    explicit Vector(size_t n, const T& val)
    {
        _size = n;
        allocate_data(n);
        for (unsigned i = 0; i < n; i++)
            _data[i] = val;
    }

    // This constructor creates list from the given array
    Vector(T* arr, size_t len);

#ifdef USE_STL
    Vector(std::initializer_list<T> initlst);
#endif

    Vector(const Vector& other);               // Copy constructor
    Vector(Vector&& other);                    // Move constructor

    ~Vector() { allocator.deallocate(_data, _capacity); }

    Vector<T>& operator=(const Vector& other); // Copy assignment operator
    Vector<T>& operator=(Vector&& other);      // Move assignment operator

    // Iterators
    class Iterator
    {
        T* _data = nullptr;
        unsigned _current = -1;
    public:
        Iterator() {}
        Iterator(T* data, unsigned n) : _data(data), _current(n) {}

        // Prefix increment operator
        Iterator& operator++()
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
    
        // Prefix decrement operator
        Iterator& operator--()
        {
            --_current;
            return *this;
        }

        // Postfix decrement operator
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --_current;
            return tmp;
        }

        T& operator*()
        {
            return _data[_current];
        }

        bool operator==(const Iterator& other)
        {
            return other._current == _current;
        }

        bool operator!=(const Iterator& other)
        {
            return other._current != _current;
        }
    };

    Iterator begin() { return Iterator(_data, 0); }
    // TODO: This is invalid end
    Iterator end() { return Iterator(nullptr, _size); }

    // Capacity
    size_t size() const { return _size; }
    size_t max_size() const { return _max_size; }
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    // Element access
    // http://www.cplusplus.com/reference/vector/vector/operator[]/
    // We must be able to assign values via []:
    //   arr[2] = 33;
    T& operator[](int n) { return _data[n]; }
    T operator[](int n) const { return _data[n]; }

    // http://www.cplusplus.com/reference/vector/vector/at/
    T at(unsigned n)
    {
        if (n < _size)
            return _data[n];
        // TODO: Throw out_of_range exception
    }

    T& front() { return _data[0]; }
    T& back() { return _data[_size-1]; }
    T* data() { return _data; }

    // Modifiers
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void append(const Vector& other);
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

template <class T, class Alloc>
void Vector<T, Alloc>::check_and_alloc_data()
{
    if (!_data)
    {
        allocate_data(vector_block_size);
    }
    else if (_size >= _capacity)
    {
        size_t new_capacity = _capacity + vector_block_size;

        if (new_capacity > _max_size)
            return;

        T* tmp = allocator.allocate(new_capacity);
        copy<T>(_data, _data + _size, tmp);
        allocator.deallocate(_data, _capacity);
        _data = tmp;
        _capacity = new_capacity;
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(T *arr, size_t len)
{
    _size = len;
    allocate_data(len);
    copy<T>(arr, arr + _size, _data);
}

#ifdef USE_STL
template <class T, class Alloc>
Vector<T, Alloc>::Vector(std::initializer_list<T> initlst)
{
    _size = initlst.size();
    allocate_data(_size);

    unsigned idx = 0;

    for (auto x : initlst)
        _data[idx++] = x;
}
#endif

// Copy constructor
template <class T, class Alloc>
Vector<T, Alloc>::Vector(const Vector& other)
{
    _size = other._size;
    allocate_data(other._size);
    copy<T>(other._data, other._data + _size, _data);
}

// Move constructor
template <class T, class Alloc>
Vector<T, Alloc>::Vector(Vector&& other)
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
template <class T, class Alloc>
Vector<T>& Vector<T, Alloc>::operator=(const Vector& other)
{
    if (&other != this)
    {
        // if (_data)
        //     delete [] _data;
        allocator.deallocate(_data, _capacity);

        _size = other._size;
        allocate_data(other._size);
        copy<T>(other._data, other._data + _size, _data);
    }
    return *this;
}

// Move assignment operator
template <class T, class Alloc>
Vector<T>& Vector<T, Alloc>::operator=(Vector&& other)
{
    if (&other != this)
    {
        // if (_data)
        //     delete [] _data;
        allocator.deallocate(_data, _capacity);

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
template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const T& value)
{
    check_and_alloc_data();
    _data[_size++] = value;
}

// Append element to end of the list
template <class T, class Alloc>
void Vector<T, Alloc>::push_back(T&& value)
{
    check_and_alloc_data();
    _data[_size++] = static_cast<T &&>(value);
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back()
{
    if (_size > 0)
        _size--;
}

// Append elements of other to end of the vector
template <class T, class Alloc>
void Vector<T, Alloc>::append(const Vector& other)
{
    // TODO: Implement
}

template <class T, class Alloc>
void Vector<T, Alloc>::clear()
{
    _size = 0;
}

template <class T, class Alloc>
void Vector<T, Alloc>::reverse()
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
