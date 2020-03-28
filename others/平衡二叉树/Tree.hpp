#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>
using namespace std;
template <class T>
struct TreeNode
{
    public:
        TreeNode():leftNode(nullptr),rightNode(nullptr){}
        TreeNode* leftNode;
        TreeNode* rightNode;
        T val;
};
template <class T>
class Tree
{
    public:
        typedef TreeNode<T> Node;
        typedef TreeNode<T>* PtNode;
        typedef TreeNode<T>& RefNode;
        typedef Tree<T> Self;
        typedef T Value_type;
        typedef T* Point;
        typedef T& Reference;
        typedef vector<PtNode> Order_type;  //遍历返回类型
        Tree():root(nullptr){}
        Tree(const initializer_list<T>& TreeValueList , T disableVal):root(nullptr)
        {
            queue<PtNode>  CrossNode;
            /*处理第一个节点*/
            PtNode tmpNode = new Node();
            tmpNode->val = *(TreeValueList.begin());
            CrossNode.push(tmpNode);
            this->root = tmpNode;
            /*处理剩下节点*/
            bool isLeft = true;
            PtNode tmpRootNode = nullptr;
            for(auto iter = TreeValueList.begin()+1 ; iter != TreeValueList.end() ; iter++)
            {

                if(isLeft)
                {
                    tmpRootNode = CrossNode.front();
                    if(*iter != disableVal)
                    {
                        tmpNode = new Node(); //生成节点
                        tmpNode->val = *iter;
                        CrossNode.push(tmpNode);
                        tmpRootNode->leftNode = tmpNode;
                    }
                }
                else
                {
                    if(*iter != disableVal)
                    {
                        tmpNode = new Node(); //生成节点
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
        Order_type preOrder()   //先序遍历
        {
            Order_type ret;
            preOrder(ret , this->root);
            return ret;
        }
        void preOrder(Order_type& ret , PtNode _root)
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
        Order_type MidOrder()
        {
            Order_type ret;
            MidOrder(ret , this->root);
            return ret;
        }
        void MidOrder(Order_type& ret , PtNode _root)   //中序遍历
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
        Order_type backOrder()  //后续遍历
        {   
            Order_type ret;
            backOrder(ret , this->root);
            return ret;
        }
        void backOrder(Order_type& ret , PtNode _root) 
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
        void display_Tree();
        int getDepth();
        int getDepth(PtNode curNode);
protected:
        virtual TreeNode<T>* NewNode();
protected:
    PtNode root;//根节点


};
template <typename T>
int Tree<T>::getDepth( )
{
    return getDepth(this->root);
}
template <typename T>
int Tree<T>::getDepth(PtNode curNode)
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
template <typename T>
void Tree<T>::display_Tree()
{
    int depth = this->getDepth();
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
template <class T>
TreeNode<T>* Tree<T>::NewNode()
{
    return new Node();
}