#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>
#include "Node.hpp"

using namespace std;

template <class T , class N = TreeNode<T>>
class Tree
{
    public:
        typedef N Node;
        typedef N* PtNode;
        typedef N& RefNode;
    
        typedef T Value_type;
        typedef T* Point;
        typedef T& Reference;

        typedef Tree<T,N> Self;
        typedef vector<PtNode> Order_type;  //������������


        Tree():root(nullptr){}
        Tree(const initializer_list<T>& TreeValueList , T disableVal):root(nullptr)
        {
            queue<PtNode>  CrossNode;
            /*�����һ���ڵ�*/
            PtNode tmpNode = new Node();
            tmpNode->val = *(TreeValueList.begin());
            CrossNode.push(tmpNode);
            this->root = tmpNode;
            /*����ʣ�½ڵ�*/
            bool isLeft = true;
            PtNode tmpRootNode = nullptr;
            for(auto iter = TreeValueList.begin()+1 ; iter != TreeValueList.end() ; iter++)
            {

                if(isLeft)
                {
                    tmpRootNode = CrossNode.front();
                    if(*iter != disableVal)
                    {
                        tmpNode = new Node(); //���ɽڵ�
                        tmpNode->val = *iter;
                        CrossNode.push(tmpNode);
                        tmpRootNode->leftNode = tmpNode;
                    }
                }
                else
                {
                    if(*iter != disableVal)
                    {
                        tmpNode = new Node(); //���ɽڵ�
                        tmpNode->val = *iter;
                        CrossNode.push(tmpNode);
                        tmpRootNode->rightNode = tmpNode;
                    }
                    CrossNode.pop();
                }
                isLeft = !isLeft;
            }
        }
        virtual ~Tree()
        {
            Order_type tmp = this->preOrder();
            for(auto i = tmp.begin() ; i != tmp.end() ; i++)
            {
                delete *i;
            }
        }
        /*�������*/
        Order_type preOrder();   
        void preOrder(Order_type& ret , PtNode _root);
         /*�������*/
        Order_type MidOrder();
        void MidOrder(Order_type& ret , PtNode _root);
  
        /*��������*/
        Order_type backOrder();
        void backOrder(Order_type& ret , PtNode _root);

        /*��ӡ��*/
        void display_Tree();

        /*��ȡ�����*/
        int getDepth();
        int getDepth(PtNode curNode);

protected:
    PtNode root;//���ڵ�


};


template <class T , class N>
typename Tree<T,N>::Order_type Tree<T,N>::preOrder()
{
    Order_type ret;
    preOrder(ret , this->root);
    return ret;
}
template <class T , class N>
void Tree<T,N>::preOrder(Order_type& ret , PtNode _root)
{
    if(_root)
        ret.push_back(_root);
    else
        return ;
    if(_root->leftNode)
    {
        preOrder(ret,_root->leftNode);
    }
    if(_root->rightNode)
    {
        preOrder(ret,_root->rightNode);
    }
    return ;
}
template <class T , class N>
typename Tree<T,N>::Order_type Tree<T,N>::MidOrder()
{
    Order_type ret;
    MidOrder(ret , this->root);
    return ret;
}
template <class T , class N>
void Tree<T,N>::MidOrder(Order_type& ret , PtNode _root)
{
    if(_root == nullptr)
        return ;
    if(_root->leftNode)
    {
        MidOrder(ret,_root->leftNode);
    }
    ret.push_back(_root);
    if(_root->rightNode)
    {
        MidOrder(ret,_root->rightNode);
    }
    return ;
}

template <class T , class N>
typename Tree<T,N>::Order_type Tree<T,N>::backOrder()
{   
    Order_type ret;
    backOrder(ret , this->root);
    return ret;
}
template <class T , class N>
void Tree<T,N>::backOrder(Order_type& ret , PtNode _root) 
{
    if(_root == nullptr)
        return ;
    if(_root->leftNode)
    {
        backOrder(ret,_root->leftNode);
    }
    if(_root->rightNode)
    {
        backOrder(ret,_root->rightNode);
    }
    ret.push_back(_root);
    return ;
}


template <class T , class N>
int Tree<T,N>::getDepth( )
{
    return getDepth(this->root);
}

template <class T , class N>
int Tree<T,N>::getDepth(PtNode curNode)
{
    if(!curNode)
    {
        return 0;
    }
    //cout<<"curNode->val = "<<curNode->val<<endl;
    if(!curNode ->leftNode && !curNode->rightNode)
    {
        return 1;
    }
    return max(getDepth(curNode->leftNode) , getDepth(curNode->rightNode))+1;
}
template <class T , class N>
void Tree<T,N>::display_Tree()
{
    Order_type preOrder = this->preOrder();
    int NodeNum = preOrder.size();
    queue<PtNode> data;
    int i = 0;
    int outputTimes = 0;
    PtNode tmpNode = nullptr;
    data.push(this->root);
    while(!data.empty())
    {
        tmpNode = data.front();
        if(!tmpNode)
        {
            cout<<"null";
        }
        else
        {
            i++;
            cout<<tmpNode->val;
            data.push(tmpNode->leftNode);
            data.push(tmpNode->rightNode);
        }
        outputTimes++;
        cout<<string("     ");
        if(outputTimes%5 == 0)
        {
            cout<<endl;
        }
        data.pop();
        if(i == NodeNum)
        {
            break;
        }
    }
    cout<<endl;
}