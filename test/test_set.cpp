#include "../include/set.h"

#include <string>
#include <iostream>
#include <assert.h>

int main()
{
    stlite::Set<int> set;

    assert(set.empty() == true);
    assert(set.size() == 0);

    set.insert(-1);
    set.insert(0);
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.insert(5);

    assert(set.empty() == false);
    assert(set.size() == 7);

    set.clear();

    assert(set.empty() == true);
    assert(set.size() == 0);

    constexpr unsigned arr1_size = 7;
    int arr1[arr1_size] = { 7, 1, 3, 2, 5, 4, 6 };
    stlite::Set<int> set2(arr1, arr1_size);

    return 0;
}
