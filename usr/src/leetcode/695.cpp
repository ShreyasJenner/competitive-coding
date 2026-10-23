#include <iostream>
#include <string>
#include <vector>

/*
LC 695 Max Area of Island (solve cold: no lesson)

grid[r][c] is 1 (land) or 0 (water). An island is land connected
up/down/left/right. Its area is its number of cells.
Return the largest area, or 0 if there is no land.
1 <= m, n <= 50.
*/
class Solution {
    private:
    int m, n;
    // function that floods water on the islands through dfs to assist in counting the number
    // of land cells available to an island
    int dfsFlood(std::vector<std::vector<int>>& grid, int r, int c) {
        if(r == -1 || r == m || c == -1 || c == n || grid[r][c] == 0) {
            return 0;
        }

        grid[r][c] = 0;

        return 1 
        + dfsFlood(grid, r + 1, c) 
        + dfsFlood(grid, r - 1, c)
        + dfsFlood(grid, r, c + 1)
        + dfsFlood(grid, r, c - 1);
    }

    public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        int max_flooded = 0;

        int tmp;

        m = grid.size();
        n = grid[0].size();
        max_flooded = 0;

        for(int r = 0; r < m; r++) {
            for(int c = 0; c < n; c++) {
                tmp = dfsFlood(grid, r, c);
                max_flooded = std::max(tmp, max_flooded);
            }
        }
        
        return max_flooded;
    }
};

#ifndef TEST
int main() {
    Solution sol;
    std::vector<std::vector<std::string>> examples = {
        {
         "0010000100000",
         "0000000111000",
         "0110100000000",
         "0100110010100",
         "0100110011100",
         "0000000000100",
         "0000000111000",
         "0000000110000"
        },  // 6
        {"00000000"},       // 0
        {"111", "101", "111"}, // 8
    };
    for (const auto &rows : examples) {
        std::vector<std::vector<int>> grid;
        for (const std::string &r : rows) {
            grid.emplace_back();
            for (char c : r) grid.back().push_back(c - '0');
        }
        std::cout << sol.maxAreaOfIsland(grid) << '\n';
    }
    return 0;
}
#endif
