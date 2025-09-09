//! 括号匹配
#include <bits/stdc++.h>

// 描述：遍历表达式，遇到左括号入栈，遇到右括号就跟栈顶比较是否相同，相同则出栈顶元素，否则说明不匹配
// 遍历完成后若栈空说明匹配，否则不匹配
bool is_match(const std::string& s) {
    std::stack<char> st;
    for (char ch : s) {
        if (ch == '[' || ch == '(') {
            st.push(ch);
        }
        if (ch == ']') {
            if (st.top() != '[') {
                return false;
            }
            st.pop();
        }
        if (ch == ')') {
            if (st.top() != '(') {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    std::string s = "[1 * (2 + 3)] / (4 + 5)";
    assert(is_match(s)); // 栈内元素最多的状态：[(
    std::string s2 = "[(])";
    assert(!is_match(s2)); // 栈内元素最多的状态：[(
}