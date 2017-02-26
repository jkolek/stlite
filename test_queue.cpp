#include "queue.h"

#include <assert.h>

int main()
{
    stlite::Queue<int> q;

    assert(q.empty() == true);
    assert(q.size() == 0);

    q.push(-1);
    q.push(0);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    assert(q.empty() == false);
    assert(q.size() == 7);
    assert(q.front() == -1);
    assert(q.back() == 5);

    q.pop();
    assert(q.front() == 0);

    q.pop();
    assert(q.front() == 1);

    while (!q.empty())
        q.pop();

    assert(q.empty() == true);
    assert(q.size() == 0);

    return 0;
}
