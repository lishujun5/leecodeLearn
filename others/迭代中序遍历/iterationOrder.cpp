/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode *> data;
        set<TreeNode *> visited;
        data.push(root);
        TreeNode *tmpNode = NULL;
        while(!data.empty() || tmpNode != NULL)
        {
            if(tmpNode == NULL)a
            {
                tmpNode = data.top();
                if((tmpNode->left && visited.count(tmpNode->left)) || tmpNode->left == NULL)   //根节点左节点已经被访问，则输出当前节点
                {

                    cout<<"first ret push"<<tmpNode->val<<endl;
                    visited.insert(tmpNode);
                    ret.push_back(tmpNode->val);
                    data.pop();
                    if(tmpNode->right)
                    {
                        tmpNode = tmpNode->right;
                    }
                    else
                    {
                        tmpNode = NULL;
                    }
                }
            }
            else
            {
                if(tmpNode->left)      //左节点存在
                {
                    cout<<"second push"<<tmpNode->val<<endl;
                    data.push(tmpNode);   //保存当前节点
                    tmpNode = tmpNode->left;
                }
                else           //左节点不存在，输出当前根节点
                {
                    visited.insert(tmpNode);
                    cout<<"second ret push"<<tmpNode->val<<endl;
                    ret.push_back(tmpNode->val);
                    if(tmpNode->right)
                    {
                        tmpNode = tmpNode->right;
                    }
                    else
                    {
                        tmpNode = NULL;
                    }
                }
            }

        }
        return ret;
    }
};