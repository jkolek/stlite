#include "stack.h"

#include <assert.h>

int main()
{
    stlite::Stack<int> s;

    assert(s.empty() == true);
    assert(s.size() == 0);

    s.push(-1);
    s.push(0);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    assert(s.empty() == false);
    assert(s.size() == 7);
    assert(s.top() == 5);

    s.pop();
    assert(s.top() == 4);

    s.pop();
    assert(s.top() == 3);

    while (!s.empty())
        s.pop();

    assert(s.empty() == true);
    assert(s.size() == 0);

    return 0;
}
