//https://leetcode.com/problems/largest-divisible-subset/description

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void zero(int &ans[]) {

    }
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int count,max;
        vector<int> store,ans;
        int cover[nums.size()]={0};

        for(i=0; i<nums.size(); i++) {
            if(cover[i] == 0) {
                memset(cover, 0, nums.size());
                int k = nums[i];
                store.push_back(k);
                index = i+1;
                while(index < nums.size()) {
                    if(cover[index] == 0) {
                        for(j=i+1;j<nums.size();j++) {
                            if(nums[j] % k == 0) {
                                cover[j] = 1;
                                k = nums[j];
                                count++;
                                store.push_back(k);
                            }
                        }
                    }
                    index++;
                    if(count > max) {
                        max = count;
                        ans = store;
                    }
                    store.clear();
                }
            }
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
