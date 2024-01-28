//https://leetcode.com/problems/can-place-flowers/description/

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> canPlaceFlowers(vector<int>& flowerbed, int n) {
        int N = flowerbed.size(),cnt=0,max;
        vector<int> s(N,0);

        for(int i=0;i<N;i++) {
            if(flowerbed[i]==1 && i-2>=0) {
                s[i-2] = 1;
                cnt++;
            }
        }
        for(int i=1;i<N-1;i++) {
            if(!flowerbed[i-1]&&!flowerbed[i+1]&&!flowerbed[i])
                s[i] = 1;
        }
        for(int i=0;i<N;i++) {
            if(flowerbed[i]==1 && i+2<N) {
                s[i+2] = 1;
                cnt++;
            }
        }

        for(int i=0;i<N;i++) {
            if(s[i]!=0)
                cnt++;
            else {
                max += ceil((float)cnt/2);
            }
        }
        if(n<=max)
            cout << true << '\n';
        else
            cout << false << '\n';
        return s;
    }
};

int main() {
    Solution s;
    vector<int> d = {0,0,1,0,1};
    vector<int> t = s.canPlaceFlowers(d,1);

    for(auto el : d) {
        cout << el << " ";
    }
    cout << '\n';
    for(auto el: t) {
        cout << el << " ";
    }
    cout << '\n';
}
