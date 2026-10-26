#include <iostream>
#include <vector>

/*
LC 198 House Robber

nums[i] is the money in house i, along a street. You can't rob two adjacent
houses. Return the most money you can rob.
1 <= nums.length <= 100, 0 <= nums[i] <= 400.
*/
class Solution {
    private:
    int best(std::vector<int>& memo, std::vector<int>& nums, int i, int n) {
        if(i >= n) {
            return 0;
        }
        
        if(memo[i] != -1) {
            return memo[i];
        }

        memo[i] = std::max(
            best(memo, nums, i + 1, n), 
            best(memo, nums, i + 2, n) + nums[i]
        );

        return memo[i];
    }

    public:
    int rob(std::vector<int>& nums) {
        std::vector<int> memo(nums.size(), -1);

        return best(memo, nums, 0, nums.size());
    }
};

#ifndef TEST
int main() {
    Solution sol;
    std::vector<int> a = {1, 2, 3, 1};
    std::vector<int> b = {2, 7, 9, 3, 1};
    std::cout << sol.rob(a) << '\n';  // 4
    std::cout << sol.rob(b) << '\n';  // 12
    return 0;
}
#endif
