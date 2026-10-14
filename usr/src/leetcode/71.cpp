#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  string parser(string path, int *idx) {
    string temp = "";
    while (*idx != path.length() && path[*idx] != '/') {
      temp += path[*idx];
      *idx = *idx + 1;
    }

    if (temp == "") {
      while (path[*idx] == '/') {
        temp = "/";
        *idx = *idx + 1;
      }
    }

    return temp;
  }

  string simplifyPath(string path) {
    bool flag;
    int i;
    string temp, ans;
    stack<string> st;

    i = 0;
    flag = true;
    while (flag) {
      temp = parser(path, &i);

      if (temp == "/") {
        if (st.empty()) {
          st.push(temp);
        } else if (st.top() != "/") {
          st.push(temp);
        }
      } else if (temp == ".") {
        if (st.size() != 1) {
          st.pop();
        }
      } else if (temp == "..") {
        if (st.size() != 1) {
          st.pop();
          st.pop();
        }
      } else if (temp == "") {
        flag = false;
      } else {
        st.push(temp);
      }
    }

    if (st.top() == "/" && st.size() > 1) {
      st.pop();
    }

    while (!st.empty()) {
      ans.insert(0, st.top());
      st.pop();
    }

    return ans;
  }
};

int main() {
  Solution s;

  int i = 0;
  std::cout << s.simplifyPath("/a/./b/../../c/") << '\n';

  return 0;
}
