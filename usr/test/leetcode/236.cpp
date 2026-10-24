#include "../../src/leetcode/236.cpp"
#include "../testlib.hpp"

#include <climits>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int N = INT_MIN;  // "null" in a level-order list (values are within ±1e9)

// LeetCode's level-order format: {3, 5, 1, N, 2} -> root 3, children 5 and 1, ...
TreeNode *build(const std::vector<int> &v) {
  if (v.empty() || v[0] == N) return nullptr;
  TreeNode *root = new TreeNode(v[0]);
  std::vector<TreeNode *> level = {root};
  size_t i = 1, k = 0;
  while (i < v.size()) {
    TreeNode *parent = level[k++];
    if (v[i] != N) level.push_back(parent->left = new TreeNode(v[i]));
    if (++i < v.size() && v[i] != N) level.push_back(parent->right = new TreeNode(v[i]));
    i++;
  }
  return root;
}

// Iterative, so that deep trees don't need a deep stack here.
void destroy(TreeNode *root) {
  std::vector<TreeNode *> st = {root};
  while (!st.empty()) {
    TreeNode *t = st.back();
    st.pop_back();
    if (!t) continue;
    st.push_back(t->left), st.push_back(t->right);
    delete t;
  }
}

TreeNode *find(TreeNode *root, int val) {
  std::vector<TreeNode *> st = {root};
  while (!st.empty()) {
    TreeNode *t = st.back();
    st.pop_back();
    if (!t) continue;
    if (t->val == val) return t;
    st.push_back(t->left), st.push_back(t->right);
  }
  return nullptr;
}

// Reference answer, no recursion: record every node's parent, collect p's
// ancestors (p included), then walk up from q until we hit one of them.
TreeNode *reference(TreeNode *root, TreeNode *p, TreeNode *q) {
  std::unordered_map<TreeNode *, TreeNode *> parent = {{root, nullptr}};
  std::vector<TreeNode *> st = {root};
  while (!st.empty()) {
    TreeNode *t = st.back();
    st.pop_back();
    for (TreeNode *c : {t->left, t->right})
      if (c) parent[c] = t, st.push_back(c);
  }
  std::unordered_set<TreeNode *> up;
  for (TreeNode *a = p; a; a = parent[a]) up.insert(a);
  for (TreeNode *b = q;; b = parent[b])
    if (up.count(b)) return b;
}

std::string show(const std::vector<int> &v) {
  if (v.size() > 15) return std::to_string(v.size()) + "-entry tree";
  std::string s = "[";
  for (size_t i = 0; i < v.size(); i++)
    s += (i ? "," : "") + (v[i] == N ? std::string("null") : std::to_string(v[i]));
  return s + "]";
}

std::string name(TreeNode *t) {
  return t ? "node " + std::to_string(t->val) : "nullptr";
}

void check(TreeNode *root, int p, int q, int want, const std::string &shown) {
  TreeNode *pn = find(root, p), *qn = find(root, q), *wn = find(root, want);
  Solution sol;
  TreeNode *got = sol.lowestCommonAncestor(root, pn, qn);
  // Compare pointers, not values: the answer must be a node of *this* tree.
  testlib::record(got == wn, shown + " p=" + std::to_string(p) + " q=" + std::to_string(q),
                  name(got), name(wn));
  destroy(root);
}

void check(const std::vector<int> &v, int p, int q, int want) {
  check(build(v), p, q, want, show(v));
}

// A "vine": each node hangs off the previous one, alternating left and right,
// so the recursion is as deep as the tree has nodes.
TreeNode *vine(int n) {
  TreeNode *root = new TreeNode(0), *t = root;
  for (int i = 1; i < n; i++) t = (i % 2 ? t->left : t->right) = new TreeNode(i);
  return root;
}

// One case covering `runs` random trees and random (p, q); reports the first mismatch.
void stress(int runs) {
  std::mt19937 rng(236);
  for (int r = 0; r < runs; r++) {
    int n = 2 + rng() % 14;
    // Grow a random binary tree: attach node i under a random node with a free slot.
    std::vector<TreeNode *> nodes = {new TreeNode(0)};
    for (int i = 1; i < n; i++) {
      for (;;) {
        TreeNode *par = nodes[rng() % nodes.size()];
        TreeNode *&slot = rng() % 2 ? par->left : par->right;
        if (!slot) { nodes.push_back(slot = new TreeNode(i * 3 - 7)); break; }
      }
    }
    TreeNode *p = nodes[rng() % n], *q;
    do q = nodes[rng() % n]; while (q == p);
    TreeNode *want = reference(nodes[0], p, q);
    Solution sol;
    TreeNode *got = sol.lowestCommonAncestor(nodes[0], p, q);
    if (got != want) {
      testlib::record(false, "random " + std::to_string(n) + "-node tree p=" + std::to_string(p->val) +
                      " q=" + std::to_string(q->val), name(got), name(want));
      destroy(nodes[0]);
      return;
    }
    destroy(nodes[0]);
  }
  testlib::record(true, std::to_string(runs) + " random trees", "all match reference", "");
}

int main() {
  const std::vector<int> ex = {3, 5, 1, 6, 2, 0, 8, N, N, 7, 4};
  // LeetCode examples
  check(ex, 5, 1, 3);
  check(ex, 5, 4, 5);   // a node is a descendant of itself
  check({1, 2}, 1, 2, 1);
  // p and q swapped gives the same answer
  check(ex, 1, 5, 3);
  check(ex, 4, 5, 5);
  // both in one subtree: the answer is below the root
  check(ex, 7, 4, 2);
  check(ex, 6, 4, 5);
  check(ex, 0, 8, 1);
  // far apart: deepest left vs deepest right
  check(ex, 7, 8, 3);
  // the root itself is p, and q is deep
  check(ex, 3, 7, 3);
  // q is a child of p, on the right
  check({1, N, 2, N, 3}, 2, 3, 2);
  // negative values and zero
  check({-1, 0, 3, -2, 4, N, N, 8}, 8, 4, 0);
  check({-1, 0, 3, -2, 4, N, N, 8}, 8, 3, -1);
  // a vine makes the recursion as deep as the tree. LeetCode allows 1e5 nodes,
  // but ASan's bigger stack frames overflow the default 8 MB stack at about
  // that depth even for correct code, so this uses 30000.
  check(vine(30000), 29999, 15000, 15000, "30000-node vine (one long path)");
  check(vine(30000), 0, 29999, 0, "30000-node vine, p = root");
  // a complete tree of 2^17 - 1 > 1e5 nodes would exceed the limit, so 2^16 - 1
  {
    std::vector<int> full(65535);
    for (int i = 0; i < 65535; i++) full[i] = i;
    // in level order, node i's children are 2i+1 and 2i+2
    check(full, 32767, 65534, 0);   // leftmost leaf vs rightmost leaf
    check(full, 32767, 32768, 16383);  // two sibling leaves
  }
  stress(3000);
  return testlib::summary();
}
