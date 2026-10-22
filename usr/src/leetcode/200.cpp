#include <iostream>
#include <string>
#include <vector>

class Solution {
    private:
    /*
    TODO (Lesson 5): write a flood fill that
        starts on one land cell,
        marks every land cell it can reach (up, down, left, right) as seen,
        never visits a cell twice.
    */
    void floodFill(std::vector<std::vector<char>> &grid, int r, int c) {
        int m, n;
        
        m = grid.size();
        n = grid[0].size();

        if(grid[r][c] == '1') {
            grid[r][c] = '0';
            if(r - 1 >= 0) {
                floodFill(grid, r - 1, c); 
            }
            if(r + 1 < m) {
                floodFill(grid, r + 1, c);
            }
            if(c - 1 >= 0) {
                floodFill(grid, r, c - 1);
            }
            if(c + 1 < n) {
                floodFill(grid, r, c + 1);
            }
        }
    }


    public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        // TODO: scan every cell; each unseen land cell starts a new island
        int m, n, isl;

        m = grid.size();
        n = grid[0].size();
        isl = 0;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == '1') {
                    isl++;
                    floodFill(grid, i, j);
                }
            }
        }

        return isl;
    }
};

#ifndef TEST
int main() {
    Solution sol;
    std::vector<std::vector<std::string>> examples = {
        {"11110", "11010", "11000", "00000"},  // 1
        {"11000", "11000", "00100", "00011"},  // 3
        {"101", "101", "111"}, // 1
    };
    for (const auto &rows : examples) {
        std::vector<std::vector<char>> grid;
        for (const std::string &r : rows) grid.emplace_back(r.begin(), r.end());
        std::cout << sol.numIslands(grid) << '\n';
    }
    return 0;
}
#endif
