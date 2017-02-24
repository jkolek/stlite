#include "linkedlist.h"

#include <string>
#include <iostream>
#include <assert.h>

void print_int_list(LinkedList<int> &lst)
{
    LinkedListIterator<int> *iter = lst.create_iterator();
    iter->first();
    while (!iter->is_end())
    {
        std::cout << iter->get_current() << "  ";
        iter->next();
    }
    std::cout << std::endl;
}

int main()
{
    LinkedList<int> ls;

    assert(ls.empty() == true);
    assert(ls.size() == 0);

    ls.push_back(-1);
    ls.push_back(0);
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);

    assert(ls.front() == -1);
    assert(ls.back() == 5);

    ls.pop_front();
    ls.pop_back();

    assert(ls.empty() == false);
    assert(ls.size() == 5);
    assert(ls.front() == 0);
    assert(ls.back() == 4);
    assert(ls.get(0) == 0);
    assert(ls.get(2) == 2);
    assert(ls.get(4) == 4);

    ls.push_front(22);
    ls.push_front(33);

    assert(ls.front() == 33);

    ls.remove(33);
    ls.remove(2);
    ls.remove(4);

    assert(ls.front() == 22);
    assert(ls.back() == 3);
    assert(ls.size() == 4);
    assert(ls.get(0) == 22);
    assert(ls.get(2) == 1);
    assert(ls.get(3) == 3);

    // Copy constructor test
    LinkedList<int> ls3 = ls;

    assert(ls3.front() == 22);
    assert(ls3.back() == 3);
    assert(ls3.size() == ls.size());
    assert(ls3.get(0) == 22);
    assert(ls3.get(2) == 1);
    assert(ls3.get(3) == 3);

    LinkedList<int> ls4;
    // Copy assignment operator test
    ls4 = ls3;

    assert(ls4.front() == 22);
    assert(ls4.back() == 3);
    assert(ls4.size() == ls3.size());
    assert(ls4.get(0) == 22);
    assert(ls4.get(2) == 1);
    assert(ls4.get(3) == 3);

    constexpr unsigned arr_size = 5;
    int arr[arr_size] = { 44, 55, 66, 77, 88 };
    LinkedList<int> ls5(arr, arr_size);

    assert(ls5.size() == arr_size);
    assert(ls5.front() == 44);
    assert(ls5.back() == 88);
    assert(ls5.get(0) == 44);
    assert(ls5.get(2) == 66);
    assert(ls5.get(4) == 88);

    ls5.append(ls4);

    assert(ls5.size() == 9);
    assert(ls5.front() == 44);
    assert(ls5.back() == 3);

    ls.clear();

    assert(ls.empty() == true);
    assert(ls.size() == 0);

    ls.push_back(10);
    ls.push_back(11);
    ls.push_back(12);
    ls.push_back(13);
    ls.push_back(14);
    ls.push_back(15);
    ls.push_back(16);

    LinkedListIterator<int> *iter = ls.create_iterator();
    iter->first();
    unsigned n = 10;
    while (!iter->is_end())
    {
        assert(iter->get_current() == n);
        iter->next();
        n++;
    }

    ls.pop_front();
    ls.pop_back();

    assert(ls.front() == 11);
    assert(ls.back() == 15);

    // Move constructor test
    LinkedList<int> *tmp1 = new LinkedList<int>(arr, arr_size);
    LinkedList<int> ls6(std::move(*tmp1));
    delete tmp1;

    assert(ls6.size() == arr_size);
    assert(ls6.front() == 44);
    assert(ls6.back() == 88);

    // Move assignment operator test
    LinkedList<int> *tmp2 = new LinkedList<int>(arr, arr_size);
    LinkedList<int> ls7;
    ls7 = std::move(*tmp2);
    delete tmp2;

    assert(ls7.size() == arr_size);
    assert(ls7.front() == 44);
    assert(ls7.back() == 88);

    // Copy constructor test 2
    LinkedList<int> *tmp3 = new LinkedList<int>(arr, arr_size);
    LinkedList<int> ls8(*tmp3);
    delete tmp3;

    assert(ls8.size() == arr_size);
    assert(ls8.front() == 44);
    assert(ls8.back() == 88);

    // Copy assignment operator test 2
    LinkedList<int> *tmp4 = new LinkedList<int>(arr, arr_size);
    LinkedList<int> ls9;
    ls9 = *tmp4;
    delete tmp4;

    assert(ls9.size() == arr_size);
    assert(ls9.front() == 44);
    assert(ls9.back() == 88);

    return 0;
}
