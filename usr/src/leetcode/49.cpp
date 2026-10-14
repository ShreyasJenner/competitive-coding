#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  void print_vector_contents(vector<string> &strs) {
    std::cout << "Vector contents: ";
    for (auto ch : strs) {
      std::cout << ch << " ";
    }
    std::cout << '\n';
  }

  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> store;
    vector<vector<string>> ans;

    for (auto str : strs) {
      string s = str;
      sort(s.begin(), s.end());
      store[s].push_back(str);
    }

    for (auto el : store) {
      ans.push_back(el.second);
    }

    return ans;
  }
};

int main() {
  Solution s;

  // vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<string> strs = {"h", "h", "h"};

  vector<vector<string>> ans = s.groupAnagrams(strs);
  for (auto an : ans) {
    for (auto str : an) {
      std::cout << str << " ";
    }
    std::cout << '\n';
  }

  return 0;
}
