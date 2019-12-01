#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    MyQueue q;
    q.enQueue(5);
    q.enQueue(3);
    vector<int> data{1,2,3,4,5};
    MycycleQueue *p = new MycycleQueue(5);
    p->enQueue(8);
    p->enQueue(9);
    p->enQueue(10);
    p->enQueue(11);
    p->enQueue(12);
    p->deQueue();
    p->enQueue(13);
    p->print_queue();
    delete p;
   // p->print_queue();
    #if 0
    if (!q.isEmpty()) {
        cout << q.Qfront() << endl;
    }
    q.deQueue();
    if (!q.isEmpty()) {
        cout << q.Qfront() << endl;
    }
    q.deQueue();
    if (!q.isEmpty()) {
        cout << q.Qfront() << endl;
    }
    #endif
}