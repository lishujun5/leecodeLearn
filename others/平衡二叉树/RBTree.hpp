#include <iostream>
#include "SearchTree.hpp"
#include "Node.hpp"
using namespace std;
typedef enum{
    RIGHT_CIRCLE = 0,
    LEFT_CIRCLE,
    EXCHANGECOLOR
}RBEXCHANGETYPE; //红黑树变换类型
template <class T , class N = RBTreeNode<T>>
class RBTree final: public SearchTree<T,N> 
{
    public:
        typedef N Node;
        typedef Node* PtNode;
        typedef Node& reference;
        typedef RBTree<T,N> self;
    /*构造函数*/
        RBTree():root(nullptr){};
        RBTree(const initializer_list<T>& TreeValueList , T disableVal);
    /*析构函数*/
        ~RBTree(){};
        /*插入节点*/
        bool insertNode(T val) override;

        bool insertNode(PtNode insertNode) override;
        /*删除节点*/
        bool deleteNode(T val);

    private:
        bool insertNode(PtNode insertNode , PtNode curNode);
        /*左旋*/
        void leftCircle(PtNode cirCleNode);
        /*右旋*/
        void rightCircle(PtNode cirCleNode);
        /*改变颜色*/
        void changeColor(PtNode exchangeNode);
        /*获得变换类型*/
        PtNode getExchangeType(PtNode exchangeNode , char& exchangeType);


};
template <class T ,class N>
RBTree<T,N>::RBTree(const initializer_list<T>& TreeValueList , T disableVal)
{
    for(auto i = TreeValueList.begin(),i != TreeValueList.end();++i)
    {
        if(disableVal != *i)
            insertNode(*i);   
    }

}
template <class T ,class N>
bool RBTree<T,N>::insertNode(T val)
{
    bool ret = true;
    PtNode tmpNode = new Node();
    if(!insertNode(tmpNode))
    {
        delete tmpNode;
        ret = false;
    }
    return ret;
}
template <class T ,class N>
 bool RBTree<T,N>::insertNode(PtNode insertNode)
 {
     if(!this->root)
     {
         this->root = insertNode;
         this->root->color = BLACK;
         return true;
     }
     return insertNode(insertNode , root);
 }
template <class T ,class N>
bool RBTree<T,N>::insertNode(PtNode insertNode , PtNode curNode)
{
    if(!SearchTree::insertNode(insertNode,curNode))
    {
        return false;
    }
    char exchangeType = 0xff;
    PtNode exchangeNode = getExchangeType(insertNode , exchangeType); 
    if(exchangeNode) 
    {
        if(exchangeType == LEFT_CIRCLE)
        {
            leftCircle(exchangeNode);
        }
        else if(exchangeType == RIGHT_CIRCLE)
        {
            rightCircle(exchangeNode);
        }
        else
        {
            changeColor(exchangeNode);
        }
    }
    return true;
}
template <class T ,class N>
void RBTree<T,N>::rightCircle(PtNode cirCleNode)
{
    PtNode pre_CurNode = circleNode;
    PtNode hin_CurNode = pre_CurNode->leftNode;
    PtNode fatherNode = pre_CurNode->pre;
    PtNode changeNode = hin_CurNode->rightNode;
/*转移节点*/
    pre_CurNode->leftNode = changeNode;
    if(changeNode)
    {
        changeNode->pre = pre_CurNode;
    }
/*旋转*/
    hin_CurNode->rightNode = pre_CurNode;
    pre_CurNode->pre = hin_CurNode;

    if(fatherNode)  //需要旋转点为根节点
    {
        if(fatherNode -> rightNode == pre_CurNode)
        {
            fatherNode->rightNode = hin_CurNode;
        }
        else
        {
            fatherNode->leftNode = hin_CurNode;
        }
        hin_CurNode->pre = fatherNode;
    }
    else
    {
        this->root = hin_CurNode;
        hin_CurNode->pre = nullptr;
    }
}
template <class T ,class N>
void RBTree<T,N>::leftCircle(PtNode cirCleNode)
{
    PtNode pre_CurNode = circleNode;
    PtNode hin_CurNode = pre_CurNode->rightNode;
    PtNode fatherNode = pre_CurNode->pre;
    PtNode changeNode = hin_CurNode->leftNode;
/*转移节点*/
    pre_CurNode->rightNode = changeNode;
    if(changeNode)
    {
        changeNode->pre = pre_CurNode;
    }
/*旋转*/
    hin_CurNode->leftNode = pre_CurNode;
    pre_CurNode->pre = hin_CurNode;

    if(fatherNode)
    {
        if(fatherNode -> rightNode == pre_CurNode)
        {
            fatherNode->rightNode = hin_CurNode;
        }
        else
        {
             fatherNode->leftNode = hin_CurNode;
        }
        
        hin_CurNode->pre = fatherNode;
    }
    else
    {
        this->root = hin_CurNode;
        hin_CurNode->pre = nullptr;
    }

}
template <class T ,class N>
 void RBTree<T,N>::changeColor(PtNode exchangeNode)
 {

 }
 template <class T ,class N>
 typename RBTree<T,N>::PtNode RBTree<T,N>::getExchangeType(PtNode exchangeNode , char& exchangeType)
 {

 }