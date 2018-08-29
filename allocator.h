// The MIT License (MIT)
//
// STLite allocator
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

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

namespace stlite
{

typedef unsigned int size_t;

template <class T>
class Allocator
{
public:
    Allocator();
    ~Allocator();

    // Return address
    //address

    // Allocate block of storage
    T* allocate(size_t n);

    // Release block of storage
    void deallocate(T* p, size_t n);

    // Maximum size possible to allocate
    // max_size

    // Construct an object
    // construct

    // Destroy an object
    // destroy
};

template <class T>
Allocator<T>::Allocator()
{
}

template <class T>
Allocator<T>::~Allocator()
{
}

template <class T>
T* Allocator<T>::allocate(size_t n)
{
    return new T();
}

template <class T>
void Allocator<T>::deallocate(T* p, size_t n)
{
    delete p;
}

} // namespace stlite

#endif
