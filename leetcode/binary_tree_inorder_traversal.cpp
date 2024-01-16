//https://leetcode.com/problems/binary-tree-inorder-traversal/description/

#include <iostream>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
//    TreeNode() : val(0), left(nullptr), right(nullptr) {}
//    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    
    void depth(TreeNode *root, std::vector<int> &v) {
        if(root==NULL)
            return ;

        depth(root->left,v);
        v.push_back(root->val);
        depth(root->right,v);
    }
    
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> visit;
        depth(root,visit);

        return visit;
    }
};

