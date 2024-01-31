//https://leetcode.com/problems/max-points-on-a-line/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(),c=0,max=0,i,j;

        sort(points.begin(), points.end());

        for(i=0;i<n;i++) {
            for(j=0;j<n;j++) {
                if(abs(points[i][0] - points[j][0]) == abs(points[i][1] - points[j][1]))
                    c++;
            }
            if(c>max)
                max = c;
            c=0;
        }

        return max;
    }
};

int main() {
    Solution s;

    vector<vector<int>> pt = {{3,2},{5,3},{4,1},{2,3},{1,4},{1,1}};

    cout << s.maxPoints(pt) << '\n';

    return 0;
}
