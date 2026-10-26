#include "../../src/leetcode/337.cpp"
#include "../testlib.hpp"

#include <climits>
#include <csignal>
#include <cstring>
#include <random>
#include <string>
#include <unistd.h>
#include <vector>

const int N = INT_MIN;  // "null" in a level-order list

// LeetCode's level-order format: {3, 2, 3, N, 3, N, 1} -> root 3, children 2 and 3, ...
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

// Reference answer by brute force over sets, not recursion: number the nodes
// 0..n-1, and bit i of `mask` means "rob node i". A set is allowed if no node
// is robbed together with its parent. 2^n masks, so only for small trees.
int reference(const std::vector<int> &val, const std::vector<int> &parent) {
  int n = val.size(), best = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    int sum = 0;
    bool ok = true;
    for (int i = 0; i < n && ok; i++)
      if (mask >> i & 1) {
        if (parent[i] >= 0 && (mask >> parent[i] & 1)) ok = false;
        sum += val[i];
      }
    if (ok) best = std::max(best, sum);
  }
  return best;
}

std::string show(const std::vector<int> &v) {
  if (v.size() > 15) return std::to_string(v.size()) + "-entry tree";
  std::string s = "[";
  for (size_t i = 0; i < v.size(); i++)
    s += (i ? "," : "") + (v[i] == N ? std::string("null") : std::to_string(v[i]));
  return s + "]";
}

// Every call has a time limit. Correct code takes milliseconds here, but a
// recursion that repeats work is exponential on a long vine. Then SIGALRM
// fires: report this case as failed and stop the run. Only write() is safe
// inside a signal handler, so the message is built before each call.
const int LIMIT = 2;  // seconds
char timeout_msg[512];

void write_int(int x) {
  char buf[16];
  int k = sizeof buf;
  do buf[--k] = '0' + x % 10; while (x /= 10);
  ssize_t r = write(1, buf + k, sizeof buf - k);
  (void)r;
}

void on_timeout(int) {
  ssize_t r = write(1, timeout_msg, strlen(timeout_msg));
  // The same line testlib::summary() prints, counting this case as failed.
  r = write(1, "cases: ", 7);
  write_int(testlib::passed);
  r = write(1, " passed, ", 9);
  write_int(testlib::failed + 1);
  r = write(1, " failed\n", 8);
  (void)r;
  _exit(1);
}

int timed_rob(TreeNode *root, int want, const std::string &shown) {
  snprintf(timeout_msg, sizeof timeout_msg,
           "FAIL  %s  ->  still running after %d s\n"
           "      want: %d. Is some node's call being made more than once? (later cases not run)\n",
           shown.c_str(), LIMIT, want);
  alarm(LIMIT);
  Solution sol;
  int got = sol.rob(root);
  alarm(0);
  return got;
}

void check(TreeNode *root, int want, const std::string &shown) {
  int got = timed_rob(root, want, shown);
  testlib::record(got == want, shown, std::to_string(got), std::to_string(want));
  destroy(root);
}

void check(const std::vector<int> &v, int want) { check(build(v), want, show(v)); }

// A "vine": each node hangs off the previous one, alternating left and right.
// The houses then form a street, exactly LC 198.
TreeNode *vine(const std::vector<int> &vals) {
  TreeNode *root = new TreeNode(vals[0]), *t = root;
  for (size_t i = 1; i < vals.size(); i++) t = (i % 2 ? t->left : t->right) = new TreeNode(vals[i]);
  return root;
}

// A random tree of n nodes with values from `rng() % range`. Returns the root;
// fills val/parent with node i's value and its parent's number (-1 for the root).
TreeNode *random_tree(std::mt19937 &rng, int n, int range, std::vector<int> &val, std::vector<int> &parent) {
  std::vector<TreeNode *> nodes;
  val.assign(n, 0), parent.assign(n, -1);
  for (int i = 0; i < n; i++) {
    val[i] = rng() % range;
    TreeNode *t = new TreeNode(val[i]);
    if (i) {
      for (;;) {
        int p = rng() % i;
        TreeNode *&slot = rng() % 2 ? nodes[p]->left : nodes[p]->right;
        if (!slot) { slot = t, parent[i] = p; break; }
      }
    }
    nodes.push_back(t);
  }
  return nodes[0];
}

// One case covering `runs` random trees of 1..14 nodes; reports the first mismatch.
// Small value ranges make repeated values common.
void stress(int runs) {
  std::mt19937 rng(337);
  std::vector<int> val, parent;
  for (int r = 0; r < runs; r++) {
    int n = 1 + rng() % 14;
    TreeNode *root = random_tree(rng, n, r % 2 ? 6 : 10001, val, parent);
    int want = reference(val, parent);
    std::string shown = "random " + std::to_string(n) + "-node tree";
    int got = timed_rob(root, want, shown);
    destroy(root);
    if (got != want) {
      testlib::record(false, shown, std::to_string(got), std::to_string(want));
      return;
    }
  }
  testlib::record(true, std::to_string(runs) + " random trees of 1-14 nodes", "all match reference", "");
}

int main() {
  signal(SIGALRM, on_timeout);
  // LeetCode examples
  check({3, 2, 3, N, 3, N, 1}, 7);
  check({3, 4, 5, 1, 3, N, 1}, 9);
  // one node, and a root with two children
  check({5}, 5);
  check({0}, 0);
  check({1, 2, 3}, 5);
  check({10, 1, 1}, 10);
  // skipping two levels: rob the root and its grandchildren
  check({1, 10, 10, 100, 100, 100, 100}, 401);
  // ...or skip the root and its children's children: the best plan mixes levels
  check({5, 1, 9, 8, 7, N, N, 1, 1}, 24);
  // a node's best plan depends on its subtree, not its value: two 4s, different answers
  check({0, 4, 4, 9, N, N, N, 9}, 17);
  // a vine is LC 198: [2,1,1,2] -> rob both ends
  check(vine({2, 1, 1, 2}), 4, "vine 2,1,1,2");
  stress(400);
  // 8191 nodes, all 1: levels 12, 10, ..., 0 hold 4096 + 1024 + ... + 1
  {
    std::vector<int> full(8191, 1);
    check(full, 5461);
  }
  {
    std::mt19937 rng(10000);
    std::vector<int> val, parent;
    check(random_tree(rng, 10000, 10001, val, parent), 30978207, "random 10000-node tree");
  }
  // 10000-node vine: a recursion that asks a node's question from both its
  // parent and its grandparent repeats work like LC 198's plain recursion
  check(vine(std::vector<int>(10000, 10000)), 50000000, "10000-node vine, all 10000");
  // Every answer here is 0. A memo that uses 0 to mean "not worked out yet"
  // can't tell a stored 0 from a missing one, so it recomputes forever.
  check(vine(std::vector<int>(10000, 0)), 0, "10000-node vine, all empty");
  return testlib::summary();
}
