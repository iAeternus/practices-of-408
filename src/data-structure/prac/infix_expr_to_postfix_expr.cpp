//! 中缀表达式转后缀表达式
#include <bits/stdc++.h>

std::map<char, int> mp = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'(', 3},
};

std::string in2post(const std::string& expr) {
    std::string res;
    std::stack<char> st;
    for (char ch : expr) {
        if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                res += st.top();
                st.pop();
            }
            if (!st.empty() && st.top() == '(') {
                st.pop();
            }
        } else if (mp.count(ch)) {
            while (!st.empty() && st.top() != '(' && mp[ch] <= mp[st.top()]) {
                res += st.top();
                st.pop();
            }
            st.push(ch);
        } else {
            res += ch;
        }
    }
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    return res;
}

int main() {
    std::string expr = "a+b-a*((c+d)/e-f)+g";
    assert(in2post(expr) == "ab+acd+e/f-*-g+");
    std::cout << "All tests passed!\n";
}