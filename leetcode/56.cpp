#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  void print_vector_contents(vector<vector<int>> &strs) {
    std::cout << "Vector contents: ";
    for (auto elem : strs) {
      std::cout << "{" << elem[0] << "," << elem[1] << "}, ";
    }
    std::cout << '\n';
  }

  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    vector<vector<int>> ans;
    int i;
    bool flag;

    sort(intervals.begin(), intervals.end(),
         [](auto const &a, auto const &b) { return a[0] < b[0]; });

    ans.push_back(intervals[0]);
    for (i = 1; i < intervals.size(); i++)
      if (intervals[i][0] <= ans.back()[1]) {
        ans.back()[1] = max(ans.back()[1], intervals[i][1]);
      } else {
        ans.push_back(intervals[i]);
      }

    return ans;
  }
};

int main() {
  Solution s;

  vector<vector<int>> intervals = {{1, 4}, {0, 2}, {3, 5}};
  // vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

  vector<vector<int>> ans = s.merge(intervals);

  for (auto an : ans) {
    for (auto el : an) {
      std::cout << el << " ";
    }
    std::cout << '\n';
  }

  return 0;
}
