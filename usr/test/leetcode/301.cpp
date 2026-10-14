#include "../../src/leetcode/301.cpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static int failures = 0;

void check(std::string in, std::vector<std::string> want) {
  Solution sol;
  std::vector<std::string> got = sol.removeInvalidParentheses(in);
  std::sort(got.begin(), got.end());
  std::sort(want.begin(), want.end());
  bool ok = got == want;
  if (!ok) failures++;
  std::cout << (ok ? "PASS  " : "FAIL  ") << '"' << in << "\"  ->";
  for (const std::string &g : got) std::cout << " \"" << g << '"';
  std::cout << '\n';
}

int main() {
  check("()())()", {"(())()", "()()()"});
  check("(a)())()", {"(a())()", "(a)()()"});
  check(")(", {""});
  check("())", {"()"});
  check("x(", {"x"});
  check("((()", {"()"});
  check(")(f", {"f"});
  return failures != 0;
}
