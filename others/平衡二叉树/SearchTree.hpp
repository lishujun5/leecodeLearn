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
        /*�����������������������*/  
        PtNode find(T val , PtNode curNode);
        /*�����ҽڵ�*/
        virtual inline void setRightNode(PtNode pre , PtNode rightNode);
        /*������ڵ�*/
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
                setRightNode(dltNode->pre , exchangeNode);
            }
            else
            {
                setLeftNode(dltNode->pre , exchangeNode);
            }
        }
        else   //ɾ���ڵ��Ǹ��ڵ�
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
    if(MiddleNode == dltNode->leftNode) //ɾ���ڵ����ڵ�����м̽ڵ�
    {
        if(dltNode->pre)  //ɾ���ڵ㲻�Ǹ��ڵ�
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
    else  //�˴�Ϊ��������
    {
        if(MiddleNode->leftNode)
        {
            setRightNode(MiddleNode->pre,MiddleNode->leftNode);
        }
        else
        {
           MiddleNode->pre->rightNode = nullptr;
        }
        if(dltNode->pre) //ɾ���ڵ㲻�Ǹ��ڵ�
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
    Order_type middleOrder = this->MidOrder(); //���ݶ������������������Ϊ��������
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