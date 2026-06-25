#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  // function to return number of descendants for passed TreeNode pointer
  int count_descendants(TreeNode *ptr) {
    if (ptr == NULL)
      return 0;

    int leftcount = count_descendants(ptr->left);
    int rightcount = count_descendants(ptr->right);

    return leftcount + rightcount + (ptr->left != NULL) + (ptr->right != NULL);
  }

  int kthSmallest(TreeNode *root, int k) {
    int count, flag;
    TreeNode *ptr;

    ptr = root;
    flag = 0;
    count = 0;
    while (1) {

      count += count_descendants(ptr);

      if (count + 1 == k)
        return ptr->val;

      if (count + 1 > k) {

        ptr = ptr->left;
        flag = 0;
      } else {

        ptr = ptr->right;
        flag = 1;
      }

      if (!flag) {
        count -= count_descendants(ptr);
        count++;
      }

      if (ptr->left == NULL && ptr->right == NULL)
        break;
    }

    return -1;
  }
};

int main() {
  Solution s;

  return 0;
}
