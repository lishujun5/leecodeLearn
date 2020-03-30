#include "blcTree.hpp"
#include <iostream>
int main()
{
    BlcTree<int> dd;
    #if 0
    dd.insertNode(3);
    dd.insertNode(6);
    dd.insertNode(17);
    dd.insertNode(15);
    dd.insertNode(13);
    dd.insertNode(12);
    #endif
    for (int i = 0; i < 100; i++)
    {
        dd.insertNode(rand()%100);
    }
    dd.display_Tree();
    return 0;
}