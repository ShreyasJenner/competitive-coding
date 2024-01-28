//https://leetcode.com/problems/largest-divisible-subset/description

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int i,j;
        int max_index = 0;
        vector<int> divcount(nums.size(), 1);
        vector<int> prev(nums.size(), -1);
        vector<int> ans;

        for(i=1;i<nums.size();i++) {
            for(j=0;j<i;j++) {
                if(nums[i] % nums[j] == 0) {
                    if(divcount[i] < divcount[j] + 1) {
                        divcount[i] = divcount[j] + 1;
                        prev[i] = j;
                    }
                }
            }
            if(divcount[max_index] < divcount[i])
                max_index = i;
        }

        while(max_index>=0) {
            ans.push_back(nums[max_index]);
            max_index = prev[max_index];
        }
        
        return ans;

    }
};

int main() {
    Solution s;

    vector<int> nums = {5,9,18,54,108,540,90,180,360,720};
    vector<int> t;

    t = s.largestDivisibleSubset(nums);

    for(auto el : t) 
        cout << el << " ";
    cout << '\n';

}
