#pragma once
#include "SearchTree.hpp"
#include "Node.hpp"
template <class T,  class N = blcTreeNode<T>>
class BlcTree : public SearchTree<T,N>
{
public:
    typedef N Node;
    typedef Node*  PtNode;
    typedef vector<PtNode> Order_type;
    BlcTree():SearchTree<T,N>(){}
    BlcTree(const initializer_list<T>& TreeValueList)
    {
        for(auto i:TreeValueList)
        {
              insertNode(i);
        }
    }
    ~BlcTree(){}
public:
    bool insertNode(T val);
    bool insertNode(PtNode tmpNode);
private:
    bool insertNode(PtNode tmpNode , PtNode curNode);
    /*左旋*/
    bool LeftCircle(PtNode circleNode);
    /*右旋*/
    bool RightCirle(PtNode circleNode);
    /*左右旋*/
    bool LRCircle(PtNode circleNode);
    /*右左旋*/
    bool RLCircle(PtNode circleNode);
    /*插入数据*/
    
    /*获取左边子树深度*/
    int getLeftDepth(PtNode curNode);
    /*获取右边子树深度*/
    int getRightDepth(PtNode curNode);

    /*设置所有节点的父节点*/
    void setFatherNode();
    void setFatherNode(PtNode curNode , PtNode fatherNode);
    /*获取旋转类型*/
    int getCirCleType(PtNode curNode);
};
template <class T ,class N>
bool BlcTree<T,N>::insertNode(T val)
{
    bool ret = false;
    PtNode tmpNode = new Node();
    tmpNode->val = val;
    ret = insertNode(tmpNode);
    if(ret == false)
    {
        delete tmpNode;
    }
    cout<<"hin****************"<<endl;
    this->display_Tree();
    cout<<"****************hin"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    return ret;
}
template <class T ,class N>
bool BlcTree<T,N>::LeftCircle(PtNode circleNode)
{
    PtNode pre_CurNode = circleNode;
    PtNode hin_CurNode = pre_CurNode->rightNode;
    PtNode fatherNode = pre_CurNode->pre;
    PtNode changeNode = hin_CurNode->leftNode;
/*转移节点*/
    pre_CurNode->rightNode = changeNode;
    if(changeNode)
    {
        pre_CurNode->rightDepth = max(changeNode->rightDepth,changeNode->leftDepth) + 1;
        changeNode->pre = pre_CurNode;
    }
    else
    {
        pre_CurNode->rightDepth = 0;
    }
/*旋转*/
    hin_CurNode->leftNode = pre_CurNode;
    pre_CurNode->pre = hin_CurNode;
    pre_CurNode->leftDepth = max(pre_CurNode->rightDepth,pre_CurNode->leftDepth) + 1;

    if(fatherNode)  //需要旋转点为根节点
    {
        if(fatherNode -> rightNode == pre_CurNode)
        {
            fatherNode->rightNode = hin_CurNode;
            fatherNode->rightDepth = max(hin_CurNode->rightDepth,hin_CurNode->leftDepth) + 1;
        }
        else
        {
             fatherNode->leftNode = hin_CurNode;
             fatherNode->leftDepth = max(hin_CurNode->rightDepth,hin_CurNode->leftDepth) + 1;
        }
        hin_CurNode->pre = fatherNode;
    }
    else
    {
        this->root = hin_CurNode;
        hin_CurNode->pre = nullptr;
    }

    return true;
}
template <class T ,class N>
bool BlcTree<T,N>::RightCirle(PtNode circleNode)
{
    PtNode pre_CurNode = circleNode;
    PtNode hin_CurNode = pre_CurNode->leftNode;
    PtNode fatherNode = pre_CurNode->pre;
    PtNode changeNode = hin_CurNode->rightNode;
/*转移节点*/
    pre_CurNode->leftNode = changeNode;
    if(changeNode)
    {
        pre_CurNode->leftDepth = max(changeNode->rightDepth,changeNode->leftDepth) + 1;
        changeNode->pre = pre_CurNode;
    }
    else
    {
        pre_CurNode->leftDepth = 0;
    }
/*旋转*/
    hin_CurNode->rightNode = pre_CurNode;
    pre_CurNode->pre = hin_CurNode;
    hin_CurNode->rightDepth = max(pre_CurNode->rightDepth,pre_CurNode->leftDepth) + 1;

    if(fatherNode)  //需要旋转点为根节点
    {
        if(fatherNode -> rightNode == pre_CurNode)
        {
            fatherNode->rightNode = hin_CurNode;
            fatherNode->rightDepth = max(hin_CurNode->rightDepth,hin_CurNode->leftDepth) + 1;
        }
        else
        {
            fatherNode->leftNode = hin_CurNode;
            fatherNode->leftDepth = max(hin_CurNode->rightDepth,hin_CurNode->leftDepth) + 1;
        }
        hin_CurNode->pre = fatherNode;
    }
    else
    {
        this->root = hin_CurNode;
        hin_CurNode->pre = nullptr;
    }

    return true;
}
template <class T ,class N>
bool BlcTree<T,N>::LRCircle(PtNode circleNode)
{
    LeftCircle(circleNode->leftNode);
    RightCirle(circleNode);
    return true;
}
template <class T ,class N>
bool BlcTree<T,N>::RLCircle(PtNode circleNode)
{
    RightCirle(circleNode->rightNode);
    LeftCircle(circleNode);
    return true;
}
template <class T ,class N>
bool BlcTree<T,N>::insertNode(PtNode tmpNode)
{
    int circleType = 0;
    PtNode needCircle = nullptr;
    if(!this->root)
    {
        this->root = tmpNode;
        return true;
    }
    if(false == insertNode(tmpNode , this->root))
    {
        return false;
    }
    cout<<"pre****************"<<endl;
    this->display_Tree();
    cout<<"****************pre"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    if(!tmpNode->pre||!tmpNode->pre->pre)  //只有两层时不需要判断是否平衡
    {
        cout<<"only two lever , balance tree"<<endl;
        return true;
    }
    cout<<tmpNode->pre->pre->val<<endl;
    cout<<"tmpNode->pre->pre->leftDepth = "<<tmpNode->pre->pre->leftDepth<<endl;
    cout<<"tmpNode->pre->pre->rightDepth = "<<tmpNode->pre->pre->rightDepth<<endl;
    if(abs(tmpNode->pre->pre->leftDepth - tmpNode->pre->pre->rightDepth) < 2)
    {
        cout<<"balance tree"<<endl;
        return true;
    }
    while(needCircle = getCirCleType())
    {
        if(circleType == 0)
        {
            cout<<"LeftCircle"<<endl;
            LeftCircle(needCircle);
        }
        else if(circleType == 1)
        {
            cout<<"LRCircle"<<endl;
            RLCircle(needCircle);
        }
        else if(circleType == 2)
        {
            cout<<"RLCircle"<<endl;
            LRCircle(needCircle);
        }
        else if(circleType == 3)
        {
            cout<<"RightCirle"<<endl;
            RightCirle(needCircle);
        }
        else
        {
            cout<<"unknown circle type"<<endl;
            return false;
        }
    }
    
    return true;
}
template <class T ,class N>
bool BlcTree<T,N>::insertNode(PtNode tmpNode , PtNode curNode)
{
    bool ret = false;
    if(!curNode)
    {
        return false;
    }
    if(curNode->val > tmpNode->val)
    {
        if(!curNode->leftNode)
        {
            curNode->leftNode = tmpNode;
            tmpNode->pre = curNode;
            curNode->leftDepth++;
            ret = true;
        }
        else
        {
            ret = insertNode(tmpNode,curNode->leftNode);
            if(ret == true)
            {
                curNode->leftDepth++;
            }
        }
    }
    else if(curNode->val < tmpNode->val)
    {
        if(!curNode->rightNode)
        {
            curNode->rightNode = tmpNode;
            tmpNode->pre = curNode;
            curNode->rightDepth++;
            ret = true;
        }
        else
        {
            ret = insertNode(tmpNode,curNode->rightNode);
            if(ret == true)
            {
                curNode->rightDepth++;
            }
        }
    }
    else
    {
        return false;
    }
    return ret;
}


template <class T ,class N>
int BlcTree<T,N>::getLeftDepth(PtNode curNode)
{
    return getDepth(curNode->leftDepth);
}
template <class T ,class N>
int BlcTree<T,N>::getRightDepth(PtNode curNode)
{
    return getDepth(curNode->rightNode);
}

template <class T ,class N>
void BlcTree<T,N>::setFatherNode()
{
    Order_type tmpPreOrder = this->preOrder();
    for(auto i : tmpPreOrder)
    {
        if(*i->rightNode)
        {
            *i->rightNode->pre = *i;
        }
        if(*i->leftNode)
        {
            *i->leftNode->pre = *i;
        }
    }
}
/***********************
0x00  ----->    右右
0x01  ----->    右左
0x10  ----->    左右
0x11  ----->    左左
***********************/
template <class T ,class N>
int BlcTree<T,N>::getCirCleType(PtNode curNode)
{
    int circleType = 0;
    PtNode tmpNode = curNode;
    for(int i = 0 ; i < 2 ; i++)
    {
            if(tmpNode->pre->leftNode == tmpNode)
            {
                circleType +=  0x01 << i;
            }
            else if(tmpNode->pre->rightNode == tmpNode)
            {
                circleType = circleType | 0x00;
            }
            else
            {
                circleType = 0xff;
            }
            tmpNode = tmpNode->pre;
    }
    return circleType;
}