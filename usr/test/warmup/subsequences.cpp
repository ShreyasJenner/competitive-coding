#include "../../src/warmup/subsequences.cpp"
#include "../testlib.hpp"

#include <algorithm>
#include <string>
#include <vector>

// Order doesn't matter, but duplicates do: "aa" really has two "a" leaves.
void check(std::string in, std::vector<std::string> want) {
  Solution sol;
  std::vector<std::string> got = sol.subsequences(in);
  std::vector<std::string> printed = got;
  std::sort(got.begin(), got.end());
  std::sort(want.begin(), want.end());
  testlib::record(got == want, '"' + in + '"', testlib::quoted(printed), testlib::quoted(want));
}

int main() {
  check("", {""});
  check("a", {"", "a"});
  check("ab", {"", "a", "b", "ab"});
  check("abc", {"", "a", "b", "c", "ab", "ac", "bc", "abc"});
  check("aa", {"", "a", "a", "aa"});
  return testlib::summary();
}
