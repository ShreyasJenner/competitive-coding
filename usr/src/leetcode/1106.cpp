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
    bool parseSingleExpr(const std::string &expr, int &cursor) {

        if(expr[cursor] == 't') {
            cursor++;
            return true;
        } else if(expr[cursor] == 'f') {
            cursor++;
            return false;
        } else if(expr[cursor] == '!') {
            cursor += 2;
            bool acc;

            while(expr[cursor] != ')') {
                acc = parseSingleExpr(expr, cursor) == true ? false : true;
            }
            cursor++;
            return acc;
        } else if(expr[cursor] == '|') {
            cursor += 2;
            bool acc = false;
            while(expr[cursor] != ')') {
                acc |= parseSingleExpr(expr, cursor);
                if(expr[cursor] == ',') {
                    cursor++;
                }
            }

            cursor++;
            return acc;
        } else {
            // '&' case handling
            cursor += 2;
            bool acc = true;

            while(expr[cursor] != ')') {
                acc &= parseSingleExpr(expr, cursor);
                if(expr[cursor] == ',') {
                    cursor++;
                }
            }

            cursor++;
            return acc;
        }
    }

    public:
    bool parseBoolExpr(std::string expression) {
        // TODO: start a cursor at 0 and parse one expression
        int start = 0;

        return parseSingleExpr(expression, start);
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
