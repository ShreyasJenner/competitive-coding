#include "../../src/leetcode/301.cpp"
#include "../testlib.hpp"

#include <algorithm>
#include <random>
#include <set>
#include <string>
#include <vector>

// `got` is sorted but NOT deduplicated, so an answer produced twice fails.
void check(std::string in, std::vector<std::string> want) {
  Solution sol;
  std::vector<std::string> got = sol.removeInvalidParentheses(in);
  std::sort(got.begin(), got.end());
  std::sort(want.begin(), want.end());
  testlib::record(got == want, '"' + in + '"', testlib::quoted(got), testlib::quoted(want));
}

bool valid(const std::string &t) {
  int open = 0;
  for (char c : t) {
    if (c == '(') open++;
    else if (c == ')' && --open < 0) return false;
  }
  return open == 0;
}

// Reference answer: try every deletion mask, keep the valid strings with the fewest deletions.
std::vector<std::string> brute(const std::string &s) {
  int n = s.size(), best = n + 1;
  std::set<std::string> ans;
  for (int mask = 0; mask < (1 << n); mask++) {
    std::string t;
    for (int k = 0; k < n; k++)
      if (!(mask >> k & 1)) t += s[k];
    int d = __builtin_popcount(mask);
    if (d > best || !valid(t)) continue;
    if (d < best) best = d, ans.clear();
    ans.insert(t);
  }
  return {ans.begin(), ans.end()};
}

// One case covering `runs` random strings; reports the first mismatch.
void stress(int runs) {
  std::mt19937 rng(301);
  for (int r = 0; r < runs; r++) {
    int n = rng() % 15;
    std::string s;
    for (int k = 0; k < n; k++) s += "((()))a"[rng() % 7];
    Solution sol;
    std::vector<std::string> got = sol.removeInvalidParentheses(s), want = brute(s);
    std::sort(got.begin(), got.end());
    if (got != want) {
      testlib::record(false, "random \"" + s + '"', testlib::quoted(got), testlib::quoted(want));
      return;
    }
  }
  testlib::record(true, std::to_string(runs) + " random strings", "all match brute force", "");
}

int main() {
  check("()())()", {"(())()", "()()()"});
  check("(a)())()", {"(a())()", "(a)()()"});
  check(")(", {""});
  check("())", {"()"});
  check("x(", {"x"});
  check("((()", {"()"});
  check(")(f", {"f"});
  // Lesson 3: runs of equal brackets
  check("()))))", {"()"});
  check("((a))))", {"((a))"});
  check("(()(()", {"(())", "()()"});
  check("())(()", {"()()"});
  check("(((", {""});
  stress(3000);
  return testlib::summary();
}
