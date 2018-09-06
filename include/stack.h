// The MIT License (MIT)
//
// STLite stack
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

#ifndef STACK_H
#define STACK_H

#include "vector.h"

namespace stlite
{

template <class T>
class Stack
{
    Vector<T> _data;

public:
    Stack() {}

    Stack(const Stack& other) {}                 // Copy constructor
    Stack(Stack&& other) {}                      // Move constructor

    ~Stack() {}                                // Destructor

    //Stack<T>& operator=(const Stack &other); // Copy assignment operator
    //Stack<T>& operator=(Stack &&other);      // Move assignment operator

    // Capacity
    bool empty() const { return _data.empty(); }
    size_t size() const { return _data.size(); }

    // Element access
    T& top() { return _data.back(); }

    const T& top() const { return _data.back(); }

    // Modifiers
    void push(T value) { _data.push_back(value); }
    void pop() { _data.pop_back(); };
};

} // namespace stlite

#endif
