// The MIT License (MIT)
//
// STLite linked list
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

#ifndef LIST_H
#define LIST_H

namespace stlite
{

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

    List(const List<T> &other);               // Copy constructor
    List(List<T> &&other);                    // Move constructor

    ~List() { clear(); }                      // Destructor

    List<T>& operator=(const List<T> &other); // Copy assignment operator

    List<T>& operator=(List<T> &&other);      // Move assignment operator

    // Iterators
    class Iterator
    {
        // This pointer points to previous Element of the current Element.
        // This way is more practical when inserting and erasing Elements.
        Element *_prev;
        bool _is_end = false;
        bool _next_is_end = false;
        friend class List;

        bool test_end(const Iterator &other)
        {
            if (_next_is_end)
                return true;

            if (_prev->next == other._prev)
                _next_is_end = true;

            return false;
        }

    public:
        Iterator() {}

        Iterator(Element *e) : _prev(e) {}
        Iterator(Element *e, bool is_end) : _prev(e), _is_end(is_end) {}

        // Prefix increment operator
        Iterator & operator++()
        {
            if (_prev)
                _prev = _prev->next;
            return *this;
        }

        // Postfix increment operator
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            if (_prev)
                _prev = _prev->next;
            return tmp;
        }

        T & operator*()
        {
            if (_prev)
                return _prev->next->value;
        }

        bool operator==(Iterator other)
        {
            if (!_prev || !other._prev)
                return false;

            if (other._is_end)
                return test_end(other);

            return other._prev->next == _prev->next;
        }

        bool operator!=(Iterator other)
        {
            if (!_prev || !other._prev)
                return false;

            if (other._is_end)
                return !test_end(other);

            return other._prev->next != _prev->next;
        }
    };

    Iterator begin() { return Iterator(_lst); }
    Iterator end() { return Iterator(_lst, true); }

    // Capacity
    bool empty() { return _lst == nullptr; }
    unsigned size() { return _size; }

    // Element access
    // If the list is empty, the return value of these functions is undefined
    T front() { if (_lst) return _lst->next->value; }
    T back() { if (_lst) return _lst->value; }
    T at(unsigned pos);

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

//====----------------------------------------------------------------------====
// Implementations of methods
//====----------------------------------------------------------------------====

template <class T>
List<T>::List(T *arr, unsigned len)
{
    for (unsigned i = 0; i < len; i++)
        push_back(arr[i]);
}

// Copy constructor
template <class T>
List<T>::List(const List<T> &other)
{
    if (&other != this && other._lst)
    {
        // Pointer to the first element
        Element *p = other._lst->next;
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
List<T>::List(List<T> &&other)
{
    if (&other != this)
    {
        _lst = other._lst;
        _size = other._size;

        other._lst = nullptr;
        other._size = 0;
    }
}

// Copy assignment operator
template <class T>
List<T>& List<T>::operator=(const List<T> &other)
{
    if (&other != this && other._lst)
    {
        clear();

        // Pointer to the first element
        Element *p = other._lst->next;
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
List<T>& List<T>::operator=(List &&other)
{
    if (&other != this)
    {
        clear();
        _lst = other._lst;
        _size = other._size;

        other._lst = nullptr;
        other._size = 0;
    }
    return *this;
}

template <class T>
T List<T>::at(unsigned pos)
{
    if (_lst)
    {
        unsigned n = 0;

        // Pointer to the first element
        Element *p = _lst->next;
        while (n != pos && p != _lst)
        {
            p = p->next;
            n++;
        }

        if ((n == pos) || (p == _lst && n+1 == pos))
            return p->value;
    }
}

// Append element to end of the list
template <class T>
void List<T>::push_back(T value)
{
    Element *e = new Element(value);

    if (!_lst)
    {
        e->next = e;
    }
    else
    {
        e->next = _lst->next;
        _lst->next = e;
    }

    _lst = e;
    _size++;
}

// Insert element at beginning of the list
template <class T>
void List<T>::push_front(T value)
{
    Element *e = new Element(value);

    if (!_lst)
    {
        e->next = e;
        _lst = e;
    }
    else
    {
        e->next = _lst->next;
        _lst->next = e;
    }

    _size++;
}
// Two possible cases:
//   - The list contains a single element, we remove it and set _lst to nullptr
//     and _size to 0.
//   - The list has more than one element. Removing a first element from the
//     list is efficient and easy, just remove _lst->next which points to the
//     first element of the list.
template <class T>
bool List<T>::pop_front()
{
    if (!_lst)
        return false;

    if (_lst->next == _lst)
    {
        delete _lst;
        _lst = nullptr;
        _size = 0;
    }
    else
    {
        Element *old = _lst->next;
        _lst->next = _lst->next->next;
        delete old;
        _size--;
    }

    return false;
}

template <class T>
bool List<T>::pop_back()
{
    if (!_lst)
        return false;

    if (_lst->next == _lst)
    {
        // The list contains a single element

        delete _lst;
        _lst = nullptr;
        _size = 0;
    }
    else
    {
        // We need to traverse entire list to get "next" pointer that points to
        // the _lst.

        Element *p = _lst->next;
        while (p->next != _lst)
            p = p->next;
        p->next = _lst->next;
        delete _lst;
        _lst = p;
        _size--;
    }

    return true;
}

template <class T>
void List<T>::insert(Iterator &pos, const T &value)
{
    if (pos._prev)
    {
        Element *e = new Element(value);
        e->next = pos._prev->next;
        pos._prev->next = e;
        pos._prev = pos._prev->next;
    }
    else
    {
        push_back(value);
        pos._prev = _lst;
    }
}

template <class T>
void List<T>::erase(Iterator &pos)
{
    if (pos._prev)
    {
        Element *old = pos._prev->next;
        pos._prev = pos._prev->next;
        delete old;
    }
}

// Append elements of other to end of the list
template <class T>
void List<T>::append(const List &other)
{
    if (other._lst)
    {
        // Pointer to the first element
        Element *p = other._lst->next;
        while (p != other._lst)
        {
            push_back(p->value);
            p = p->next;
        }

        push_back(p->value);
    }
}

template <class T>
void List<T>::clear()
{
    if (!_lst)
        return;

    Element *p = _lst;

    while (p->next != _lst)
    {
        Element *old = _lst->next;
        _lst->next = _lst->next->next;
        delete old;
    }

    delete _lst;
    _lst = nullptr;
    _size = 0;
}

// Remove element with the value from the list.
// Return true if element has been removed, false otherwise.
template <class T>
bool List<T>::remove(T value)
{
    if (!_lst)
        return false;

    if (_lst->next == _lst)
    {
        if (_lst->value == value)
        {
            delete _lst;
            _size--;
            return true;
        }

        return false;
    }

    // Pointer to the last element
    Element *p = _lst;

    while (p->next->value != value &&  p->next != _lst)
        p = p->next;

    if (p->next->value == value)
    {
        if (p->next == _lst)
            _lst = p;

        Element *old = p->next;
        p->next = p->next->next;
        delete old;
        _size--;

        return true;
    }

    return false;
}

// Remove element at the position "pos" in the list.
// Return true if element has been removed, false otherwise.
template <class T>
bool List<T>::remove_pos(unsigned pos)
{
    if (!_lst)
        return false;

    // TODO: Implement

    return false;
}

template <class T>
void List<T>::reverse()
{
    // TODO: Implement
}

} // namespace stlite

#endif
