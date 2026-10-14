// Shared helpers for the tests in usr/test.
//
// Each test calls testlib::record() once per case, and main() ends with
// `return testlib::summary();`. summary() prints the line
//     cases: <passed> passed, <failed> failed
// which test.sh reads to total the cases across all test files.
#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace testlib {

inline int passed = 0;
inline int failed = 0;

// "a", "b" -> "\"a\" \"b\""
inline std::string quoted(const std::vector<std::string> &v) {
  std::string s;
  for (const std::string &x : v) s += (s.empty() ? "\"" : " \"") + x + '"';
  return s.empty() ? "(none)" : s;
}

// Prints one PASS/FAIL line. `want` is shown only for failures.
inline void record(bool ok, const std::string &input, const std::string &got,
                   const std::string &want) {
  (ok ? passed : failed)++;
  std::cout << (ok ? "PASS  " : "FAIL  ") << input << "  ->  " << got << '\n';
  if (!ok) std::cout << "      want: " << want << '\n';
  // Flush so finished cases are still printed (and counted) if a later one crashes.
  std::cout.flush();
}

// Prints the summary line test.sh parses; returns main()'s exit code.
inline int summary() {
  std::cout << "cases: " << passed << " passed, " << failed << " failed\n";
  return failed != 0;
}

} // namespace testlib
