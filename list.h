// The MIT License (MIT)
//
// STLite linked list - header file
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

#ifndef LIST_H
#define LIST_H

namespace stlite {

template <class T>
class List
{
    struct Element
    {
        T value;
        struct Element *next = nullptr;
        Element(T v) : value(v) {}
    };

    //
    //                                 _lst
    //  +---+   +---+   +---+   +---+    |
    //  | 1 |-->| 2 |-->| 3 |-->| 4 |<---+
    //  +---+   +---+   +---+   +---+
    //    ^                       |
    //    |                       |
    //    +-----------------------+
    //

    Element *_lst = nullptr;
    unsigned _size = 0;

public:
    List() {}

    // This constructor creates list from the given array
    List(T *arr, unsigned len);

    List(const List<T> &other); // Copy constructor
    List(List<T> &&other);      // Move constructor

    ~List() { clear(); }              // Destructor

    // Copy assignment operator
    List<T>& operator=(const List<T> &other);

    // Move assignment operator
    List<T>& operator=(List<T> &&other);

    // Iterators
    class Iterator
    {
        // This pointer points to previous Element of the current Element.
        // This way is more practical when inserting and erasing Elements.
        Element *_prev;
        friend class List;
    public:
        Iterator() {}

        Iterator(Element *e)
        {
            _prev = e;
        }

        // Prefix increment operator
        Iterator & operator++()
        {
            _prev = _prev->next;
            return *this;
        }

        // Postfix increment operator
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            _prev = _prev->next;
            return tmp;
        }

        T & operator*()
        {
            return _prev->next->value;
        }

        bool operator==(Iterator other)
        {
            return other._prev->next == _prev->next;
        }

        bool operator!=(Iterator other)
        {
            return other._prev->next != _prev->next;
        }
    };

    Iterator begin() { return Iterator(_lst); }
    // TODO: This is invalid end
    Iterator end() { return Iterator(_lst); }

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
    void insert(Iterator &pos, const T &value);
    void erase(Iterator &pos);
    void append(const List &other);
    void clear();

    // Operations
    bool remove(T value);
    bool remove_pos(unsigned pos);
    void reverse();
};

//
// Linked list Iterator class
//

/*template <class T>
class listIterator
{
    list<T> *_list;
    Element *_current = nullptr;
    bool _next_is_end = false;

public:
    listIterator(list<T> *ls) : _list(ls) {}

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

        // There is one more Element to iterate
        if (_current == _list->_lst)
            _next_is_end = true;

        return false;
    }

    T get_current()
    {
        if (_current)
            return _current->value;
    }
};*/

#include "list.cpp"

};

#endif
