// The MIT License (MIT)
//
// STLite forward list
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

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "allocator.h"

#include <memory>

namespace stlite
{

// TODO: Support custom allocators:
//   http://www.cplusplus.com/reference/memory/allocator/
//   http://www.cplusplus.com/reference/memory/allocator_traits/

template <class T, class Alloc = Allocator<T>>
class ForwardList
{
    struct Element
    {
        T value;
        struct Element* next = nullptr;
        Element() = default;
        Element(const T& v) : value(v) {}
        Element(T&& v) : value(std::move(v)) {}
    };

    Element* _lst = nullptr; // First element of the list
    unsigned _max_size = 0;

    Allocator<T> allocator;

public:
    ForwardList() {}

    // This constructor creates list from the given array
    // ForwardList(T* arr, unsigned len);

    // Copy constructor
    // ForwardList(const ForwardList<T>& other);

    // Move constructor
    ForwardList(ForwardList<T, Alloc>&& other);

    ~ForwardList() { clear(); }

    // Copy assignment operator
    ForwardList<T, Alloc>& operator=(const ForwardList<T, Alloc>& other);

    // Move assignment operator
    ForwardList<T, Alloc>& operator=(ForwardList<T, Alloc>&& other);

    // Iterators
    class Iterator
    {
        Element* _p = nullptr;
        friend class List;

    public:
        Iterator() = default;

        Iterator(Element* e) : _p(e) {}

        // Only forward iteration is supported

        // Prefix increment operator
        Iterator & operator++()
        {
            if (_p)
                _p = _p->next;
            return *this;
        }

        // Postfix increment operator
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            if (_p)
                _p = _p->next;
            return tmp;
        }

        T& operator*()
        {
            if (_p)
                return _p->value;
        }

        bool operator==(const Iterator& other)
        {
            return other._p == _p;
        }

        bool operator!=(const Iterator& other)
        {
            return other._p != _p;
        }
    };

    Iterator begin() { return Iterator(_lst); }
    Iterator end() { return Iterator(); }

    // Capacity
    bool empty() { return _lst == nullptr; }
    unsigned max_size() { return _max_size; }

    // Element access
    // If the list is empty, the return value of these functions is undefined
    T front();

    // Modifiers

    // http://www.cplusplus.com/reference/forward_list/forward_list/assign/
    // void assign();
    // http://www.cplusplus.com/reference/forward_list/forward_list/emplace_front/
    template <class... Args> void emplace_front(Args&&... args);
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();
    //void emplace_after();
    //void insert_after(Iterator& pos, const T& value);
    //void erase_after(Iterator& pos);
    void swap();
    void resize();
    void clear();

    // Operations
    void remove(const T& value);
    void reverse();
};

//====----------------------------------------------------------------------====
// Implementations of methods
//====----------------------------------------------------------------------====

// template <class T>
// ForwardList<T>::ForwardList(T* arr, unsigned len)
// {
//     for (unsigned i = 0; i < len; i++)
//         push_back(arr[i]);
// }

// // Copy constructor
// template <class T>
// ForwardList<T>::ForwardList(const ForwardList<T>& other)
// {
//     if (&other != this && other._lst)
//     {
//         // Pointer to the first element
//         Element* p = other._lst->next;
//         while (p != other._lst)
//         {
//             push_back(p->value);
//             p = p->next;
//         }

//         push_back(p->value);
//     }
// }

// Move constructor
template <class T, class Alloc>
ForwardList<T, Alloc>::ForwardList(ForwardList<T, Alloc>&& other)
{
    if (&other != this)
    {
        _lst = other._lst;
        _max_size = other._max_size;

        other._lst = nullptr;
        other._max_size = 0;
    }
}

// Copy assignment operator
template <class T, class Alloc>
ForwardList<T, Alloc>& ForwardList<T, Alloc>::operator=(const ForwardList<T,
                                                        Alloc>& other)
{
    if (&other != this && other._lst)
    {
        clear();

        // Pointer to the first element
        Element* p = other._lst->next;
        while (p != other._lst)
        {
            push_back(p->value);
            p = p->next;
        }

        push_back(p->value);
    }
    return *this;
}

// Move assignment operator
template <class T, class Alloc>
ForwardList<T, Alloc>&ForwardList<T, Alloc>::operator=(ForwardList<T,
                                                       Alloc>&& other)
{
    if (&other != this)
    {
        clear();
        _lst = other._lst;
        _max_size = other._max_size;

        other._lst = nullptr;
        other._max_size = 0;
    }
    return *this;
}

// TODO: Check if _lst is nullptr?
template <class T, class Alloc>
T ForwardList<T, Alloc>::front()
{
    return _lst->value;
}

template <class T, class Alloc>
template <class... Args>
void ForwardList<T, Alloc>::emplace_front(Args&&... args)
{
    Element* e = new Element();
    // TODO: This is WRONG. How to make it generic?
    e->value = std::make_tuple(std::forward<Args>(args)...);

    if (_lst)
        e->next = _lst;

    _lst = e;
}

// Insert element at beginning of the list
template <class T, class Alloc>
void ForwardList<T, Alloc>::push_front(const T& value)
{
    Element* e = new Element(value);

    if (_lst)
        e->next = _lst;

    _lst = e;
}

// Insert element at beginning of the list
template <class T, class Alloc>
void ForwardList<T, Alloc>::push_front(T&& value)
{
    Element* e = new Element();
    e->value = std::move(value);

    if (_lst)
        e->next = _lst;

    _lst = e;
}

template <class T, class Alloc>
void ForwardList<T, Alloc>::pop_front()
{
    if (!_lst)
        return;

    if (!_lst->next)
    {
        // There is single element in the list
        delete _lst;
        _lst = nullptr;
    }
    else
    {
        Element* old = _lst;
        _lst = _lst->next;
        delete old;
    }
}

// template <class T>
// void ForwardList<T>::insert_after(Iterator& pos, const T& value)
// {
//     if (pos._prev)
//     {
//         Element* e = new Element(value);
//         e->next = pos._prev->next;
//         pos._prev->next = e;
//         pos._prev = pos._prev->next;
//     }
//     else
//     {
//         push_back(value);
//         pos._prev = _lst;
//     }
// }

// template <class T>
// void ForwardList<T>::erase_after(Iterator& pos)
// {
//     if (pos._prev)
//     {
//         Element* old = pos._prev->next;
//         pos._prev = pos._prev->next;
//         delete old;
//     }
// }

// // Append elements of other to end of the list
// template <class T>
// void ForwardList<T>::append(const ForwardList& other)
// {
//     if (other._lst)
//     {
//         // Pointer to the first element
//         Element* p = other._lst->next;
//         while (p != other._lst)
//         {
//             push_back(p->value);
//             p = p->next;
//         }

//         push_back(p->value);
//     }
// }

template <class T, class Alloc>
void ForwardList<T, Alloc>::clear()
{
    if (!_lst)
        return;

    Element* p = _lst;

    while (p)
    {
        Element* old = p;
        p = p->next;
        delete old;
    }

    _lst = nullptr;
}

// Remove element with the value from the list.
template <class T, class Alloc>
void ForwardList<T, Alloc>::remove(const T& value)
{
    if (!_lst)
        return;

    Element* p = _lst;
    Element* prev = nullptr;

    while (p->value != value)
    {
        prev = p;
        p = p->next;

        if (!p)
            return;
    }

    if (!prev)
        // First element in the list therefore we need to update _lst
        _lst = p->next;
    else
        prev->next = p->next;

    delete p;
}

template <class T, class Alloc>
void ForwardList<T, Alloc>::reverse()
{
    // TODO: Implement
}

} // namespace stlite

#endif
