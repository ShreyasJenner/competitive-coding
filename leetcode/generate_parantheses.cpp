//https://leetcode.com/problems/valid-parentheses/description/

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Solution {
public:
    void generate(int open, int close, string& s, vector<string>& v) {
        if(open == 0 && close == 0)
            v.push_back(s);

        if( open > close || open < 0 || close < 0)
            return ;

        s.push_back('{');
        generate(open-1, close, s, v);
        s.pop_back();

        s.push_back('}');
        generate(open, close-1, s, v);
        s.pop_back();
    }
    vector<string> generateParenthesis(int n) {
        vector<string> s;
        string k;
        generate(n,n,k,s);

        return s;
    }
};

int main() {
    Solution s;
    vector<string> v;

    auto start = high_resolution_clock::now();
    v = s.generateParenthesis(16);
    auto stop = high_resolution_clock::now();

    /*for(auto el: v)
        std::cout << el << '\n';*/

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << '\n';
    return 0;
}
