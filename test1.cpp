#include "linkedlist.h"

#include <string>
#include <iostream>

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
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    //ls.push_back(6);
    //ls.push_back(7);
    print_int_list(ls);
    std::cout << ls.size() << std::endl;

    LinkedList<int> ls2;
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

    LinkedList<int> ls3 = ls2;
    print_int_list(ls3);
    LinkedList<int> ls4;
    ls4 = ls3;
    print_int_list(ls4);

    int arr[6] = { 22, 33, 44, 55, 66, 77 };
    LinkedList<int> ls5(arr, 6);
    print_int_list(ls5);

    ls5.append(ls4);

    print_int_list(ls5);

    ls5.reverse();

    print_int_list(ls5);

    //LinkedList<int> ls6(new LinkedList<int>(arr, 6));
    //ls6.print();

    /*LinkedList<std::string> ls6;
    ls6.push_back("hello");
    ls6.push_back("world");
    ls6.print();

    std::cout << "ls6.get(5) == " << ls6.get(5) << std::endl;*/


}
