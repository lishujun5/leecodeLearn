#include <iostream>
#include "Tree.hpp"
using namespace std;
int main()
{
    Tree<int> data{1,2,4,5,6,7,8,9,10};
    Tree<int>::Order_type b= data.preOrder();
    for(auto i:b)
    {
        cout<<(*i).val<<endl;
    }
    return 0;
}