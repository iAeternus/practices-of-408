#include <bits/stdc++.h>

/**
 * @brief 判断大端还是小端
 * @return true=小端 false=大端
 */
bool judge_bigend_littleend1() {
    int i = 48;
    char c = *((char*)&i);
    return c == '0';
}

/**
 * @brief 判断大端还是小端
 * @return true=小端 false=大端
 */
bool judge_bigend_littleend2() {
    union {
        int i;
        char c;
    } un;
    un.i = 1;
    return un.c == 1;
}

int main() {
    assert(judge_bigend_littleend1() == true);
    assert(judge_bigend_littleend2() == true);

    std::cout << (judge_bigend_littleend1() ? "Little-Endian" : "Big-Endian") << std::endl;
    std::cout << (judge_bigend_littleend2() ? "Little-Endian" : "Big-Endian") << std::endl;
}