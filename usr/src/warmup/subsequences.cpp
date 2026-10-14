#include <iostream>
#include <string>
#include <vector>

class Solution {
  std::string s, path;
  std::vector<std::string> out;

  void dfs(int i) {
    // base case, then the two children
    if(i == static_cast<int>(s.size())) {
        out.push_back(path);
        return;
    }

    dfs(i + 1);
    path.push_back(s[i]);
    dfs(i + 1);
    path.pop_back();
  }

public:
  std::vector<std::string> subsequences(std::string str) {
    s = str;
    path.clear();
    out.clear();
    dfs(0);
    return out;
  }
};

#ifndef TEST
int main() {
  Solution sol;
  for (const std::string &r : sol.subsequences("abc")) std::cout << '"' << r << "\"\n";
}
#endif