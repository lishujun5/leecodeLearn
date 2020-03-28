#pragma once
#include "SearchTree.hpp"
template <class T>
struct blcTreeNode:public TreeNode<T>
{
    blcTreeNode():TreeNode<T>(),rightDepth(0),leftDepth(0),pre(nullptr){}
    int rightDepth;
    int leftDepth;
    blcTreeNode<T>* pre;  //父节点
};
template <class T>
class BlcTree : public SearchTree<T>
{
public:
    typedef SearchTree<T> FatherTree;
    typedef blcTreeNode<T> Node;
    typedef blcTreeNode<T>*  PtNode;
    typedef vector<PtNode> Order_type;
    BlcTree():SearchTree<T>(){}
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
protected:
    bool insertNode(PtNode tmpNode);
    bool insertNode(PtNode tmpNode , PtNode curNode);
private:
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
protected:
    /*生成新的节点*/
    virtual TreeNode<T>* NewNode() override;
};
template <class T>
bool BlcTree<T>::insertNode(T val)
{
    bool ret = false;
    PtNode tmpNode = (PtNode)this->NewNode();
    if(tmpNode == nullptr)
    {
        cout<<"get new node failed!!!"<<endl;
        return false;
    }
    tmpNode->val = val;
    ret = insertNode(tmpNode);
    if(ret == false)
    {
        delete tmpNode;
    }
    return ret;
}
template <typename T>
bool BlcTree<T>::LeftCircle(PtNode circleNode)
{
    PtNode hin_CurNode = circleNode;    //当前节点==>替换之后节点
    PtNode pre_CurNode = hin_CurNode->pre;  //被替换节点
    PtNode fatherNode = pre_CurNode->pre; //父节点
    PtNode changeNode = hin_CurNode->leftNode; //需要转移节点


    pre_CurNode->rightNode = changeNode;
    changeNode->pre = pre_CurNode;


    hin_CurNode ->leftNode = pre_CurNode;
    pre_CurNode->pre = hin_CurNode;


    if(fatherNode)
    {
        if(fatherNode->leftNode == pre_CurNode)
        {
            fatherNode->leftNode = hin_CurNode;
        }
        else
        {
            fatherNode->rightNode = hin_CurNode;
        }
        hin_CurNode->pre = fatherNode;
    }
    else
    {
        this->root = hin_CurNode;
        hin_CurNode->pre = (PtNode)this->root;
    }
    return true;
}
template <typename T>
bool BlcTree<T>::RightCirle(PtNode circleNode)
{
    PtNode hin_CurNode = circleNode;    //当前节点==>替换之后节点
    PtNode pre_CurNode = hin_CurNode->pre;  //被替换节点
    PtNode fatherNode = pre_CurNode->pre; //父节点
    PtNode changeNode = hin_CurNode->rightNode; //需要转移节点
    

    pre_CurNode->leftNode = changeNode;
    changeNode->pre = pre_CurNode;


    hin_CurNode ->rightNode = pre_CurNode;
    pre_CurNode->pre = hin_CurNode;
    if(fatherNode)
    {
        if(fatherNode->leftNode == pre_CurNode)
        {
            fatherNode->leftNode = hin_CurNode;
        }
        else
        {
            fatherNode->rightNode = hin_CurNode;
        }
        hin_CurNode->pre = fatherNode;
    }
    else
    {
        this->root = hin_CurNode;
        hin_CurNode->pre = (PtNode)this->root;
    }
    return true;
}
template <typename T>
bool BlcTree<T>::LRCircle(PtNode circleNode)
{
    RightCirle(circleNode->leftNode);
    LeftCircle(circleNode);
    return true;
}
template <typename T>
bool BlcTree<T>::RLCircle(PtNode circleNode)
{
    RightCirle(circleNode->rightNode);
    LeftCircle(circleNode);
    return true;
}
template <typename T>
bool BlcTree<T>::insertNode(PtNode tmpNode)
{
    int circleType = 0;
    if(!this->root)
    {
        this->root = tmpNode;
        return true;
    }
    if(false == insertNode(tmpNode , (PtNode)this->root))
    {
        return false;
    }
    if(!tmpNode->pre->pre)
    {
        cout<<"balance tree"<<endl;
        return true;
    }
    if(abs(tmpNode->pre->pre->leftDepth - tmpNode->pre->pre->rightDepth) < 2)
    {
        cout<<"balance tree"<<endl;
        return true;
    }
    circleType = getCirCleType(tmpNode);
    if(circleType == 0x00)
    {
        LeftCircle(tmpNode->pre->pre);
    }
    else if(circleType == 0x01)
    {
        LRCircle(tmpNode->pre->pre);
    }
    else if(circleType == 0x10)
    {
        RLCircle(tmpNode->pre->pre);
    }
    else if(circleType == 0x11)
    {
        RightCirle(tmpNode->pre->pre);
    }
    else
    {
        cout<<"unknown circle type"<<endl;
        return false;
    }
    return true;
}
template <typename T>
bool BlcTree<T>::insertNode(PtNode tmpNode , PtNode curNode)
{
    bool ret = false;
    if(!curNode)
    {
        return false;
    }
    if(curNode->val < tmpNode->val)
    {
        if(!curNode->leftNode)
        {
            curNode->leftNode = tmpNode;
            tmpNode->pre = curNode;
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
    else if(curNode->val > tmpNode->val)
    {
        if(!curNode->rightNode)
        {
            curNode->rightNode = tmpNode;
            tmpNode->pre = curNode;
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

template<typename T>
TreeNode<T>* BlcTree<T>::NewNode()
{
    return new Node();
}

template <typename T>
int BlcTree<T>::getLeftDepth(PtNode curNode)
{
    return getDepth(curNode->leftDepth);
}
template <typename T>
int BlcTree<T>::getRightDepth(PtNode curNode)
{
    return getDepth(curNode->rightNode);
}

template <typename T>
void BlcTree<T>::setFatherNode()
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
template <typename T>
int BlcTree<T>::getCirCleType(PtNode curNode)
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