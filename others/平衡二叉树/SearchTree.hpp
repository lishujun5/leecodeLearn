#pragma once
/*����������*/
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

        virtual bool insertNode(PtNode tmpNode);

        virtual bool deleteNode(T val);
    private:
        /*�����������������������*/  
        bool insertNode(PtNode tmpNode , PtNode curNode); 

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
    /*step 1:�ҵ�ɾ���ڵ�*/
    PtNode dltNode = find(val);
    if(dltNode == nullptr)
    {
        cout<<"�ڵ㲻����,�޷�ɾ��"<<endl;
        return false;
    }
    /*step 2:�����������*/
    /*���һ���ڵ�û���ӽڵ�*/
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
    /*�����: �ڵ������ӽڵ�ֻ����һ��*/
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
    /*����������ҽڵ㶼����*/
    PtNode MiddleNode = dltNode->leftNode;
    while(MiddleNode) //Ѱ���м̽ڵ�
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

    if(dltNode->leftNode !=  MiddleNode) // ����м̽ڵ���ɾ���ڵ���ӽڵ㣬���滻ʱ�����ܽ��ӽڵ���ӽڵ�ָ���Լ�
    {
        MiddleNode->leftNode = dltNode->leftNode;
        dltNode->leftNode->pre = MiddleNode;
    }
    if(dltNode->rightNode !=  MiddleNode)
    {
        MiddleNode->rightNode = dltNode->rightNode;
        dltNode->rightNode->pre = MiddleNode;
    }
   
    if(!dltNode->pre)   //ɾ���ڵ��Ǹ��ڵ�
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