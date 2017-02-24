// The MIT License (MIT)
//
// High-performance generic vector - implementation file
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

#include <algorithm>

template <class T>
Vector<T>::Vector(T *arr, unsigned len)
{
    _size = len;
    allocate_data(len);
    std::copy(arr, arr + _size, _data);
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
void Vector<T>::operator=(const Vector &other)
{
    if (&other != this)
    {
        if (_data)
            delete [] _data;

        _size = other._size;
        allocate_data(other._size);
        std::copy(other._data, other._data + _size, _data);
    }
}

// Move assignment operator
template <class T>
void Vector<T>::operator=(Vector &&other)
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
}

// Append element to end of the list
template <class T>
void Vector<T>::push_back(T value)
{
    if (!_data)
    {
        allocate_data(BLOCK_SIZE);
    }
    else if (_size >= _capacity)
    {
        unsigned new_capacity = _capacity + BLOCK_SIZE;

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
    {
        T tmp = _data[i];
        _data[i] = _data[j];
        _data[j] = tmp;
        i++;
        j--;
    }
}
