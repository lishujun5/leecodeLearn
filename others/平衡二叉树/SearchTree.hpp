#pragma once
/*搜索二叉树*/
#include "Tree.hpp"
#include "Node.hpp"
template <class T , class N = TreeNode<T>>
class SearchTree : public Tree<T,N>
{
    public:
        typedef N Node;
        typedef Node* PtNode;
        typedef Node& RefNode;
        typedef SearchTree<T,N> self;
        typedef Tree<T,N> FatherTree;
        typedef SearchTree<T,N> STree;


        SearchTree():Tree<T,N>(){};
        SearchTree(const initializer_list<T>& TreeValueList):Tree<T,N>()
        {
            auto firstval = TreeValueList.begin();
            auto endVal = TreeValueList.end();
            PtNode tmpNode = new Node();
            tmpNode->val = *firstval++;
            this->root = tmpNode;
            
            while(firstval != endVal)
            {
                PtNode tmp = new Node();
                tmp->val = *firstval;
                insertNode(tmp);
                firstval++;
            }
        }
        ~SearchTree()
        {
            
        }
    public:
        PtNode find(T val);
        PtNode find(T val , PtNode curNode);
        bool insertNode(T val);
        bool insertNode(PtNode tmpNode);
    private:
        /*将传入的树生成搜索二叉树*/  
        bool insertNode(PtNode tmpNode , PtNode curNode); 
};

template <class T, class N>
bool SearchTree<T,N>::insertNode(T val)
{
    bool ret = false;
    PtNode tmpNode = new Node();
    tmpNode->val = val;
    ret = insertNode(tmpNode);
    if(ret == false)
    {
        delete tmpNode;
    }
    return ret;
}
template <class T, class N>
bool SearchTree<T,N>::insertNode(PtNode tmpNode , PtNode curNode)
{
    bool ret = false;
    if(tmpNode->val < curNode->val)
    {
        if(curNode -> leftNode)
        {
            ret = this->insertNode(tmpNode , curNode->leftNode);
        }
        else
        {
            //cout<<tmpNode->val<<"-------->"<<curNode->val<<endl;
            curNode->leftNode  = tmpNode;
            ret = true;
        }
    }
    else if(tmpNode->val > curNode->val)
    {
        if(curNode -> rightNode)
        {
            ret = this->insertNode(tmpNode , curNode->rightNode);
        }
        else
        {
            //cout<<tmpNode->val<<"-------->"<<curNode->val<<endl;
            curNode->rightNode  = tmpNode;
            ret = true;
        }
    }
    else
    {
        ret = false;

    }
    return ret;
}
template <class T, class N>
typename SearchTree<T,N>::PtNode SearchTree<T,N>::find(T val)
{
    return find(val,this->root);
}
template <class T, class N>
typename SearchTree<T,N>::PtNode SearchTree<T,N>::find(T val , PtNode curNode)
{
    if(curNode->val == val)
        return curNode;
    else if(val < curNode->val)
    {
        if(curNode->leftNode)
        return find(val ,curNode->leftNode);
    }
    else
    {
        if(curNode->rightNode)
        {
            return find(val ,curNode->rightNode);
        }
    }
    return nullptr;
}
template <class T, class N>
bool SearchTree<T,N>::insertNode(PtNode tmpNode)
{
    if(this->root == nullptr)
    {
        this->root = tmpNode;
        return true;
    }
    return this->insertNode(tmpNode,  this->root);
}