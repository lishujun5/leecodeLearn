#include <iostream>
#include "Tree.hpp"
#include "SearchTree.hpp"
using namespace std;
int main()
{
    Tree<int> data({1,2,4,5,6,7,8,9,10},-1);
    cout<<"depth is "<<data.getDepth()<<endl;
    data.display_Tree();
    cout<<"****************"<<endl;
    
    SearchTree<int> dd;
    for (int i = 0; i < 20; i++)
    {
        int tmpInt  = rand()%20;
        cout<<tmpInt<<"   ";
        dd.insertNode(tmpInt);
    }
    cout<<endl;
    cout<<"depth is "<<dd.getDepth()<<endl;
    dd.display_Tree();
    auto q = dd.find(5);
    if(q == nullptr)
    {
        cout<<"没有找到"<<endl;
    }
    else
    {
        cout<<"找到了"<<endl;
    }

    return 0;
}