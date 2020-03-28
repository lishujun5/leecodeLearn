#include "blcTree.hpp"
#include <iostream>
int main()
{
    BlcTree<int> dd;
    for (int i = 0; i < 20; i++)
    {
        dd.insertNode(rand()%20);
    }
    return 0;
}