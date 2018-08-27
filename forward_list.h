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

#include <memory>

namespace stlite
{

template <class T>
class ForwardList
{
    struct Element
    {
        T value;
        struct Element* next = nullptr;
        Element() = default;
        Element(T v) : value(v) {}
    };

    Element* _lst = nullptr; // First element of the list
    unsigned _max_size = 0;

public:
    ForwardList() {}

    // This constructor creates list from the given array
    ForwardList(T* arr, unsigned len);

    ForwardList(const ForwardList<T>& other);               // Copy constructor
    ForwardList(ForwardList<T>&& other);                    // Move constructor

    ~ForwardList() { clear(); }                      // Destructor

    ForwardList<T>& operator=(const ForwardList<T>& other); // Copy assignment operator

    ForwardList<T>& operator=(ForwardList<T>&& other);      // Move assignment operator

    // // Iterators
    // class Iterator
    // {
    //     // This pointer points to previous Element of the current Element.
    //     // This way is more practical when inserting and erasing Elements.
    //     Element *_prev;
    //     bool _is_end = false;
    //     bool _next_is_end = false;
    //     friend class List;

    //     bool test_end(const Iterator &other)
    //     {
    //         if (_next_is_end)
    //             return true;

    //         if (_prev->next == other._prev)
    //             _next_is_end = true;

    //         return false;
    //     }

    // public:
    //     Iterator() {}

    //     Iterator(Element *e) : _prev(e) {}
    //     Iterator(Element *e, bool is_end) : _prev(e), _is_end(is_end) {}

    //     // Prefix increment operator
    //     Iterator & operator++()
    //     {
    //         if (_prev)
    //             _prev = _prev->next;
    //         return *this;
    //     }

    //     // Postfix increment operator
    //     Iterator operator++(int)
    //     {
    //         Iterator tmp = *this;
    //         if (_prev)
    //             _prev = _prev->next;
    //         return tmp;
    //     }

    //     T & operator*()
    //     {
    //         if (_prev)
    //             return _prev->next->value;
    //     }

    //     bool operator==(Iterator other)
    //     {
    //         if (!_prev || !other._prev)
    //             return false;

    //         if (other._is_end)
    //             return test_end(other);

    //         return other._prev->next == _prev->next;
    //     }

    //     bool operator!=(Iterator other)
    //     {
    //         if (!_prev || !other._prev)
    //             return false;

    //         if (other._is_end)
    //             return !test_end(other);

    //         return other._prev->next != _prev->next;
    //     }
    // };

    // Iterator begin() { return Iterator(_lst); }
    // Iterator end() { return Iterator(_lst, true); }

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
    // void emplace_front();
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

template <class T>
ForwardList<T>::ForwardList(T* arr, unsigned len)
{
    for (unsigned i = 0; i < len; i++)
        push_back(arr[i]);
}

// Copy constructor
template <class T>
ForwardList<T>::ForwardList(const ForwardList<T>& other)
{
    if (&other != this && other._lst)
    {
        // Pointer to the first element
        Element* p = other._lst->next;
        while (p != other._lst)
        {
            push_back(p->value);
            p = p->next;
        }

        push_back(p->value);
    }
}

// Move constructor
template <class T>
ForwardList<T>::ForwardList(ForwardList<T>&& other)
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
template <class T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
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
template <class T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList&& other)
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
template <class T>
T ForwardList<T>::front()
{
    return _lst->value;
}

// Insert element at beginning of the list
template <class T>
void ForwardList<T>::push_front(const T& value)
{
    Element* e = new Element(value);

    if (!_lst)
    {
        _lst = e;
    }
    else
    {
        e->next = _lst;
        _lst = e;
    }
}

// Insert element at beginning of the list
template <class T>
void ForwardList<T>::push_front(T&& value)
{
    Element* e = new Element();
    e->value = std::move(value);

    if (!_lst)
    {
        _lst = e;
    }
    else
    {
        e->next = _lst;
        _lst = e;
    }
}

template <class T>
void ForwardList<T>::pop_front()
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

template <class T>
void ForwardList<T>::clear()
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
template <class T>
void ForwardList<T>::remove(const T& value)
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

template <class T>
void ForwardList<T>::reverse()
{
    // TODO: Implement
}

} // namespace stlite

#endif
