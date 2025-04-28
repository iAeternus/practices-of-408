#include <bits/stdc++.h>

/**
 * @see 68-03-2
 */
bool is_valid(const char ops[], int n) {
    int cnt = 0; // 栈内元素个数
    for (int i = 0; i < n; ++i) {
        if (ops[i] == 'I') {
            cnt++; // 入栈
        } else {
            cnt--; // 出栈
            if (cnt < 0) {
                return false;
            }
        }
    }
    return true;
}

auto should_is_valid = []() {
    assert(is_valid("IOIIOIOO", 8) == true);
    assert(is_valid("IOOIOIIO", 8) == false);
    assert(is_valid("IIIOIOIO", 8) == true);
    assert(is_valid("IIIOOIOO", 8) == true);
};

void separator() {
    std::cout << "=============================================\n";
}

int main() {
    should_is_valid();
    separator();
}