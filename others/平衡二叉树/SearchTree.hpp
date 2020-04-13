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

        bool isSearchTree();

protected:

        virtual bool insertNode(PtNode tmpNode);

        bool insertNode(PtNode tmpNode , PtNode curNode); 
        /*将传入的树生成搜索二叉树*/  
        PtNode find(T val , PtNode curNode);
        /*设置右节点*/
        virtual inline void setRightNode(PtNode pre , PtNode rightNode);
        /*设置左节点*/
        virtual inline void setLeftNode(PtNode pre , PtNode leftNode);
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
            setLeftNode(curNode , tmpNode);
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
            setRightNode(curNode,tmpNode);
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
                setRightNode(dltNode->pre , exchangeNode);
            }
            else
            {
                setLeftNode(dltNode->pre , exchangeNode);
            }
        }
        else   //删除节点是根节点
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
    if(MiddleNode == dltNode->leftNode) //删除节点的左节点就是中继节点
    {
        if(dltNode->pre)  //删除节点不是根节点
        {
            if(dltNode->pre->rightNode == dltNode)
            {
                setRightNode(dltNode->pre , MiddleNode);
            }
            else
            {
                setLeftNode(dltNode->pre , MiddleNode);
            }
            setRightNode(MiddleNode,dltNode->rightNode);
        }
        else
        {
            this->root = MiddleNode;
            setRightNode(MiddleNode,dltNode->rightNode);
            MiddleNode->pre = nullptr;
        }
        delete dltNode;
        return true;
    }
    else  //此处为大概率情况
    {
        if(MiddleNode->leftNode)
        {
            setRightNode(MiddleNode->pre,MiddleNode->leftNode);
        }
        else
        {
           MiddleNode->pre->rightNode = nullptr;
        }
        if(dltNode->pre) //删除节点不是根节点
        {
            if(dltNode->pre->rightNode == dltNode)
            {
                setRightNode(dltNode->pre,MiddleNode);
            }
            else
            {
                setLeftNode(dltNode->pre,MiddleNode);
            }
            setLeftNode(MiddleNode,dltNode->leftNode);
            setRightNode(MiddleNode,dltNode->rightNode);
        }
        else
        {
            this->root = MiddleNode;
            MiddleNode->pre = nullptr;
            setLeftNode(MiddleNode,dltNode->leftNode);
            setRightNode(MiddleNode,dltNode->rightNode);
        }
        delete dltNode;
        return true;
    }
    
}
template <class T , class N>
inline void SearchTree<T,N>::setRightNode(PtNode pre , PtNode rightNode)
{
    pre->rightNode = rightNode;
    rightNode->pre = pre;
}
template <class T , class N>
inline void SearchTree<T,N>::setLeftNode(PtNode pre , PtNode leftNode)
{
    pre->leftNode = leftNode;
    leftNode->pre = pre;
}
template <class T , class N>
bool SearchTree<T,N>::isSearchTree()
{
    Order_type middleOrder = this->MidOrder(); //根据二叉搜索树，中序遍历为有序数列
    auto i=middleOrder.begin();
    auto next = i;
    ++next;
    while(++next != middleOrder.end())
    {
        if((*i)->val > (*next)->val)
            return false;
        ++i;
    }
    return true;
}