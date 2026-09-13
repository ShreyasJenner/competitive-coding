#include <iostream>
#include <string>
#include <unordered_map>

int longestKSubstr(const std::string &s, int k) {
  int l_itr, r_itr, rl, max_rl;
  l_itr = r_itr = rl = max_rl = 0;
  std::unordered_map<char, int> lookup;

  while (r_itr != s.length()) {
    if (lookup.find(s[l_itr]) != lookup.end()) {
      lookup[s[r_itr]]++;
    } else {
      lookup[s[r_itr]] = 1;
    }
    r_itr++;
    rl++;

    while (lookup.size() > k) {
      lookup[s[l_itr]]--;
      rl--;

      if (lookup[s[l_itr]] == 0) {
        lookup.erase(s[l_itr]);
      }
      l_itr++;
    }

    max_rl = max_rl > rl ? max_rl : rl;
  }

  return lookup.size() < k ? -1 : max_rl;
}

int main() {
  std::string s = "aabaaab";
  int k = 2;

  std::cout << longestKSubstr(s, k) << '\n';

  return 0;
}
