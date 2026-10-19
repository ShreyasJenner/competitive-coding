#include <iostream>
#include <string>

class Solution {
    private:
    /*
    TODO (Lesson 4): write a helper that honours the contract
        reads exactly ONE expression starting at the cursor,
        returns its value,
        leaves the cursor on the character just after it.
    */

    public:
    bool parseBoolExpr(std::string expression) {
        // TODO: start a cursor at 0 and parse one expression
        return false;
    }
};

#ifndef TEST
int main() {
    Solution sol;
    for (std::string e : {"&(|(f))", "|(f,f,f,t)", "!(&(f,t))"}) {
        std::cout << e << " -> " << (sol.parseBoolExpr(e) ? "true" : "false") << '\n';
    }
    return 0;
}
#endif
