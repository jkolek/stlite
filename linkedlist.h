// The MIT License (MIT)
//
// High-performance generic linked list - header file
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

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
class LinkedListIterator;

template <class T>
struct Element
{
    T value;
    struct Element *next = nullptr;
    Element(T v) : value(v) {}
};

template <class T>
class LinkedList
{
    //
    //                                 _lst
    //  +---+   +---+   +---+   +---+    |
    //  | 1 |-->| 2 |-->| 3 |-->| 4 |<---+
    //  +---+   +---+   +---+   +---+
    //    ^                       |
    //    |                       |
    //    +-----------------------+
    //

    Element<T> *_lst = nullptr;
    unsigned _size = 0;

    friend class LinkedListIterator<T>;

public:
    LinkedList() {}

    // This constructor creates list from the given array
    LinkedList(T *arr, unsigned len);

    LinkedList(const LinkedList<T> &other);     // Copy constructor
    LinkedList(LinkedList<T> &&other);          // Move constructor

    ~LinkedList() { clear(); }                  // Destructor

    void operator=(const LinkedList<T> &other); // Copy assignment operator
    void operator=(LinkedList<T> &&other);      // Move assignment operator

    // Capacity
    bool empty() { return _lst == nullptr; }
    unsigned size() { return _size; }

    // Element access
    // If the list is empty, the return value of these functions is undefined
    T front() { if (_lst) return _lst->next->value; }
    T back() { if (_lst) return _lst->value; }
    T get(unsigned pos);

    // Modifiers
    void push_back(T value);
    void push_front(T value);
    bool pop_front();
    bool pop_back();
    void append(const LinkedList &other);
    void clear();

    // Operations
    bool remove(T value);
    bool remove_pos(unsigned pos);
    void reverse();

    LinkedListIterator<T> *create_iterator()
    {
        return new LinkedListIterator<T>(this);
    }
};

//
// Linked list iterator class
//

template <class T>
class LinkedListIterator
{
    LinkedList<T> *_list;
    Element<T> *_current = nullptr;
    bool _next_is_end = false;

public:
    LinkedListIterator(LinkedList<T> *ls) : _list(ls) {}

    void first()
    {
        if (!_list)
            return;
        _current = _list->_lst->next;
        _next_is_end = false;
    }

    void next()
    {
        if (!_current)
            return;

        _current = _current->next;
    }

    bool is_end()
    {
        if (!_list)
            return false;

        if (_next_is_end)
            return true;

        // There is one more element to iterate
        if (_current == _list->_lst)
            _next_is_end = true;

        return false;
    }

    T get_current()
    {
        if (_current)
            return _current->value;
    }
};

#include "linkedlist.cpp"

#endif
