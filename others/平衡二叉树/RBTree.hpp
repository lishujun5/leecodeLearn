#include <iostream>
#include "SearchTree.hpp"
#include "Node.hpp"
#include "stack"
using namespace std;
typedef enum{
    RIGHT_CIRCLE = 0,
    LEFT_CIRCLE,
    EXCHANGECOLOR,
    ROOTNODE,
}RBEXCHANGETYPE; //红黑树变换类型
template <class T , class N = RBTreeNode<T>>
class RBTree final: public SearchTree<T,N> 
{
    public:
        typedef N Node;
        typedef Node* PtNode;
        typedef Node& reference;
        typedef RBTree<T,N> self;
        typedef typename SearchTree<T,N>::Order_type Order_type;
    /*构造函数*/
        RBTree():SearchTree<T,N>(){};
        RBTree(const initializer_list<T>& TreeValueList , T disableVal);
    /*析构函数*/
        ~RBTree(){};
        /*插入节点*/
        bool insertNode(T val) override;

        bool insertNode(PtNode tmpNode) override;
        /*删除节点*/
        bool deleteNode(T val);
        /*判断是否正确生成红黑树*/
        bool isRbTree();

    private:
        bool insertNode(PtNode tmpNode , PtNode curNode);
        /*左旋*/
        PtNode leftCircle(PtNode circleNode);
        /*右旋*/
        PtNode rightCircle(PtNode circleNode);
        /*改变颜色*/
        PtNode changeColor(PtNode exchangeNode);
        /*获得变换类型*/
        PtNode getExchangeType(PtNode exchangeNode , char& exchangeType);
        /*遍历子树判断黑色节点数目*/
        bool getBlackNum(PtNode curNode , int& blackNodeNum);

};
template <class T ,class N>
RBTree<T,N>::RBTree(const initializer_list<T>& TreeValueList , T disableVal)
{
    for(auto i = TreeValueList.begin();i != TreeValueList.end();++i)
    {
        if(disableVal != *i)
            insertNode(*i);   
    }

}
template <class T ,class N>
bool RBTree<T,N>::insertNode(T val)
{
    bool ret = true;
    PtNode tmpNode = new Node(val);
    if(!insertNode(tmpNode))
    {
        delete tmpNode;
        ret = false;
    }
    return ret;
}
template <class T ,class N>
 bool RBTree<T,N>::insertNode(PtNode tmpNode)
 {
     if(!this->root)
     {
         this->root = tmpNode;
         this->root->color = BLACK;
         return true;
     }
     return insertNode(tmpNode , this->root);
 }
template <class T ,class N>
bool RBTree<T,N>::insertNode(PtNode tmpNode , PtNode curNode)
{
    PtNode judgeNode = tmpNode;
    if(!SearchTree<T,N>::insertNode(tmpNode,curNode))
    {
        return false;
    }
    char exchangeType = -1;
    PtNode exchangeNode = getExchangeType(judgeNode , exchangeType);
    while(exchangeType != -1 && judgeNode != nullptr)    
    {
        cout<<"exchangeNode->val = "<<exchangeNode->val<<endl;
        if(exchangeType == LEFT_CIRCLE)
        {
            cout<<"leftCircle"<<endl;
            judgeNode = leftCircle(exchangeNode);
        }
        else if(exchangeType == RIGHT_CIRCLE)
        {
            cout<<"rightCircle"<<endl;
            judgeNode = rightCircle(exchangeNode);
        }
        else if(exchangeType == ROOTNODE)
        {
            cout<<"ROOTNODE"<<endl;
            exchangeNode->color = BLACK;
        }
        else if(exchangeType == EXCHANGECOLOR)
        {
            cout<<"changeColor"<<endl;
            judgeNode = changeColor(exchangeNode);
        }
        exchangeNode = getExchangeType(judgeNode , exchangeType);
    }
    return true;
}
template <class T ,class N>
typename RBTree<T,N>::PtNode RBTree<T,N>::rightCircle(PtNode circleNode)
{
    PtNode pre_CurNode = circleNode;
    PtNode hin_CurNode = pre_CurNode->leftNode;
    PtNode fatherNode = pre_CurNode->pre;
    PtNode changeNode = hin_CurNode->rightNode;
    int colorTmp = hin_CurNode->color;
    hin_CurNode->color = pre_CurNode->color;
    pre_CurNode->color = colorTmp;
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
    return pre_CurNode;
}
template <class T ,class N>
typename RBTree<T,N>::PtNode RBTree<T,N>::leftCircle(PtNode circleNode)
{
    PtNode pre_CurNode = circleNode;
    PtNode hin_CurNode = pre_CurNode->rightNode;
    PtNode fatherNode = pre_CurNode->pre;
    PtNode changeNode = hin_CurNode->leftNode;
    int colorTmp = hin_CurNode->color;
    hin_CurNode->color = pre_CurNode->color;
    pre_CurNode->color = colorTmp;
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
    return pre_CurNode;
}
template <class T ,class N>
typename RBTree<T,N>::PtNode RBTree<T,N>::changeColor(PtNode exchangeNode)
 {
    if(exchangeNode->pre->pre)  //爷爷节点不为根节点
    {
        exchangeNode->pre->color = RED; //爷爷节点红色
    }
    if(exchangeNode->pre->rightNode)
    {
        exchangeNode->pre->rightNode->color = BLACK;   //父节点和叔叔节点黑色
    }
    if(exchangeNode->pre->leftNode)
    {
        exchangeNode->pre->leftNode->color = BLACK;
    }
    return exchangeNode->pre;  //返回爷爷节点
 }
 template <class T ,class N>
 typename RBTree<T,N>::PtNode RBTree<T,N>::getExchangeType(PtNode exchangeNode , char& exchangeType)
 {
     exchangeType = -1;
     if(exchangeNode->color == BLACK || (exchangeNode->pre && exchangeNode->pre->color == BLACK)) //不变换
     {
         return exchangeNode;
     }
     if(!exchangeNode->pre && exchangeNode->color == RED)  //根节点
     {
         exchangeType = ROOTNODE;
         return exchangeNode;
     }
     if(exchangeNode->pre->pre \
     && exchangeNode->pre->pre->rightNode\
     && exchangeNode->pre->pre->leftNode\
     &&exchangeNode->pre->pre->rightNode->color == exchangeNode->pre->pre->leftNode->color)
     {
         exchangeType = EXCHANGECOLOR;
         return exchangeNode->pre;
     }
     if(exchangeNode == exchangeNode->pre->rightNode)  //右节点 判断左旋
     {
         if(!exchangeNode->pre->leftNode || (exchangeNode->pre->leftNode && exchangeNode->pre->leftNode->color== BLACK)) //需要左旋
         {
             if(exchangeNode->pre->pre->rightNode == exchangeNode->pre)  //判断是以父节点还是爷爷节点进行左旋
             {
                exchangeType = LEFT_CIRCLE;
                return exchangeNode->pre->pre;
             }
             else
             {
                exchangeType = LEFT_CIRCLE;
                return exchangeNode->pre;
             }

         }
         else
         {
             return nullptr; //不需要旋转
         }
     }
     else     //左节点  判断右旋
     {
         if(!exchangeNode->pre->rightNode||(exchangeNode->pre->rightNode && exchangeNode->pre->rightNode->color == BLACK))
         {
             if(exchangeNode->pre->pre->leftNode == exchangeNode->pre)  //判断是以父节点还是爷爷节点进行左旋
             {
                exchangeType = RIGHT_CIRCLE;
                return exchangeNode->pre->pre;
             }
             else
             {
                exchangeType = RIGHT_CIRCLE;
                return exchangeNode->pre;
             }

         }
         else
         {
             return nullptr;
         }
     }
 }
 template <class T ,class N>
 bool RBTree<T,N>::isRbTree()
{
     stack<PtNode> data;
    /*1.判断根节点是否为黑色*/
    if(this->root->color == RED)
    {
        return false;
    }
    /*2.判断两个红色节点不能连续*/

     Order_type pre = this->preOrder();
     for(auto i:pre)
     {
        if(i->color == BLACK)
            continue;
        if(i->leftNode)
        {
            if(i->leftNode->color== RED)
            {
                return false;
            }
        }
        if(i->rightNode)
        {
            if(i->rightNode->color == RED)
            {
                return false;
            }
        }
     }

    /*3.从任何一个节点出发，到叶子节点，这条路径都有相同数目的黑色节点*/
    int blackNodeNum = 0;
    return getBlackNum(this->root , blackNodeNum);
}
template <class T ,class N>
bool RBTree<T,N>::getBlackNum(PtNode curNode , int& blackNodeNum)
{

    int rightNum = 0;
    int leftNum = 0;
    if(!curNode)
    {
        return true;
    }
    if(!getBlackNum(curNode->rightNode,rightNum))
    {
        return false;
    }
    if(!getBlackNum(curNode->leftNode,leftNum))
    {
        return false;
    }
    if(curNode->color == BLACK)
    {
        blackNodeNum = rightNum+1;
    }
    else
    {
        blackNodeNum = rightNum;
    }
    cout<<curNode->val<<" have leftNum = "<<leftNum<<"*****"<<"rightNum = "<<rightNum<<endl;
    return rightNum == leftNum;
}
template <class T ,class N>
bool RBTree<T,N>::deleteNode(T val)
{

}
