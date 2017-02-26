// The MIT License (MIT)
//
// STLite queue
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

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

namespace stlite {

template <class T>
class Queue
{
    List<T> _data;

public:
    Queue() {}

    //Queue(const Queue<T> &other);               // Copy constructor
    //Queue(Queue<T> &&other);                    // Move constructor

    ~Queue() {}                      // Destructor

    //Queue<T>& operator=(const Queue<T> &other); // Copy assignment operator
    //Queue<T>& operator=(Queue<T> &&other);      // Move assignment operator

    // Capacity
    bool empty() { return _data.empty(); }
    unsigned size() { return _data.size(); }

    // Element access
    T front() { return _data.front(); }
    T back() { return _data.back(); }

    // Modifiers
    void push(T value) { _data.push_back(value); }
    bool pop() { _data.pop_front(); }
};

};

#endif
