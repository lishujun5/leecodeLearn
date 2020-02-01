/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {}
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Solution {
public:
    map<int,Node*> visited;
    Node* cloneGraph(Node* node) {
        if(node == NULL)
            return NULL;           //返回空
        if(visited.count(node->val) != 0)   //已访问
            return visited[node->val];              //返回已经访问节点
        Node *tmp = new Node(node->val);
        visited[node->val] = tmp;
        for(Node *tmpNode:node->neighbors)
        {
            if(tmpNode !=NULL)
            {
                tmp->neighbors.push_back(cloneGraph(tmpNode)); //当前节点添加 
            }
        }
        return tmp;
    }
};