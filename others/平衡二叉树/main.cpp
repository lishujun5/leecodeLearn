#include <iostream>
#include "Tree.hpp"
#include "RBTree.hpp"
#include "SearchTree.hpp"
using namespace std;
int main()
{
    Tree<int> data({1,2,4,5,6,7,8,9,10},-1);
    cout<<"depth is "<<data.getDepth()<<endl;
    data.display_Tree();


    cout<<"********SearchTree********"<<endl;
    SearchTree<int> dd;
    for (int i = 0; i < 100; i++)
    {
        int tmpInt  = rand()%100;
        cout<<tmpInt<<"   ";
        dd.insertNode(tmpInt);
    }
    cout<<"*************"<<endl;
    dd.display_Tree();
    cout<<"now is search tree "<<dd.isSearchTree()<<endl;
    cout<<"pre depth is "<<dd.getDepth()<<endl;
    for(int i = 0; i < 50; i++)
    {
        int tmpInt  = rand()%100;
        dd.deleteNode(tmpInt);
    }
    dd.display_Tree();
    cout<<"now is search tree "<<dd.isSearchTree()<<endl;
    cout<<"hin depth is "<<dd.getDepth()<<endl;

    cout<<"****************RBtree*****************"<<endl;
    RBTree<int> aa;
    int elecount = 0;
    for (int i = 0; i < 100; i++)
    {
        int tmpInt  = rand()%100;
        cout<<tmpInt<<"   ";
        if(aa.insertNode(tmpInt))
        {
            ++elecount;
        }
    }
    // aa.insertNode(19);
    // aa.insertNode(12);
    // aa.insertNode(30);
    // aa.insertNode(5);
    // aa.insertNode(13);
    // aa.insertNode(35);
    // aa.insertNode(1);
    // aa.insertNode(7);
    // aa.insertNode(6);
    aa.display_Tree();
    cout<<"before delete "<<aa.isRbTree()<<endl;
    for (int i = 0; i < 100; i++)
    {
        int tmpInt  = rand()%100;
        if(aa.deleteNode(tmpInt))
        {
            --elecount;
        }
    }
    cout<<"after delete "<<aa.isRbTree()<<endl;
    if(aa.preOrder().size() == elecount)
    {
        cout<<"equal elecount = "<<elecount <<endl;
    }
    else
    {
        cout<<"wrong , RBtree = "<<aa.preOrder().size()<<"  elecount = "<<elecount<<endl;
    }
    
    return 0;
}