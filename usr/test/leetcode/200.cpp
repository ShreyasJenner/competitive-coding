#include "../../src/leetcode/200.cpp"
#include "../testlib.hpp"

#include <numeric>
#include <random>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<char>>;

// "11000","11000" -> grid
Grid make(const std::vector<std::string> &rows) {
  Grid g;
  for (const std::string &r : rows) g.emplace_back(r.begin(), r.end());
  return g;
}

std::string show(const Grid &g) {
  if (g.size() * g[0].size() > 40) return std::to_string(g.size()) + "x" + std::to_string(g[0].size()) + " grid";
  std::string s;
  for (const auto &row : g) s += (s.empty() ? "" : "/") + std::string(row.begin(), row.end());
  return s;
}

// Reference answer: union-find, no DFS, so it fails differently from yours.
int reference(const Grid &g) {
  int m = g.size(), n = g[0].size(), count = 0;
  std::vector<int> parent(m * n);
  std::iota(parent.begin(), parent.end(), 0);
  auto find = [&](int x) {
    while (parent[x] != x) x = parent[x] = parent[parent[x]];
    return x;
  };
  auto unite = [&](int a, int b) {
    a = find(a), b = find(b);
    if (a != b) parent[a] = b, count--;
  };
  for (int r = 0; r < m; r++)
    for (int c = 0; c < n; c++) {
      if (g[r][c] != '1') continue;
      count++;
      if (r > 0 && g[r - 1][c] == '1') unite(r * n + c, (r - 1) * n + c);
      if (c > 0 && g[r][c - 1] == '1') unite(r * n + c, r * n + c - 1);
    }
  return count;
}

// Your function may change the grid, so it gets a copy.
void check(Grid g, int want, std::string label = "") {
  std::string shown = label.empty() ? show(g) : label;
  Solution sol;
  int got = sol.numIslands(g);
  testlib::record(got == want, shown, std::to_string(got), std::to_string(want));
}

// One case covering `runs` random grids; reports the first mismatch.
void stress(int runs) {
  std::mt19937 rng(200);
  for (int r = 0; r < runs; r++) {
    int m = 1 + rng() % 8, n = 1 + rng() % 8, land = 20 + rng() % 60;
    Grid g(m, std::vector<char>(n));
    for (auto &row : g)
      for (char &c : row) c = (int)(rng() % 100) < land ? '1' : '0';
    int want = reference(g);
    Solution sol;
    Grid copy = g;
    int got = sol.numIslands(copy);
    if (got != want) {
      testlib::record(false, "random " + show(g), std::to_string(got), std::to_string(want));
      return;
    }
  }
  testlib::record(true, std::to_string(runs) + " random grids", "all match reference", "");
}

int main() {
  // LeetCode examples
  check(make({"11110", "11010", "11000", "00000"}), 1);
  check(make({"11000", "11000", "00100", "00011"}), 3);
  // tiny grids
  check(make({"1"}), 1);
  check(make({"0"}), 0);
  check(make({"10101"}), 3);
  check(make({"1", "1", "0", "1"}), 2);
  // diagonal cells are NOT connected
  check(make({"10", "01"}), 2);
  check(make({"101", "010", "101"}), 5);
  // one island reached from two directions: count it once
  check(make({"111", "101", "111"}), 1);
  check(make({"101", "101", "111"}), 1);
  check(make({"0111", "0001", "1111"}), 1);
  // limits: m, n <= 300
  check(Grid(300, std::vector<char>(300, '1')), 1, "300x300 all land");
  check(Grid(300, std::vector<char>(300, '0')), 0, "300x300 all water");
  Grid board(300, std::vector<char>(300));
  for (int r = 0; r < 300; r++)
    for (int c = 0; c < 300; c++) board[r][c] = (r + c) % 2 ? '0' : '1';
  check(board, 45000, "300x300 checkerboard");
  // a snake: one path of ~45000 cells, so a recursive search goes very deep
  Grid snake(300, std::vector<char>(300, '0'));
  for (int r = 0; r < 300; r += 2) {
    for (int c = 0; c < 300; c++) snake[r][c] = '1';
    if (r + 1 < 300) snake[r + 1][(r / 2) % 2 ? 0 : 299] = '1';
  }
  check(snake, 1, "300x300 snake (one long path)");
  stress(3000);
  return testlib::summary();
}
