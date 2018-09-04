// The MIT License (MIT)
//
// STLite set
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

#ifndef SET_H
#define SET_H

#include "algorithms.h"

#include <algorithm>

namespace stlite
{

template <class T>
class SetIterator;

template <class T>
struct Node
{
    T value;
    struct Node *left = nullptr;
    struct Node *right = nullptr;
    Node(T v) : value(v) {}
};

template <class T>
class Set
{
    Node<T> *_root = nullptr;
    unsigned _size = 0;
    unsigned _max_size = -1;

    friend class SetIterator<T>;

    void insert_element(Node<T>* &node, T value)
    {
        if (!node)
        {
            node = new Node<T>(value);
            _size++;
        }
        else
        {
            if (value < node->value)
                insert_element(node->left, value);
            else
                insert_element(node->right, value);
        }
    }

    void remove_elements(Node<T>* &node)
    {
        if (!node)
            return;

        remove_elements(node->left);
        remove_elements(node->right);

        delete node;
    }

    Node<T> *array_to_tree(T *arr, int lo, int hi)
    {
        if (lo <= hi)
        {
            int middle = (lo + hi) / 2;
            Node<T> *n = new Node<T>(arr[middle]);
            n->left = array_to_tree(arr, lo, middle-1);
            n->right = array_to_tree(arr, middle+1, hi);
            return n;
        }
        return nullptr;
    }

public:
    Set() {}

    // This constructor creates set from the given array
    Set(const T *arr, unsigned len)
    {
        // TODO: Implement. Sort array and insert the elements.
        T tmparr[len];
        std::copy(arr, arr + len, tmparr);
        quick_sort<T>(tmparr, len);
        _root = array_to_tree(tmparr, 0, len-1);
    }

    // Copy constructor
    Set(const Set<T> &other) {}

    // Move constructor
    Set(Set<T> &&other)
    {
        if (&other != this)
        {
            _root = other._root;
            _size = other._size;

            other._root = nullptr;
            other._size = 0;
        }
    }

    // Destructor
    ~Set() { clear(); }

    // Copy assignment operator
    Set<T>& operator=(const Set<T> &other)
    {
        // TODO: Implement
        return *this;
    }

    // Move assignment operator
    Set<T>& operator=(Set<T> &&other)
    {
        if (&other != this)
        {
            clear();
            _root = other._root;
            _size = other._size;

            other._root = nullptr;
            other._size = 0;
        }
        return *this;
    }

    // Capacity
    bool empty() { return _root == nullptr; }
    unsigned size() { return _size; }
    unsigned max_size() { return _max_size; }

    // Modifiers

    void insert(T value) { insert_element(_root, value); }

    void erase(T value) {}

    void clear()
    {
        if (!_root)
            return;

        remove_elements(_root);
        _root = nullptr;
        _size = 0;
    }

    // Operations
    void find(T value) {}

    unsigned count(T value)
    {
        if (!_root)
            return 0;

        return 0;
    }

    SetIterator<T>* create_iterator()
    {
        return new SetIterator<T>(this);
    }
};

} // namespace stlite

#endif
