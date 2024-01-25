//https://leetcode.com/problems/count-number-of-teams/description/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int numTeams(vector<int>& rating) {
        int count=0;
        set<vector<int>> s;
        vector<int> a=rating, b=rating;

        sort(a.begin(), a.end());

        for(auto i=a.begin();i!=a.end();i++) {
                    auto it = find(b.begin(), b.end(), *i);
            for(auto j=i+1;j!=a.end();j++) {
                    auto jt = find(b.begin(), b.end(), *j); 
                    if(jt - it < 0 ) {
                        break;
                    }
                for(auto k=j+1;k!=a.end();k++) {
                    auto kt = find(b.begin(), b.end(), *k); 
                    if(kt - jt > 0) {
                        count++;
                    }
                }
                    
            }
        }

        for(auto i=a.begin();i!=a.end();i++) {
                    auto it = find(b.begin(), b.end(), *i);
            for(auto j=i+1;j!=a.end();j++) {
                    auto jt = find(b.begin(), b.end(), *j); 
                    if(jt - it > 0 ) {
                        break;
                    }

                for(auto k=j+1;k!=a.end();k++) {
                    auto kt = find(b.begin(), b.end(), *k); 
                    
                    if(kt - jt < 0) {
                        count++;
                    }
                }
                    
            }
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
