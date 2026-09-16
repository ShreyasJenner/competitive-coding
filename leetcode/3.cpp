#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  int lengthOfLongestSubstring(std::string s) {
    std::vector<int> freq(256, 0);
    int l_itr, r_itr, m_rl, n;

    l_itr = 0;
    m_rl = 0;
    n = s.size();
    for (r_itr = 0; r_itr < n; r_itr++) {

      if (freq[s[r_itr]] == 0) {
        freq[s[r_itr]]++;
      } else {
        m_rl = std::max(r_itr - l_itr, m_rl);
        freq[s[r_itr]]++;

        while (freq[s[r_itr]] != 1) {
          freq[s[l_itr]]--;
          l_itr++;
        }
      }
    }

    return std::max(m_rl, r_itr - l_itr);
  }
};

int main() {
  Solution s;

  std::cout << s.lengthOfLongestSubstring("abcabcbb") << '\n';
}
