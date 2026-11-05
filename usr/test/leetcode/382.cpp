#include "../../src/leetcode/382.cpp"
#include "../testlib.hpp"

#include <cmath>
#include <cstdio>
#include <map>
#include <random>
#include <string>
#include <vector>

// Every node made by build(), so destroy() can free them all even if a
// solution relinked the list (say, into a cycle).
std::vector<ListNode *> made;

ListNode *build(const std::vector<int> &v) {
  ListNode *head = nullptr;
  for (size_t i = v.size(); i-- > 0;) {
    ListNode *node = new ListNode(v[i]);
    node->next = head;
    head = node;
    made.push_back(node);
  }
  return head;
}

// Walks at most `limit` nodes, so that a cycle can't make it run forever.
std::vector<int> values(ListNode *head, size_t limit) {
  std::vector<int> v;
  for (; head && v.size() < limit; head = head->next) v.push_back(head->val);
  return v;
}

void destroy(ListNode *) {
  for (ListNode *node : made) delete node;
  made.clear();
}

std::string show(const std::vector<int> &v) {
  if (v.size() > 12) return std::to_string(v.size()) + "-node list";
  std::string s = "[";
  for (size_t i = 0; i < v.size(); i++) s += (i ? "," : "") + std::to_string(v[i]);
  return s + "]";
}

// How far `seen` is from `expected`: the sum of (seen - expected)^2 / expected
// over all cells (Pearson's chi-square). With k cells, a fair picker scores
// about k - 1, give or take sqrt(2(k - 1)). The limit allows 10 of those
// steps and more, so a correct solution fails by bad luck less than once in
// a million runs. A biased picker scores in the hundreds or thousands.
double chi_square(const std::vector<long> &seen, const std::vector<double> &expected) {
  double score = 0;
  for (size_t i = 0; i < seen.size(); i++) {
    double d = seen[i] - expected[i];
    score += d * d / expected[i];
  }
  return score;
}

double limit(int cells) { return cells - 1 + 10 * std::sqrt(2.0 * (cells - 1)) + 10; }

std::string fmt(double x) {
  char buf[32];
  snprintf(buf, sizeof buf, "%.1f", x);
  return buf;
}

// Calls getRandom `calls` times and checks that every value is in the list
// and that each value comes up in proportion to how many nodes hold it.
void check_fair(const std::vector<int> &v, int calls, const std::string &label = "") {
  std::string shown = (label.empty() ? show(v) : label) + ", " + std::to_string(calls) + " calls";
  ListNode *head = build(v);
  std::map<int, int> slot;  // value -> cell
  for (int x : v) slot.emplace(x, slot.size());
  std::vector<long> seen(slot.size());
  std::vector<double> expected(slot.size());
  for (int x : v) expected[slot[x]] += (double)calls / v.size();
  {
    Solution sol(head);
    for (int c = 0; c < calls; c++) {
      int got = sol.getRandom();
      if (!slot.count(got)) {
        testlib::record(false, shown, "returned " + std::to_string(got),
                        "only values that are in the list");
        destroy(head);
        return;
      }
      seen[slot[got]]++;
    }
  }
  bool unchanged = values(head, v.size() + 1) == v;
  destroy(head);
  if (!unchanged) {
    testlib::record(false, shown, "the list was changed (e.g. its last node no longer points to nullptr)",
                    "leave the list as it was: it belongs to the caller");
    return;
  }
  if (slot.size() == 1) {
    testlib::record(true, shown, "always " + std::to_string(v[0]), "");
    return;
  }
  double score = chi_square(seen, expected);
  std::string got = "unfairness " + fmt(score);
  if (slot.size() <= 6) {
    got += " (counts:";
    for (auto [x, i] : slot) got += " " + std::to_string(x) + "x" + std::to_string(seen[i]);
    got += ")";
  }
  testlib::record(score < limit(slot.size()), shown, got,
                  "unfairness under " + fmt(limit(slot.size())) +
                      " (each node equally likely)");
}

// Each call must be a fresh draw, not a pattern. A picker that cycles
// 1,2,3,1,2,3 is fair one call at a time but gives only 3 of the 9 possible
// (previous, next) pairs. Counts every consecutive pair.
void check_pairs(const std::vector<int> &v, int calls) {
  int n = v.size();
  std::string shown = show(v) + ", " + std::to_string(calls) + " calls, consecutive pairs";
  ListNode *head = build(v);
  std::map<int, int> slot;
  for (int i = 0; i < n; i++) slot[v[i]] = i;  // values here are distinct
  std::vector<long> seen(n * n);
  std::vector<double> expected(n * n, (double)(calls - 1) / (n * n));
  bool ok = true;
  {
    Solution sol(head);
    int prev = -1;
    for (int c = 0; c < calls && ok; c++) {
      int got = sol.getRandom();
      if (!slot.count(got)) ok = false;
      else {
        if (prev >= 0) seen[prev * n + slot[got]]++;
        prev = slot[got];
      }
    }
  }
  destroy(head);
  if (!ok) {
    testlib::record(false, shown, "a value not in the list", "only values that are in the list");
    return;
  }
  double score = chi_square(seen, expected);
  testlib::record(score < limit(n * n), shown, "unfairness " + fmt(score),
                  "unfairness under " + fmt(limit(n * n)) + " (each pair equally likely)");
}

// Two objects alive at once must not share state.
void check_two_lists() {
  std::vector<int> a = {1, 2}, b = {7, 8, 9};
  ListNode *ha = build(a), *hb = build(b);
  std::vector<long> sa(2), sb(3);
  bool ok = true;
  {
    Solution x(ha), y(hb);
    for (int c = 0; c < 30000 && ok; c++) {
      int p = x.getRandom(), q = y.getRandom();
      if (p < 1 || p > 2 || q < 7 || q > 9) ok = false;
      else sa[p - 1]++, sb[q - 7]++;
    }
  }
  destroy(ha), destroy(hb);
  std::string shown = "[1,2] and [7,8,9] at the same time, 30000 calls each";
  if (!ok) {
    testlib::record(false, shown, "a value from the wrong list", "each object uses its own list");
    return;
  }
  double score = chi_square(sa, {15000, 15000}) + chi_square(sb, {10000, 10000, 10000});
  testlib::record(score < limit(4), shown, "unfairness " + fmt(score),
                  "unfairness under " + fmt(limit(4)));
}

std::vector<int> random_list(int n, unsigned seed) {
  std::mt19937 rng(seed);
  std::vector<int> v(n);
  for (int &x : v) x = (int)(rng() % 20001) - 10000;
  return v;
}

int main() {
  // LeetCode example
  check_fair({1, 2, 3}, 60000);
  // one node: the only answer
  check_fair({5}, 100);
  check_fair({-10000}, 100);
  // two nodes: a coin flip
  check_fair({4, 9}, 60000);
  // the first and the last node must be as likely as the middle ones
  check_fair({10, 20, 30, 40, 50}, 100000);
  check_fair({-3, 0, 3, 6, 9, 12}, 100000);
  // repeated values: 1 is on 3 of the 4 nodes, so it comes up 3/4 of the time
  check_fair({1, 1, 2, 1}, 80000);
  check_fair({7, 7, 7}, 1000);
  // longer lists
  check_fair(random_list(100, 100), 50000, "100 random values");
  check_fair(random_list(10000, 10000), 1000, "10000 random values");
  {
    std::vector<int> v(100, 1);
    v.back() = 2;
    check_fair(v, 100000, "99 ones, then one 2");
  }
  // independence between calls
  check_pairs({1, 2, 3}, 90000);
  check_pairs({4, 5, 6, 7}, 160000);
  check_two_lists();
  return testlib::summary();
}
