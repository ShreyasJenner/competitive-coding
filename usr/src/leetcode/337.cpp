#include <iostream>
#include <vector>

/*
LC 337 House Robber III

The houses form a binary tree; root is the only entrance. You can't rob two
houses joined by an edge (a parent and its child). Return the most money you
can rob.
1 <= number of nodes <= 1e4, 0 <= Node.val <= 1e4.
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
    int rob(TreeNode* root) {
        return 0;
    }
};

#ifndef TEST
int main() {
    /*
          3            3
         / \          / \
        2   3        4   5
         \   \      / \   \
          3   1    1   3   1
    */
    TreeNode *a = new TreeNode(3);
    a->left = new TreeNode(2), a->right = new TreeNode(3);
    a->left->right = new TreeNode(3), a->right->right = new TreeNode(1);
    TreeNode *b = new TreeNode(3);
    b->left = new TreeNode(4), b->right = new TreeNode(5);
    b->left->left = new TreeNode(1), b->left->right = new TreeNode(3), b->right->right = new TreeNode(1);

    Solution sol;
    std::cout << sol.rob(a) << '\n';  // 7: 3 + 3 + 1
    std::cout << sol.rob(b) << '\n';  // 9: 4 + 5
    return 0;
}
#endif
