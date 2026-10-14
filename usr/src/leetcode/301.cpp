#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <tuple>

class Solution {
    private:
    std::string s, path;
    int s_len;
    std::set<std::string> out;
    /* 
    Function that goes through the string and returns the allowed deletions of the '(' and ')' characters
    as a tuple
    */
    std::tuple<int, int> getDeleteBudget(std::string s) {
        int open = 0, len = s.size(), rmL, rmR;
        rmL = rmR = 0;

        for(int i = 0; i < len; i++) {
            if(s[i] == '(') {
                open++;
            } else if(s[i] == ')') {
                if(open) {
                    open--;
                } else {
                    rmR++;
                }
            }
        }
        rmL = open;

        return std::make_tuple(rmL, rmR);
    }

    /* DFS Function that builds the path with valid parantheses */
    void dfs(int i, int open, int rmL, int rmR) {
        if(i == this->s_len) {
            if(open == 0 && rmL == 0 && rmR == 0) {
                this->out.insert(path);
            }
            return;
        }

        if(this->s[i] == '(') {
            if(rmL > 0) {
                this->dfs(i + 1, open, rmL - 1, rmR);
            }
            this->path.push_back(this->s[i]);
            this->dfs(i + 1, open + 1, rmL, rmR);
            this->path.pop_back();
        } else if(this->s[i] == ')') {
            if(rmR > 0) {
                this->dfs(i + 1, open, rmL, rmR - 1);
            }
            if(open > 0) {
                this->path.push_back(this->s[i]);
                this->dfs(i + 1, open - 1, rmL, rmR);
                this->path.pop_back();
            }
        } else {
            this->path.push_back(s[i]);
            this->dfs(i + 1, open, rmL, rmR);
            this->path.pop_back();
        }
    }

    public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        // 2. dfs(i, open, rmL, rmR) building a path
        // 3. collect accepted paths in a set
        this->out.clear();
        this->path.clear();
        this->s = s;
        this->s_len = s.size();

        int rmL, rmR;

        std::tie(rmL, rmR) = this->getDeleteBudget(s);
        this->dfs(0, 0, rmL, rmR);

        return std::vector<std::string> (this->out.begin(), this->out.end());
    }
};

#ifndef TEST
int main() {

    Solution s;
    for (const std::string &r : s.removeInvalidParentheses("())"))
        std::cout << r << '\n';

    return 0;
}
#endif