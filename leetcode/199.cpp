#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class TreeNode {
public:
  int val;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;

  TreeNode() { this->val = 0; }

  TreeNode(int x) { this->val = x; }

  TreeNode(int x, TreeNode *left, TreeNode *right) {
    this->val = x;
    this->left = left;
    this->right = right;
  }
};

class Solution {
public:
  int height(TreeNode *root) {
    if (root == nullptr)
      return -1;

    int l_ht = height(root->left);
    int r_ht = height(root->right);

    return l_ht > r_ht ? l_ht + 1 : r_ht + 1;
  }

  vector<int> rightSideView(TreeNode *root) {
    int ht = height(root);
    int lvl, idx;

    vector<int> ans;
    stack<tuple<TreeNode *, int>> stck;
    TreeNode *ptr;

    idx = 0;
    stck.push(make_tuple(root, 0));
    while (idx <= ht) {
      ptr = get<0>(stck.top());
      lvl = get<1>(stck.top());
      stck.pop();

      if (ptr != nullptr) {
        stck.push(make_tuple(ptr->left, lvl + 1));
        stck.push(make_tuple(ptr->right, lvl + 1));

        if (lvl >= idx) {
          ans.push_back(ptr->val);
          idx++;
        }
      }
    }

    return ans;
  }
};

int main() {
  Solution s;

  TreeNode t1, t2, t3, t4, t5;

  t5 = TreeNode(5);
  t4 = TreeNode(4);
  t3 = TreeNode(3);
  t2 = TreeNode(2, &t4, &t5);
  t1 = TreeNode(1, &t2, &t3);

  vector<int> ans = s.rightSideView(&t1);

  for (auto val : ans) {
    cout << val << " ";
  }
  cout << '\n';

  return 0;
}
