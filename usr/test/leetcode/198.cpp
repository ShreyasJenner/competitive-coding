#include "../../src/leetcode/198.cpp"
#include "../testlib.hpp"

#include <csignal>
#include <cstring>
#include <random>
#include <string>
#include <unistd.h>
#include <vector>

// Reference answer by brute force over sets, not recursion: bit i of `mask`
// means "rob house i". A set is allowed if no two set bits are neighbours.
// 2^n masks, so only for n <= 16.
int reference(const std::vector<int> &v) {
  int n = v.size(), best = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    if (mask & (mask >> 1)) continue;
    int sum = 0;
    for (int i = 0; i < n; i++)
      if (mask >> i & 1) sum += v[i];
    best = std::max(best, sum);
  }
  return best;
}

std::string show(const std::vector<int> &v) {
  if (v.size() > 12) return std::to_string(v.size()) + " houses";
  std::string s = "[";
  for (size_t i = 0; i < v.size(); i++) s += (i ? "," : "") + std::to_string(v[i]);
  return s + "]";
}

// Every case has a time limit. Correct code takes microseconds here, but a
// recursion that repeats work is exponential and never finishes on 100
// houses. Then SIGALRM fires: report this case as failed and stop the run.
// Only write() is safe inside a signal handler, so the message is built
// before each case starts.
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

void check(std::vector<int> v, int want, const std::string &shown) {
  snprintf(timeout_msg, sizeof timeout_msg,
           "FAIL  %s  ->  still running after %d s\n"
           "      want: %d. Is some call being made again with the same i? (later cases not run)\n",
           shown.c_str(), LIMIT, want);
  alarm(LIMIT);
  Solution sol;
  int got = sol.rob(v);
  alarm(0);
  testlib::record(got == want, shown, std::to_string(got), std::to_string(want));
}

void check(const std::vector<int> &v, int want) { check(v, want, show(v)); }

// One case covering `runs` random streets of 1..16 houses; reports the first mismatch.
void stress(int runs) {
  std::mt19937 rng(198);
  for (int r = 0; r < runs; r++) {
    std::vector<int> v(1 + rng() % 16);
    for (int &x : v) x = rng() % 5 == 0 ? 0 : rng() % 401;
    int want = reference(v);
    Solution sol;
    std::vector<int> copy = v;
    int got = sol.rob(copy);
    if (got != want) {
      testlib::record(false, "random " + show(v), std::to_string(got), std::to_string(want));
      return;
    }
  }
  testlib::record(true, std::to_string(runs) + " random streets of 1-16 houses", "all match reference", "");
}

std::vector<int> random_street(int n, unsigned seed) {
  std::mt19937 rng(seed);
  std::vector<int> v(n);
  for (int &x : v) x = rng() % 401;
  return v;
}

int main() {
  signal(SIGALRM, on_timeout);
  // LeetCode examples
  check({1, 2, 3, 1}, 4);
  check({2, 7, 9, 3, 1}, 12);
  // one or two houses
  check({5}, 5);
  check({0}, 0);
  check({2, 1}, 2);
  check({1, 2}, 2);
  // skipping two houses in a row: "all even houses or all odd houses" gets 3 here
  check({2, 1, 1, 2}, 4);
  check({5, 1, 1, 5}, 10);
  // the best plan for the first houses changes once a big house appears
  check({1, 3, 1, 3, 100}, 103);
  check({4, 1, 2, 7, 5, 3, 1}, 14);
  check({3, 3, 3, 3, 3}, 9);
  check({0, 0, 0}, 0);
  stress(1000);
  // 30 houses: a recursion that repeats work still finishes (just)
  check(random_street(30, 30), 3856);
  // 100 houses: it doesn't
  check(std::vector<int>(100, 400), 20000);
  check(random_street(100, 100), 11931);
  {
    std::vector<int> v(100);
    for (int i = 0; i < 100; i++) v[i] = i % 2 ? 400 : 1;
    check(v, 20000, "100 houses: 1,400,1,400,...");
  }
  check(std::vector<int>(99, 1), 50);
  // Every answer here is 0. A memo that uses 0 to mean "not worked out yet"
  // can't tell a stored 0 from a missing one, so it recomputes forever.
  check(std::vector<int>(100, 0), 0, "100 houses, all empty");
  {
    std::vector<int> v(100, 0);
    v[0] = 7, v[2] = 9;
    check(v, 16, "100 houses: 7,0,9, then 97 empty");
  }
  return testlib::summary();
}
