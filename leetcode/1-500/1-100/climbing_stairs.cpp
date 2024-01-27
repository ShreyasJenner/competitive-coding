//https://leetcode.com/problems/climbing-stairs/description/

#include <iostream>

class Solution {
public:
    int climbStairs(int n) {
        if(n==1)
            return 1;

        int a=1,b=1,c;
        for(int i=1;i<n;i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
};

int main() {
    Solution s;
    std::cout << s.climbStairs(5) << '\n';
}
