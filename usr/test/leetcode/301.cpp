#include "../../src/leetcode/301.cpp"
#include "../testlib.hpp"

#include <algorithm>
#include <string>
#include <vector>

void check(std::string in, std::vector<std::string> want) {
  Solution sol;
  std::vector<std::string> got = sol.removeInvalidParentheses(in);
  std::sort(got.begin(), got.end());
  std::sort(want.begin(), want.end());
  testlib::record(got == want, '"' + in + '"', testlib::quoted(got), testlib::quoted(want));
}

int main() {
  check("()())()", {"(())()", "()()()"});
  check("(a)())()", {"(a())()", "(a)()()"});
  check(")(", {""});
  check("())", {"()"});
  check("x(", {"x"});
  check("((()", {"()"});
  check(")(f", {"f"});
  return testlib::summary();
}
