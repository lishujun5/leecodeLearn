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
}RBEXCHANGETYPE; //������任����
template <class T , class N = RBTreeNode<T>>
class RBTree final: public SearchTree<T,N> 
{
    public:
        typedef N Node;
        typedef Node* PtNode;
        typedef Node& reference;
        typedef RBTree<T,N> self;
        typedef typename SearchTree<T,N>::Order_type Order_type;
    /*���캯��*/
        RBTree():SearchTree<T,N>(){};
        RBTree(const initializer_list<T>& TreeValueList , T disableVal);
    /*��������*/
        ~RBTree(){};
        /*����ڵ�*/
        bool insertNode(T val) override;

        bool insertNode(PtNode tmpNode) override;
        /*ɾ���ڵ�*/
        bool deleteNode(T val);
        /*�ж��Ƿ���ȷ���ɺ����*/
        bool isRbTree();

    private:
        bool insertNode(PtNode tmpNode , PtNode curNode);
        /*����*/
        PtNode leftCircle(PtNode circleNode);
        /*����*/
        PtNode rightCircle(PtNode circleNode);
        /*�ı���ɫ*/
        PtNode changeColor(PtNode exchangeNode);
        /*��ñ任����*/
        PtNode getExchangeType(PtNode exchangeNode , char& exchangeType);
        /*���������жϺ�ɫ�ڵ���Ŀ*/
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
/*ת�ƽڵ�*/
    pre_CurNode->leftNode = changeNode;
    if(changeNode)
    {
        changeNode->pre = pre_CurNode;
    }
/*��ת*/
    hin_CurNode->rightNode = pre_CurNode;
    pre_CurNode->pre = hin_CurNode;

    if(fatherNode)  //��Ҫ��ת��Ϊ���ڵ�
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
/*ת�ƽڵ�*/
    pre_CurNode->rightNode = changeNode;
    if(changeNode)
    {
        changeNode->pre = pre_CurNode;
    }
/*��ת*/
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
    if(exchangeNode->pre->pre)  //үү�ڵ㲻Ϊ���ڵ�
    {
        exchangeNode->pre->color = RED; //үү�ڵ��ɫ
    }
    if(exchangeNode->pre->rightNode)
    {
        exchangeNode->pre->rightNode->color = BLACK;   //���ڵ������ڵ��ɫ
    }
    if(exchangeNode->pre->leftNode)
    {
        exchangeNode->pre->leftNode->color = BLACK;
    }
    return exchangeNode->pre;  //����үү�ڵ�
 }
 template <class T ,class N>
 typename RBTree<T,N>::PtNode RBTree<T,N>::getExchangeType(PtNode exchangeNode , char& exchangeType)
 {
     exchangeType = -1;
     if(exchangeNode->color == BLACK || (exchangeNode->pre && exchangeNode->pre->color == BLACK)) //���任
     {
         return exchangeNode;
     }
     if(!exchangeNode->pre && exchangeNode->color == RED)  //���ڵ�
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
     if(exchangeNode == exchangeNode->pre->rightNode)  //�ҽڵ� �ж�����
     {
         if(!exchangeNode->pre->leftNode || (exchangeNode->pre->leftNode && exchangeNode->pre->leftNode->color== BLACK)) //��Ҫ����
         {
             if(exchangeNode->pre->pre->rightNode == exchangeNode->pre)  //�ж����Ը��ڵ㻹��үү�ڵ��������
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
             return nullptr; //����Ҫ��ת
         }
     }
     else     //��ڵ�  �ж�����
     {
         if(!exchangeNode->pre->rightNode||(exchangeNode->pre->rightNode && exchangeNode->pre->rightNode->color == BLACK))
         {
             if(exchangeNode->pre->pre->leftNode == exchangeNode->pre)  //�ж����Ը��ڵ㻹��үү�ڵ��������
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
    /*1.�жϸ��ڵ��Ƿ�Ϊ��ɫ*/
    if(this->root->color == RED)
    {
        return false;
    }
    /*2.�ж�������ɫ�ڵ㲻������*/

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

    /*3.���κ�һ���ڵ��������Ҷ�ӽڵ㣬����·��������ͬ��Ŀ�ĺ�ɫ�ڵ�*/
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
