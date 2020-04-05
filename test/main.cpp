#include <iostream>
#include "queue.h"
using namespace std;
int main()
{
    using namespace Mynamespace;
    queue<int> a;
    #if 0
    a.push(1);
    a.front() = 2;
    cout<<a.front()<<endl;
    #endif
    return 0;
}