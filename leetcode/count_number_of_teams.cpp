//https://leetcode.com/problems/count-number-of-teams/description/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    void asc_valid(vector<int>& v,vector<int>::iterator i,vector<int>& stac,set<vector<int>>& s) {
        if(stac.size()==3) {
            cout << "asc\n";
            for(auto el: stac) {
                cout << el << " ";
            }
            cout << '\n';
            s.insert(stac);
            stac.clear();
        }

        if(v.end() == i)
            return ;

        if(*i < *(i+1)) {
            stac.push_back(*i);
            asc_valid(v,i+1,stac,s);
        }
        stac.clear();
        asc_valid(v,i+1,stac,s);
    }

    void desc_valid(vector<int>& v,vector<int>::iterator i,vector<int>& stac,set<vector<int>>& s) {
        if(stac.size()==3) {
            cout << "desc\n";
            for(auto el : stac) {
                cout << el << " ";
            }
            cout << '\n';
            s.insert(stac);
            stac.clear();
        }

        if(v.end() == i)
            return ;

        if(*i > *(i+1)) {
            stac.push_back(*i);
            desc_valid(v,i+1,stac,s);
        }
        stac.clear();
        desc_valid(v,i+1,stac,s);
    }

    int numTeams(vector<int>& rating) {
        int count=0;
        set<vector<int>> s;
        vector<int> a;

        for(int i=0;i<rating.size();i++) {
            asc_valid(rating,rating.begin()+i,a,s);
            a.clear();
            desc_valid(rating,rating.begin()+i,a,s);
            a.clear();
        }

        
        return s.size();
    }
};

int main() {
    Solution s;

    vector<int> a = {1,2,3,4};
    cout << s.numTeams(a) << '\n';

    for(auto el : a) {
        cout << el << " ";
    }
    cout << '\n';

    return 0;
}
