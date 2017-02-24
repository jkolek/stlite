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

template <class T>
Vector<T>::Vector(T *arr, unsigned len)
{
    for (unsigned i = 0; i < len; i++)
        push_back(arr[i]);
    _capacity = len;
}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector &other)
{
    // TODO: Implement
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
    // TODO: Implement
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
        _data = new T[BLOCK_SIZE];
        _capacity = BLOCK_SIZE;
    }
    else if (_size >= _capacity)
    {
        unsigned new_capacity = _capacity + BLOCK_SIZE;

        if (new_capacity > _max_size)
            return;

        T *tmp = new T[new_capacity];
        for (unsigned i = 0; i < _capacity; i++)
            tmp[i] = _data[i];
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

// Append elements of other to end of the list
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
