#include <iostream>
#include <vector>

/*
LC 236 Lowest Common Ancestor of a Binary Tree

Given the root of a binary tree and two different nodes p and q in it, return
their lowest common ancestor: the lowest node that has both p and q as
descendants. A node counts as a descendant of itself.
2 <= number of nodes <= 1e5. All values are unique. p and q both exist.
*/

// LeetCode supplies this struct; don't change it.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Function returns the node if only it exists in the subtree. If both the target 
        // nodes exist, it returns itself. In all other cases it returns NULL 
        if(root == NULL) {
            return NULL;
        }

        if(root == p || root == q) {
            return root;
        }

        TreeNode *a = lowestCommonAncestor(root->left, p, q);
        TreeNode *b = lowestCommonAncestor(root->right, p, q);

        if(a != NULL && b != NULL) {
            return root;
        }

        return a == NULL ? b : a;
    }
};

#ifndef TEST
int main() {
    //          3
    //       /     \
    //      5       1
    //     / \     / \
    //    6   2   0   8
    //       / \
    //      7   4
    TreeNode *n[9];
    for (int v = 0; v < 9; v++) n[v] = new TreeNode(v);
    TreeNode *root = n[3];
    n[3]->left = n[5], n[3]->right = n[1];
    n[5]->left = n[6], n[5]->right = n[2];
    n[1]->left = n[0], n[1]->right = n[8];
    n[2]->left = n[7], n[2]->right = n[4];

    Solution sol;
    std::cout << sol.lowestCommonAncestor(root, n[5], n[1])->val << '\n';  // 3
    std::cout << sol.lowestCommonAncestor(root, n[5], n[4])->val << '\n';  // 5
    std::cout << sol.lowestCommonAncestor(root, n[7], n[4])->val << '\n';  // 2

    for (TreeNode *t : n) delete t;
    return 0;
}
#endif
