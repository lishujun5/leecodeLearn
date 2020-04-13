#pragma once
/*搜索二叉树*/
#include "Tree.hpp"
#include "Node.hpp"
template <class T , class N = SearchNode<T>>
class SearchTree : public Tree<T,N>
{
    public:
        typedef N Node;
        typedef Node* PtNode;
        typedef Node& RefNode;
        typedef SearchTree<T,N> self;
        typedef Tree<T,N> FatherTree;
        typedef SearchTree<T,N> STree;
        typedef typename Tree<T,N>::Order_type Order_type;

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
        virtual ~SearchTree()
        {
            
        }
    public:
        PtNode find(T val);
        
        virtual bool insertNode(T val);
        
        virtual bool deleteNode(T val);

protected:

        virtual bool insertNode(PtNode tmpNode);

        bool insertNode(PtNode tmpNode , PtNode curNode); 
        /*将传入的树生成搜索二叉树*/  
        PtNode find(T val , PtNode curNode);
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
            tmpNode->pre = curNode;
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
            tmpNode->pre  = curNode;
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
template <class T, class N>
bool SearchTree<T,N>::deleteNode(T val)
{
    PtNode fatherNode = nullptr;
    PtNode exchangeNode = nullptr;
    /*step 1:找到删除节点*/
    PtNode dltNode = find(val);
    if(dltNode == nullptr)
    {
        cout<<"节点不存在,无法删除"<<endl;
        return false;
    }
    /*step 2:根据情况处理*/
    /*情况一：节点没有子节点*/
    if(!dltNode->leftNode && !dltNode -> rightNode)
    {
        if(dltNode->pre)
        {
            if(dltNode->pre->leftNode == dltNode)
            {
                dltNode->pre->leftNode = nullptr;
            }
            else
            {
                dltNode->pre->rightNode = nullptr;
            } 
        }
        else
        {
            this->root = nullptr;
        }
        
        delete dltNode;
        return true;
    }
    /*情况二: 节点左右子节点只存在一个*/
    if(dltNode->leftNode && !dltNode->rightNode)
    {
        exchangeNode = dltNode->leftNode;
    }
    else if(!dltNode->leftNode && dltNode->rightNode)
    {
        exchangeNode = dltNode->rightNode;
    }
    if(exchangeNode)
    {
        if(dltNode->pre)
        {
            if(dltNode->pre->rightNode == dltNode)
            {
                dltNode->pre->rightNode = exchangeNode;
            }
            else
            {
                dltNode->pre->leftNode = exchangeNode;
            }
            exchangeNode->pre = dltNode->pre;
        }
        else
        {
            this->root = exchangeNode;
            exchangeNode -> pre = nullptr;
        }
        delete dltNode;
        return true;
    }
    /*情况三：左右节点都存在*/
    PtNode MiddleNode = dltNode->leftNode;
    while(MiddleNode) //寻找中继节点
    {
        if(!MiddleNode->rightNode)
        {
            break;
        }
        MiddleNode = MiddleNode->rightNode;
    }
    if(MiddleNode -> leftNode)
    {
        MiddleNode->pre->rightNode = MiddleNode;
    }

    if(dltNode->leftNode !=  MiddleNode) // 如果中继节点是删除节点的子节点，则替换时，不能将子节点的子节点指向自己
    {
        MiddleNode->leftNode = dltNode->leftNode;
        dltNode->leftNode->pre = MiddleNode;
    }
    if(dltNode->rightNode !=  MiddleNode)
    {
        MiddleNode->rightNode = dltNode->rightNode;
        dltNode->rightNode->pre = MiddleNode;
    }
   
    if(!dltNode->pre)   //删除节点是根节点
    {
        this->root = MiddleNode;
        delete dltNode;
        return true;
    }
    if(dltNode->pre->rightNode == dltNode)
    {
        dltNode->pre->rightNode = MiddleNode;
    }
    else
    {
        dltNode->pre->leftNode = MiddleNode;
    }
    delete dltNode;
    return true;
}