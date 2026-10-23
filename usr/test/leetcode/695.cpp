#include "../../src/leetcode/695.cpp"
#include "../testlib.hpp"

#include <algorithm>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<int>>;

// "0110","0100" -> grid of 0/1 ints
Grid make(const std::vector<std::string> &rows) {
  Grid g;
  for (const std::string &r : rows) {
    g.emplace_back();
    for (char c : r) g.back().push_back(c - '0');
  }
  return g;
}

std::string show(const Grid &g) {
  if (g.size() * g[0].size() > 40) return std::to_string(g.size()) + "x" + std::to_string(g[0].size()) + " grid";
  std::string s;
  for (const auto &row : g) {
    if (!s.empty()) s += "/";
    for (int v : row) s += char('0' + v);
  }
  return s;
}

// Reference answer: union-find with component sizes, no DFS.
int reference(const Grid &g) {
  int m = g.size(), n = g[0].size();
  std::vector<int> parent(m * n), size(m * n, 1);
  std::iota(parent.begin(), parent.end(), 0);
  auto find = [&](int x) {
    while (parent[x] != x) x = parent[x] = parent[parent[x]];
    return x;
  };
  auto unite = [&](int a, int b) {
    a = find(a), b = find(b);
    if (a != b) parent[a] = b, size[b] += size[a];
  };
  for (int r = 0; r < m; r++)
    for (int c = 0; c < n; c++) {
      if (g[r][c] != 1) continue;
      if (r > 0 && g[r - 1][c] == 1) unite(r * n + c, (r - 1) * n + c);
      if (c > 0 && g[r][c - 1] == 1) unite(r * n + c, r * n + c - 1);
    }
  int best = 0;
  for (int i = 0; i < m * n; i++)
    if (g[i / n][i % n] == 1 && find(i) == i) best = std::max(best, size[i]);
  return best;
}

// Your function may change the grid, so it gets a copy.
void check(Grid g, int want, std::string label = "") {
  std::string shown = label.empty() ? show(g) : label;
  Solution sol;
  int got = sol.maxAreaOfIsland(g);
  testlib::record(got == want, shown, std::to_string(got), std::to_string(want));
}

// One case covering `runs` random grids; reports the first mismatch.
void stress(int runs) {
  std::mt19937 rng(695);
  for (int r = 0; r < runs; r++) {
    int m = 1 + rng() % 8, n = 1 + rng() % 8, land = 20 + rng() % 60;
    Grid g(m, std::vector<int>(n));
    for (auto &row : g)
      for (int &c : row) c = (int)(rng() % 100) < land ? 1 : 0;
    int want = reference(g);
    Solution sol;
    Grid copy = g;
    int got = sol.maxAreaOfIsland(copy);
    if (got != want) {
      testlib::record(false, "random " + show(g), std::to_string(got), std::to_string(want));
      return;
    }
  }
  testlib::record(true, std::to_string(runs) + " random grids", "all match reference", "");
}

int main() {
  // LeetCode examples
  check(make({"0010000100000",
              "0000000111000",
              "0110100000000",
              "0100110010100",
              "0100110011100",
              "0000000000100",
              "0000000111000",
              "0000000110000"}), 6);
  check(make({"00000000"}), 0);
  // tiny grids
  check(make({"1"}), 1);
  check(make({"0"}), 0);
  check(make({"10101"}), 1);
  check(make({"1", "1", "0", "1"}), 2);
  // diagonal cells are NOT connected
  check(make({"10", "01"}), 1);
  check(make({"101", "010", "101"}), 1);
  // a cell reachable by two paths counts once
  check(make({"111", "101", "111"}), 8);
  check(make({"11", "11"}), 4);
  // the biggest island is not the first one the scan finds
  check(make({"1001", "0011", "0111"}), 6);
  check(make({"11000", "00001", "00111", "00011"}), 6);
  // limits: m, n <= 50
  check(Grid(50, std::vector<int>(50, 1)), 2500, "50x50 all land");
  check(Grid(50, std::vector<int>(50, 0)), 0, "50x50 all water");
  // a snake: one path of 1275 cells, so a recursive search goes deep
  Grid snake(50, std::vector<int>(50, 0));
  for (int r = 0; r < 50; r += 2) {
    for (int c = 0; c < 50; c++) snake[r][c] = 1;
    if (r + 1 < 50) snake[r + 1][(r / 2) % 2 ? 0 : 49] = 1;
  }
  check(snake, 1275,"50x50 snake (one long path)");
  stress(3000);
  return testlib::summary();
}
