//https://leetcode.com/problems/3sum/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> temp;
        sort(nums.begin(),nums.end());
        int i=0,j=0,size=nums.size(),k;

        while(i!=size) {
            j = i+1;
            k = size-1;
            while(j<k) {
                int sum = nums[i] + nums[j] + nums[k];
                if(sum == 0) {
                    temp.insert({nums[i],nums[j],nums[k]});
                    j++;
                    k--;
                } else if(sum < 0) {
                    j++;
                } else {
                    k--;
                }
            }
            i++;
        }
        vector<vector<int>> ans(temp.begin(),temp.end());
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> v = {-1,0,1,0};
    vector<vector<int>> ans,store;

    ans = s.threeSum(v);
   
    std::cout << "[";
    for(auto el: ans) {
        std::cout << "[";
        for(auto i: el) {
            std::cout << i << ",";
        }
        std::cout << "],";
    }
    std::cout << '\b' << "]" << '\n';
    return 0;
}
