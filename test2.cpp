#include "linkedlist.h"

#include <vector>
#include <list>

#define MAX_NUM 50000000

void test_linked_list_push_back()
{
    LinkedList<int> lst;

    for (unsigned i = 0; i < MAX_NUM; i++)
        lst.push_back(i);

    //while (!lst.empty())
    //    lst.pop_back();

    //while (!lst.empty())
    //    lst.pop_front();

    lst.clear();
}

void test_std_linked_list_push_back()
{
    std::list<int> lst;

    for (unsigned i = 0; i < MAX_NUM; i++)
        lst.push_back(i);

    while (!lst.empty())
        lst.pop_front();
}

void test_vector_push_back()
{
    std::vector<int> vec;

    for (unsigned i = 0; i < MAX_NUM; i++)
        vec.push_back(i);
}

void test_linked_list_push_front()
{
    LinkedList<int> lst;

    for (unsigned i = 0; i < MAX_NUM; i++)
        lst.push_front(i);
}

void test_std_linked_list_push_front()
{
    std::list<int> lst;

    for (unsigned i = 0; i < MAX_NUM; i++)
        lst.push_front(i);
}

void test_vector_push_front()
{
    std::vector<int> vec;

    //for (unsigned i = 0; i < MAX_NUM; i++)
    //    vec.push_front(i);
}

int main()
{
    test_linked_list_push_back();
    //test_std_linked_list_push_back();
    //test_vector_push_back();

    //test_linked_list_push_front();
    //test_std_linked_list_push_front();
    //test_vector_push_front();

    return 0;
}
