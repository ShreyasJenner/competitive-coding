#include <iostream>
#include <vector>

class Solution {
private:
  void compression(std::vector<int> &fruits, std::vector<int> &occurrences,
                   std::vector<int> &frequencies) {

    int itr, f_itr, o_itr;
    itr = 0;
    occurrences.push_back(fruits[itr]);
    frequencies.push_back(1);
    f_itr = o_itr = 0;
    for (itr = 1; itr != fruits.size(); itr++) {
      if (occurrences[o_itr] == fruits[itr]) {
        frequencies[f_itr]++;
      } else {
        occurrences.push_back(fruits[itr]);
        o_itr++;
        frequencies.push_back(1);
        f_itr++;
      }
    }
  }

  void print_vector(std::vector<int> &a) {
    for (auto itr : a) {
      std::cout << itr << " ";
    }
    std::cout << '\n';
  }

public:
  int totalFruit(std::vector<int> &fruits) {
    std::vector<int> occurrences, freq;

    if (fruits.size() == 1) {
      return 1;
    }

    compression(fruits, occurrences, freq);

    if (occurrences.size() == 1) {
      return freq[0];
    }

    int a = occurrences[0], b = occurrences[1];
    int rl = 0, m_rl = 0;

    for (int i = 0; i < occurrences.size(); i++) {
      if (occurrences[i] == a || occurrences[i] == b) {
        rl += freq[i];
      } else {
        a = occurrences[i - 1];
        b = occurrences[i];
        rl = freq[i - 1] + freq[i];
      }

      m_rl = m_rl > rl ? m_rl : rl;
    }

    return m_rl;
  }
};

int main() {
  std::vector<int> fruits = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};

  Solution s;

  std::cout << s.totalFruit(fruits) << '\n';

  return 0;
}
