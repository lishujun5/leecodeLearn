#pragma once
/*搜索二叉树*/
#include "Tree.hpp"
template <class T>
class SearchTree : public Tree<T>
{
    public:
        typedef typename Tree<T>::PtNode PtNode;
        typedef SearchTree<T> self;
        typedef Tree<T> FatherTree;
        typedef typename Tree<T>::Node Node;
        typedef SearchTree<T> STree;
        SearchTree():Tree<T>(){};
        SearchTree(const initializer_list<T>& TreeValueList):Tree<T>()
        {
            auto firstval = TreeValueList.begin();
            auto endVal = TreeValueList.end();
            PtNode tmpNode = this->NewNode();
            tmpNode->val = *firstval++;
            this->root = tmpNode;
            
            while(firstval != endVal)
            {
                PtNode tmp = this->NewNode();
                tmp->val = *firstval;
                insertNode(tmp);
                firstval++;
            }
        }
        ~SearchTree()
        {
            
        }
    protected:
        /*将传入的树生成搜索二叉树*/
        TreeNode<T>* find(T val);
        TreeNode<T>* find(T val , PtNode curNode);
        bool insertNode(T val);
        bool insertNode(PtNode tmpNode);
        bool insertNode(PtNode tmpNode , PtNode curNode); 
};
template <class T>
bool SearchTree<T>::insertNode(T val)
{
    bool ret = false;
    PtNode tmpNode = this->NewNode();
    tmpNode->val = val;
    ret = insertNode(tmpNode);
    if(ret == false)
    {
        delete tmpNode;
    }
    return ret;
}
template <class T>
bool SearchTree<T>::insertNode(PtNode tmpNode , PtNode curNode)
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
template <class T>
TreeNode<T>* SearchTree<T>::find(T val)
{
    return find(val,this->root);
}
template <class T>
TreeNode<T>* SearchTree<T>::find(T val , PtNode curNode)
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
template <typename T>
bool SearchTree<T>::insertNode(PtNode tmpNode)
{
    if(this->root == nullptr)
    {
        this->root = tmpNode;
        return true;
    }
    return this->insertNode(tmpNode,  this->root);
}