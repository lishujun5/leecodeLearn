#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define NULLNODE (-1)
template <class T>
struct TreeNode
{
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
        typedef vector<PtNode> Order_type;  //������������
        Tree() = delete;
        Tree(const initializer_list<T>& TreeValueList):root(nullptr)
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
                    if(*iter != NULLNODE)
                    {
                        tmpNode = new Node(); //���ɽڵ�
                        tmpNode->val = *iter;
                        CrossNode.push(tmpNode);
                        tmpRootNode->leftNode = tmpNode;
                    }
                }
                else
                {
                    if(*iter != NULLNODE)
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
        ~Tree()
        {
            Order_type tmp = this->preOrder();
            for(auto i = tmp.begin() ; i != tmp.end() ; i++)
            {
                delete *i;
            }
        }
        Order_type preOrder()   //�������
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
            if(_root->leftNode)
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
        void MidOrder(Order_type& ret , PtNode _root)   //�������
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
        Order_type backOrder()  //��������
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
    private:
        PtNode root;//���ڵ�
};
