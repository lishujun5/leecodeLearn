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
    /*在插入元素后判断是否有不平衡节点*/
    PtNode isBalance(PtNode insertNode , int* circleType);
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
    hin_CurNode->leftDepth = pre_CurNode->leftDepth + 1;

    if(fatherNode)
    {
        if(fatherNode -> rightNode == pre_CurNode)
        {
            fatherNode->rightNode = hin_CurNode;
            fatherNode->rightDepth = max(hin_CurNode->rightDepth , hin_CurNode->leftDepth)+1;
        }
        else
        {
             fatherNode->leftNode = hin_CurNode;
             fatherNode->leftDepth = max(hin_CurNode->rightDepth , hin_CurNode->leftDepth)+1;
        }
        
        hin_CurNode->pre = fatherNode;
    }
    else
    {
        this->root = hin_CurNode;
        hin_CurNode->pre = nullptr;
    }
    while(fatherNode && fatherNode->pre)  //在插入节点的子树上的父节点，都需要更新一下左右树高度，否则在大量插入的情况下会产生问题
    {
        if(fatherNode ->pre-> rightNode == fatherNode)
        {
            int preDepth = fatherNode->pre->rightDepth;
            fatherNode->pre->rightDepth = max(fatherNode->rightDepth , fatherNode->leftDepth)+1;
            if(preDepth == fatherNode->pre->rightDepth) //当某一处父节点保持不变时，则不需要向上遍历他的父节点，节省时间
            {
                break;
            }
        }
        else
        {
            int preDepth = fatherNode->pre->leftDepth;
            fatherNode->pre->leftDepth = max(fatherNode->rightDepth , fatherNode->leftDepth)+1;
            if(preDepth == fatherNode->pre->leftDepth) //当某一处父节点保持不变时，则不需要向上遍历他的父节点，节省时间
            {
                break;
            }
        }
        fatherNode = fatherNode->pre;
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
    hin_CurNode->rightDepth = pre_CurNode->rightDepth + 1;

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
    while(fatherNode && fatherNode->pre)
    {
        if(fatherNode ->pre-> rightNode == fatherNode)
        {
            fatherNode->pre->rightDepth = max(fatherNode->rightDepth , fatherNode->leftDepth)+1;
        }
        else
        {
            fatherNode->pre->leftDepth = max(fatherNode->rightDepth , fatherNode->leftDepth)+1;
        }
        fatherNode = fatherNode->pre;
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
    cout<<"afterInsert***********"<<endl;
    Order_type tmp = this->preOrder();
    for(auto i:tmp)
    {
        cout<<"i->val = "<<i->val<<"----->"<<"leftDepth = "<<i->leftDepth<<"-------->"<<"rightDepth = "<<i->rightDepth<<endl;
    }
    cout<<"***********afterInsert"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    if(nullptr != (needCircle = isBalance(tmpNode , &circleType)))
    {
        cout<<"needCircle->val = "<<needCircle->val<<endl;
        cout<<"circleType = "<<circleType<<endl;
        circleType = circleType & 0x3;
        if(circleType == 0)
        {
            cout<<"LeftCircle"<<endl;
            LeftCircle(needCircle);
        }
        else if(circleType == 2)
        {
            cout<<"RLCircle"<<endl;
            RLCircle(needCircle);
        }
        else if(circleType == 1)
        {
            cout<<"LRCircle"<<endl;
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
    cout<<"afterCircle***********"<<endl;
    Order_type tmph = this->preOrder();
    for(auto i:tmph)
    {
        cout<<"i->val = "<<i->val<<"----->"<<"leftDepth = "<<i->leftDepth<<"-------->"<<"rightDepth = "<<i->rightDepth<<endl;
    }
    cout<<"***********afterCircle"<<endl;
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
                curNode->leftDepth = max(curNode->leftNode->leftDepth,curNode->leftNode->rightDepth)+1;
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
                curNode->rightDepth = max(curNode->rightNode->rightDepth , curNode->rightNode->leftDepth)+1;
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
circleType:
00  ----->    右右
01  ----->    左右
10  ----->    右左
11  ----->    左左
return:nullptr --- > 无不平衡节点
***********************/
template <class T ,class N>
typename BlcTree<T,N>::PtNode BlcTree<T,N>::isBalance(PtNode insertNode , int* circleType)
{
    if(!insertNode->pre || !insertNode->pre->pre) //低于三层的树，无需判断是否平衡
    {
        return nullptr;
    }
    bool isEnough = false;//记录是否已经记录两个树形
    char recodeTime = 0;
    PtNode tmpNode = insertNode;
    *circleType = 0;
    while(tmpNode)
    {

        if(abs(tmpNode->rightDepth - tmpNode->leftDepth) >= 2)
        {
            return tmpNode;
        }
        else
        {
            *circleType = *circleType<<1;
            if(tmpNode->pre && tmpNode->pre->leftNode == tmpNode)
            {
                *circleType = *circleType | 0x1;
            }
            tmpNode = tmpNode->pre;
        }
    }
    return nullptr;
}
