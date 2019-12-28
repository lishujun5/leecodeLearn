#include <iostream>
#include <vector>
using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        data = new vector<int>;
    }
    
    void push(int x) {
        data->push_back();
    }
    
    void pop() {
        if(data->empty())
        {
            data->pop_back()
        }
    }
    
    int top() {
        if(data->empty())
            return data->back();
    }
    
    int getMin() {
        int min = data->front();
        for(vector<int>::const_iterator cur = data->cbegin() ; cur <= data->cend();cur++)
        {
            if(min < )
        }
    }
    private:
    vector<int> *data;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */