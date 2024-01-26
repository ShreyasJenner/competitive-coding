//https://leetcode.com/problems/count-number-of-teams/description/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numTeams(vector<int>& rating) {
        int count=0;

        vector<int>::iterator i,j;

        for(i=rating.begin()+1;i<rating.end()-1;i++) {
            int less[2] = {}, great[2] = {};
            for(j=rating.begin();j!=rating.end();j++) {
                if(*j > *i)
                    great[j>i]++;
                else if(*j < *i)
                    less[j>i]++;
            }
            count += (less[0]*great[1]) + (great[0]*less[1]);
        }
 
        return count;
    }
};

int main() {
    Solution s;

    vector<int> a = {2,5,3,4,1};
    cout << s.numTeams(a) << '\n';

    for(auto el : a) {
        cout << el << " ";
    }
    cout << '\n';

    return 0;
}
