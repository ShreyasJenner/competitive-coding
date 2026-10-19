#include "../../src/leetcode/1106.cpp"
#include "../testlib.hpp"

#include <random>
#include <string>
#include <vector>

void check(std::string in, bool want, std::string label = "") {
  Solution sol;
  bool got = sol.parseBoolExpr(in);
  std::string shown = label.empty() ? '"' + in + '"' : label;
  testlib::record(got == want, shown, got ? "true" : "false", want ? "true" : "false");
}

// Reference answer: a stack evaluator (no recursion), so it fails differently from yours.
bool reference(const std::string &s) {
  std::vector<char> st;
  for (char c : s) {
    if (c == ',' || c == '(') continue;
    if (c != ')') { st.push_back(c); continue; }
    int t = 0, f = 0;
    while (st.back() == 't' || st.back() == 'f') {
      (st.back() == 't' ? t : f)++;
      st.pop_back();
    }
    char op = st.back();
    st.pop_back();
    bool v = op == '!' ? f > 0 : op == '&' ? f == 0 : t > 0;
    st.push_back(v ? 't' : 'f');
  }
  return st.back() == 't';
}

std::string randomExpr(std::mt19937 &rng, int depth) {
  if (depth == 0 || rng() % 3 == 0) return rng() % 2 ? "t" : "f";
  char op = "!&|"[rng() % 3];
  int kids = op == '!' ? 1 : 1 + rng() % 4;
  std::string e = std::string(1, op) + '(';
  for (int k = 0; k < kids; k++) e += (k ? "," : "") + randomExpr(rng, depth - 1);
  return e + ')';
}

// One case covering `runs` random expressions; reports the first mismatch.
void stress(int runs) {
  std::mt19937 rng(1106);
  for (int r = 0; r < runs; r++) {
    std::string s = randomExpr(rng, 1 + rng() % 5);
    Solution sol;
    bool got = sol.parseBoolExpr(s), want = reference(s);
    if (got != want) {
      testlib::record(false, "random \"" + s + '"', got ? "true" : "false", want ? "true" : "false");
      return;
    }
  }
  testlib::record(true, std::to_string(runs) + " random expressions", "all match reference", "");
}

int main() {
  // LeetCode examples
  check("&(|(f))", false);
  check("|(f,f,f,t)", true);
  check("!(&(f,t))", true);
  // single values and single operators
  check("t", true);
  check("f", false);
  check("!(f)", true);
  check("&(t,t,t)", true);
  check("|(f)", false);
  // the cursor must land right after each child
  check("&(!(t),|(f,t))", false);
  check("|(&(t,!(f)),f,!(!(f)))", true);
  check("|(&(f,t),f)", false);
  // limits: length 2*10^4
  std::string deep = std::string(6666 * 2, ' ');
  for (int k = 0; k < 6666; k++) deep[2 * k] = '!', deep[2 * k + 1] = '(';
  check(deep + "t" + std::string(6666, ')'), true, "6666 nested !( )");
  std::string wide = "|(";
  for (int k = 0; k < 9998; k++) wide += "f,";
  check(wide + "t)", true, "|( 9998 f's then t )");
  stress(3000);
  return testlib::summary();
}
