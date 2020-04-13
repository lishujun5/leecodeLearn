#pragma once
/*二叉树节点*/
template <class T>
struct TreeNode
{
        TreeNode():leftNode(nullptr),rightNode(nullptr),val(0){}
        TreeNode(const T& value):leftNode(nullptr),rightNode(nullptr),val(value){}
        TreeNode* leftNode;
        TreeNode* rightNode;
        T val;
};
/*平衡二叉树节点*/
template <class T>
struct blcTreeNode
{
    blcTreeNode():leftNode(nullptr),rightNode(nullptr),val(0),rightDepth(0),leftDepth(0),pre(nullptr){}
    blcTreeNode(const T& value):leftNode(nullptr),rightNode(nullptr),val(value),rightDepth(0),leftDepth(0),pre(nullptr){}
    blcTreeNode* leftNode;
    blcTreeNode* rightNode;
    int rightDepth;
    int leftDepth;
    blcTreeNode<T>* pre;  //父节点
    T val;
};
template <class T>
struct SearchNode
{
        SearchNode():leftNode(nullptr),rightNode(nullptr),val(0),pre(nullptr){}
        SearchNode(const T& value):leftNode(nullptr),rightNode(nullptr),val(value),pre(nullptr){}
        SearchNode* leftNode;
        SearchNode* rightNode;
        SearchNode* pre;
        T val;
};
/*红黑树节点*/
typedef enum
{
    RED = 0,
    BLACK
}RBtreeColor;
template <class T>
struct RBTreeNode
{
    RBTreeNode():leftNode(nullptr),rightNode(nullptr),val(0),color(RED),pre(nullptr){}
    RBTreeNode(const T& value):leftNode(nullptr),rightNode(nullptr),val(value),color(RED),pre(nullptr){}
    RBTreeNode* leftNode;
    RBTreeNode* rightNode;
    int color;
    RBTreeNode* pre;
    T val;
};
