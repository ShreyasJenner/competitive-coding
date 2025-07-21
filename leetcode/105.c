#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

void preorderTraversal(struct TreeNode *root) {
  if (root == NULL)
    return;

  printf("%d ", root->val);

  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

void inorderTraversal(struct TreeNode *root) {
  if (root == NULL)
    return;
  inorderTraversal(root->left);
  printf("%d ", root->val);
  inorderTraversal(root->right);
}

struct TreeNode *create_node(int val) {
  struct TreeNode *ptr;

  ptr = (struct TreeNode *)malloc(sizeof(struct TreeNode));
  ptr->val = val;
  ptr->left = NULL;
  ptr->right = NULL;

  return ptr;
}

int inorder_index(int *inorder, int inorderSize, int val) {
  int i;

  for (i = 0; i < inorderSize; i++) {
    if (inorder[i] == val) {
      return i;
    }
  }
  return -1;
}

void recursive_build(struct TreeNode **parent_conn, int *p_idx, int *preorder,
                     int *inorder, int inorderSize, int start, int stop) {
  int i_idx;

  *parent_conn = create_node(preorder[*p_idx]);

  i_idx = inorder_index(inorder, inorderSize, preorder[*p_idx]);

  if (i_idx - 1 >= start) {
    *p_idx = *p_idx + 1;
    recursive_build(&(*parent_conn)->left, p_idx, preorder, inorder,
                    inorderSize, start, i_idx - 1);
  }

  if (i_idx + 1 <= stop) {
    *p_idx = *p_idx + 1;
    recursive_build(&(*parent_conn)->right, p_idx, preorder, inorder,
                    inorderSize, i_idx + 1, stop);
  }
}

struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder,
                           int inorderSize) {
  struct TreeNode *root;
  int i_idx, start, stop, p_idx;

  root = create_node(preorder[0]);
  i_idx = inorder_index(inorder, inorderSize, preorder[0]);
  start = 0;
  stop = preorderSize - 1;
  p_idx = 0;

  if (i_idx - 1 >= start) {
    p_idx++;
    recursive_build(&root->left, &p_idx, preorder, inorder, inorderSize, start,
                    i_idx - 1);
  }

  if (i_idx + 1 <= stop) {
    p_idx++;
    recursive_build(&root->right, &p_idx, preorder, inorder, inorderSize,
                    i_idx + 1, stop);
  }

  return root;
}

int main() {
  // int preorder[] = {3, 9, 20, 15, 7};
  // int inorder[] = {9, 3, 15, 20, 7};
  int preorder[] = {-1};
  int inorder[] = {-1};

  int size = 1;
  struct TreeNode *root = buildTree(preorder, size, inorder, size);

  preorderTraversal(root);
  printf("\n");
  inorderTraversal(root);
  printf("\n");

  return 0;
}
