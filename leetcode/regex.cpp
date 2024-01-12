//https://leetcode.com/problems/regular-expression-matching/description/

#include <iostream>
#include <string>

class Solution {
    public:
        bool isMatching(std::string s, std::string p) {
            std::string r = "";
            int len = s.length(), plen = p.length(),i=0,j=0;

            while(j!=plen) {
                if(s[i]==p[j]) {
                    if(p[j+1]=='*') {
                        std::string temp = p.substr(j+2);
                        int tlen = temp.length();
                        while(j!=plen-tlen) {
                            r += s[i];
                            i++;
                            j++;
                        }
                    } else {
                        r += s[i];
                        i++;
                        j++;
                    }
                } else if(p[j]!='.') {
                    if(p[j+1]=='*') {
                        j += 2;
                    } else {
                        return false;
                    }
                } else {
                    if(p[j+1]=='*') {
                        while(p[j]=='.' || p[j]=='*')
                            j++;
                        if(j==plen) {
                            r += s.substr(i);
                            break;
                        }
                        int temp = i;
                        i = s.find(p[j],i);
                        if(i==std::string::npos)
                            return false;
                        r += s.substr(temp,i-temp);
                    } else {
                        r += s[i];
                        i++;
                        j++;
                    }
                }
            }
            std::cout << r << '\n';
            if(r==s)
                return true;
            return false;
        }
};

int main() {
    Solution so;

    std::string s,p;
    std::cin >> s;
    std::cin >> p;

    std::cout << so.isMatching(s,p) << '\n';

    return 0;
}

