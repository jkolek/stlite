#include "../include/array.h"

#include <string>
#include <iostream>
#include <assert.h>

void test_iterator()
{
    stlite::Array<int> arr(5);

    assert(arr.size() == 5);

    arr[0] = -1;
    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 2;
    arr[4] = 3;

    int i = -1;
    stlite::Array<int>::Iterator iter = arr.begin();
    while (iter != arr.end())
    {
        assert(*iter == i);
        ++iter;
        ++i;
    }

    iter = arr.end();
    do
    {
        --i;
        --iter;
        assert(*iter == i);
    } while (iter != arr.begin());
}

int main()
{
    stlite::Array<int> arr(5);

    // assert(arr.empty() == true);
    assert(arr.size() == 5);

    arr[0] = -1;
    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 2;
    arr[4] = 3;

    assert(arr.front() == -1);
    assert(arr.back() == 3);

    assert(arr.at(0) == -1);
    assert(arr.at(2) == 1);
    assert(arr.at(4) == 3);

    assert(arr[0] == -1);
    assert(arr[2] == 1);
    assert(arr[4] == 3);

    int *data = arr.data();
    assert(data[0] == -1);
    assert(data[2] == 1);
    assert(data[4] == 3);

    // stlite::Vector<int> vec2;

    // assert(vec.capacity() == stlite::vector_block_size);

    // for (unsigned i = 0; i < 250; i++)
    //     vec2.push_back(i);

    // assert(vec2.capacity() == (stlite::vector_block_size * 3));

    // for (unsigned i = 0; i < 250; i++)
    //     assert(vec2[i] == i);

    // assert(vec2.max_size() == (unsigned) - 1);

    // stlite::Vector<int> vec3(80);

    // assert(vec3.capacity() == 80);
    // assert(vec3.size() == 80);

    // stlite::Vector<int> vec4(25, 33);

    // assert(vec4.capacity() == 25);
    // assert(vec4.size() == 25);

    // for (unsigned i = 0; i < 25; i++)
    //     assert(vec4[i] == 33);

    // vec.clear();

    // assert(vec.empty() == true);
    // assert(vec.size() == 0);

    // vec.push_back(10);
    // vec.push_back(11);
    // vec.push_back(12);
    // vec.push_back(13);
    // vec.push_back(14);
    // vec.push_back(15);
    // vec.push_back(16);

    // unsigned n = 10;
    // stlite::Vector<int>::Iterator it;
    // for (it = vec.begin(); it != vec.end(); ++it)
    // {
    //     assert(*it == n);
    //     n++;
    // }

    // constexpr unsigned arr_size = 5;
    // int arr[arr_size] = { 44, 55, 66, 77, 88 };

    // // Move constructor test
    // stlite::Vector<int> *tmp1 = new stlite::Vector<int>(arr, arr_size);
    // stlite::Vector<int> vec5(std::move(*tmp1));
    // delete tmp1;

    // assert(vec5.size() == arr_size);
    // assert(vec5.capacity() == arr_size);
    // assert(vec5.front() == 44);
    // assert(vec5.back() == 88);

    // // Move assignment operator test
    // stlite::Vector<int> *tmp2 = new stlite::Vector<int>(arr, arr_size);
    // stlite::Vector<int> vec6;
    // vec6 = std::move(*tmp2);
    // delete tmp2;

    // assert(vec6.size() == arr_size);
    // assert(vec6.capacity() == arr_size);
    // assert(vec6.front() == 44);
    // assert(vec6.back() == 88);

    // // Copy constructor test
    // stlite::Vector<int> *tmp3 = new stlite::Vector<int>(arr, arr_size);
    // stlite::Vector<int> vec7(*tmp3);
    // delete tmp3;

    // assert(vec7.size() == arr_size);
    // assert(vec7.capacity() == arr_size);
    // assert(vec7.front() == 44);
    // assert(vec7.back() == 88);

    // // Copy assignment operator test
    // stlite::Vector<int> *tmp4 = new stlite::Vector<int>(arr, arr_size);
    // stlite::Vector<int> vec8;
    // vec8 = *tmp4;
    // delete tmp4;

    // assert(vec8.size() == arr_size);
    // assert(vec8.capacity() == arr_size);
    // assert(vec8.front() == 44);
    // assert(vec8.back() == 88);

    // it = vec8.begin();
    // assert(*it == 44);
    // ++it;
    // assert(*it == 55);
    // it++;
    // assert(*it == 66);

    // assert(*(it++) == 66);

    // assert(*(++it) == 88);

    // // Test reverse

    // stlite::Vector<int> vec9(arr, arr_size);
    // vec9.reverse();

    // assert(vec9[0] == 88);
    // assert(vec9[1] == 77);
    // assert(vec9[2] == 66);
    // assert(vec9[3] == 55);
    // assert(vec9[4] == 44);

    // //std::vector<int> v(50);
    // //std::vector<int> v(50, 33);
    // //std::vector<int> v;
    // //v.push_back(22);
    // //std::cout << v.size() << std::endl;
    // //std::cout << v.capacity() << std::endl;

    // Initializer list test
    stlite::Array<int> arr10({ 44, 55, 66, 77, 88 });

    assert(arr10.size() == 5);
    assert(arr10.front() == 44);
    assert(arr10.back() == 88);
    assert(arr10[2] == 66);
    assert(arr10.at(2) == 66);

    return 0;
}
