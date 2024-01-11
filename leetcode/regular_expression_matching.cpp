#include <iostream>
#include <string>

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        int len = s.length(), plen = p.length(), i=0,j=0;
        bool mult=false,match;

        if(len!=plen && p.find('*')==std::string::npos)
            return false;

        if(p[plen-1]!='*' && p[plen-1]!='.' && p[plen-1]!=s[len-1])
            return false;

        match = false;
        while(j!=plen) {
            if(p[j]!=s[i] && p[j]!='.' && p[j]!='*') {
                if(p[j+1]!='*') {
                    i = 0;
                    j = p.find(s[i],j);
                    if(j==std::string::npos)
                        return false;
                } else {
                    j++;
                }
            }
            if(p[j]=='*') {
                char prev = p[j-1];
                while(p[j]=='*') {
                    if(prev==s[i] || prev=='.')
                        i++;
                    j++;
                }
            } else {
                i++;
                j++;
            }
        }
        if(i==len)
            return true;
        else
            return false;
    }
};

int main() {
    std::string s,p;

    std::cin >> s;
    std::cin >> p;

    Solution so;

    std::cout << so.isMatch(s,p) << '\n';

    return 0;
}
