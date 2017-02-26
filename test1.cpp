#include "list.h"
#include "algorithms.h"

#include <string>
#include <iostream>

void print_int_list(stlite::List<int> &lst)
{
/*    stlite::Listiterator<int> *iter = lst.create_iterator();
    iter->first();
    while (!iter->is_end())
    {
        std::cout << iter->get_current() << "  ";
        iter->next();
    }
    std::cout << std::endl;*/
}

int pivot(int *arr, unsigned size, int lo, int hi)
{
    int pval = arr[hi];
    int i = lo-1;
    int j = lo;
    while (j < hi)
    {
        if (arr[j] < pval)
        {
            i++;
            stlite::swap(arr[i], arr[j]);
        }
        j++;
    }
    i++;
    stlite::swap(arr[i], arr[hi]);
    return i;
}

void quick_sort(int *arr, unsigned size, int lo, int hi)
{
    if (lo < hi)
    {
        int pi = pivot(arr, size, lo, hi);
        quick_sort(arr, size, lo, pi-1);
        quick_sort(arr, size, pi+1, hi);
    }
}


int main()
{
    stlite::List<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    //ls.push_back(6);
    //ls.push_back(7);
    print_int_list(ls);
    std::cout << ls.size() << std::endl;

    stlite::List<int> ls2;
    ls2.push_front(1);
    ls2.push_front(2);
    ls2.push_front(3);
    ls2.push_front(4);
    ls2.push_front(5);
    //ls2.push_front(6);
    //ls2.push_front(7);
    print_int_list(ls2);

    ls.remove(3);
    ls.remove(5);
    ls.remove(1);
    //ls.remove_last();
    //ls.remove_first();
    print_int_list(ls);
    std::cout << ls.size() << std::endl;

    std::cout << "ls2.get(0) == " << ls2.get(0) << std::endl;
    std::cout << "ls2.get(3) == " << ls2.get(3) << std::endl;
    std::cout << "ls2.get(5) == " << ls2.get(5) << std::endl;
    std::cout << "ls2.front() == " << ls2.front() << std::endl;
    std::cout << "ls2.back() == " << ls2.back() << std::endl;

    stlite::List<int> ls3 = ls2;
    print_int_list(ls3);
    stlite::List<int> ls4;
    ls4 = ls3;
    print_int_list(ls4);

    int arr[6] = { 22, 33, 44, 55, 66, 77 };
    stlite::List<int> ls5(arr, 6);
    print_int_list(ls5);

    ls5.append(ls4);

    print_int_list(ls5);

    ls5.reverse();

    print_int_list(ls5);

    //list<int> ls6(new list<int>(arr, 6));
    //ls6.print();

    /*list<std::string> ls6;
    ls6.push_back("hello");
    ls6.push_back("world");
    ls6.print();

    std::cout << "ls6.get(5) == " << ls6.get(5) << std::endl;*/

    constexpr unsigned asize = 5;
    int a[asize] = { 5, 2, 3, 1, 7 };
    quick_sort(a, asize, 0, asize-1);

    for (unsigned i = 0; i < asize; i++)
    {
        std::cout << a[i] << std::endl;
    }

    std::cout << std::endl << stlite::binary_search(5, a, asize) << std::endl;
}
